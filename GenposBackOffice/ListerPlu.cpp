#include "StdAfx.h"
#include "ListerPlu.h"

char const * const CListerPlu::aszSqlDrop = "drop table PluTable;";
char const * const CListerPlu::aszSqlCreate = "create table PluTable (akey character(14) primary key not null, avalue blob);";
char const * const CListerPlu::aszSqlInsert = "insert into PluTable values (?1, ?2);";
char const * const CListerPlu::aszSqlUpdate = "update PluTable set avalue = ?2 where akey == ?1;";
char const * const CListerPlu::aszSqlDelete = "delete from PluTable where akey == ?1;";
char const * const CListerPlu::aszSqlSelect = "select avalue from PluTable where akey == ?1;";
char const * const CListerPlu::aszSqlSelectSet = "select akey, avalue from PluTable where akey >= ?1 and akey <= ?2 order by akey;";
char const * const CListerPlu::aszSqlSelectSetKeyOnly = "select akey from PluTable where akey >= ?1 and akey <= ?2 order by akey;";
char const * const CListerPlu::aszSqlSelectAll = "select akey, avalue from PluTable order by akey;";
char const * const CListerPlu::aszSqlSelectAllKeyOnly = "select akey from PluTable order by akey;";


CListerPlu::CListerPlu(void) :
	bPluData(FALSE),
	PluDataCount(0), PluDataIndex(0)
{
}

CListerPlu::~CListerPlu(void)
{
}

/*
 *  Retrieve the list of PLUs from the terminal.
 *
*/
short   CListerPlu::RetrieveList (sqlite3 *db)
{

	m_sLastError = 0;
	PluDataCount = 0;
	PluDataList.RemoveAll ();

	// read and keep reading PLUs untile there are no more.
	int   rc;
	sqlite3_stmt  *selectStmt;

	rc = sqlite3_prepare(db, aszSqlSelectAll, -1, &selectStmt, NULL);
	TRACE2("   sqlite3_prepare()  \"%S\" %d\n", aszSqlSelectAll, rc);

	bool  bStart = true;
	short sCount = 0;
	while ( (rc = sqlite3_step (selectStmt)) == SQLITE_ROW) {
		// This is a valid PLU number so add it to our list.
		const void *pBlob = sqlite3_column_blob (selectStmt, 1);
		CParamPlu::ParamPluKey tempPluKey = *((CParamPlu::ParamPluKey *)pBlob);
		PluDataList.Add (tempPluKey);
		PluDataCount++;
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (selectStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return m_sLastError;
}

/*
 *  RetrieveAndStoreOnly (sqlite3 *db) - retrieve data from GenPOS and build the
 *  database table
 *  This function does a persistent storage of the data retrieved.
 *  The data retrieves is not kept in the memory resident area.
*/
short    CListerPlu::RetrieveAndStoreOnly (sqlite3 *db)
{
	int     rc;

	// read from GenPOS and keep reading PLUs untile there are no more.
	// for each PLU returned by GenPOS we will create a database record.
	sqlite3_stmt  *insertStmt;
	rc = sqlite3_prepare(db, aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare()  \"%S\" %d\n", aszSqlInsert, rc);

	CParamPlu  PluData;
	bool  bStart = true;
	int   sCount = 0;
	while ( (sCount = PluData.RetrieveNextSet(bStart)) > 0) {
		bStart = false;
		for (int i = 0; i < sCount; i++) {
			char xKey[14] = {0};

			// convert the PLU number, stored as wchar_t, to char to create the table key.
			for (int j = 0; j < 14; j++) xKey[j] = (char)PluData.m_paraPlu[i].auchPluNo[j];

			// bind the key to the first parameter of the insert, the key value
			rc = sqlite3_bind_text (insertStmt, 1, xKey, 14, SQLITE_STATIC);
			TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

			// bind the PLU data to the second parameter of the insert, the data value
			rc = sqlite3_bind_blob (insertStmt, 2, PluData.m_paraPlu + i, sizeof(PluData.m_paraPlu[0]), SQLITE_STATIC);
			TRACE1("   sqlite3_bind_blob() bind blob value %d\n", rc);

			// perform the actual insert with the modified prepared statement
			rc = sqlite3_step (insertStmt);
			TRACE2("   sqlite3_step() step insert (%d is SQLITE_DONE) %d\n", SQLITE_DONE, rc);

			// reset the prepared statement so that we do our next set of binds.
			rc = sqlite3_reset (insertStmt);
			TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);
		}
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (insertStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 1;
}

short   CListerPlu::GetCurrentListItem (void)
{
	short  sRet = -1;

	if (PluDataIndex < PluDataCount) {
		sRet = PluData.PullParam (PluDataList.GetAt(PluDataIndex));
	}

	bPluData = (sRet == 0);
	return -1;
}

short   CListerPlu::GetNextListItem (void)
{
	if (PluDataIndex <= PluDataCount) {
		// we use <= in order to allow the index to go one past the max
		// we depend on GetCurrentListItem() to indicate past end of list.
		PluDataIndex++;
	}

	return GetCurrentListItem (); 
}

short   CListerPlu::GetFirstListItem (void)
{
	PluDataIndex = 0;

	return GetCurrentListItem ();
}

short   CListerPlu::GetCurrentListTotal (void)
{
	short  sRet = -1;

	return -1;
}

short   CListerPlu::GetNextListTotal (void)
{
	return GetCurrentListTotal (); 
}

short   CListerPlu::GetFirstListTotal (void)
{

	return GetCurrentListTotal ();
}

short   CListerPlu::GetCurrentListItemTotal (void)
{

	return GetCurrentListTotal ();
}

short   CListerPlu::GetCurrentListTotalItem (void)
{

	return GetCurrentListItem ();
}
