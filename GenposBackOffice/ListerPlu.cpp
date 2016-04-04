#include "StdAfx.h"
#include "ListerPlu.h"

char const * const CListerPlu::aszSqlDrop = "drop table PluTable;";
char const * const CListerPlu::aszSqlCreate = "create table PluTable (akey character(14) primary key not null, avalue blob);";
char const * const CListerPlu::aszSqlInsert = "insert into PluTable values (?1, ?2);";
char const * const CListerPlu::aszSqlUpdate = "update PluTable set avalue = ?2 where akey == ?1;";
char const * const CListerPlu::aszSqlDelete = "delete from PluTable where akey == ?1;";
char const * const CListerPlu::aszSqlSelect = "select avalue from PluTable where akey == ?1;";


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
short   CListerPlu::RetrieveList (void)
{
	CParamPlu::ParamPluKey tempPluKey;

	m_sLastError = 0;
	PluDataCount = 0;
	PluDataList.RemoveAll ();

	// read and keep reading PLUs untile there are no more.
	bool  bStart = true;
	short sCount = 0;
	while ( (sCount = PluData.RetrieveNextSet(bStart)) > 0) {
		bStart = false;
		for (int i = 0; i < sCount; i++) {
			tempPluKey = PluData.GetPluKey (i);
			if (tempPluKey.auchPluNo[0]) {
				// This is a valid PLU number so add it to our list.
				PluDataList.Add (tempPluKey);
				PluDataCount++;
			}
		}
	}

	return m_sLastError;
}

short   CListerPlu::RetrieveList (sqlite3 *db)
{
	CParamPlu::ParamPluKey tempPluKey;

	m_sLastError = 0;
	PluDataCount = 0;
	PluDataList.RemoveAll ();

	// read and keep reading PLUs untile there are no more.
	int   rc;
	sqlite3_stmt  *insertStmt;
	char  *aszSqlInsert = "insert into PluTable values (?, ?);";

	rc = sqlite3_prepare(db, aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare()  \"%s\" %d\n", aszSqlInsert, rc);

	bool  bStart = true;
	short sCount = 0;
	while ( (sCount = PluData.RetrieveNextSet(bStart)) > 0) {
		bStart = false;
		for (int i = 0; i < sCount; i++) {
			tempPluKey = PluData.GetPluKey (i);
			if (tempPluKey.auchPluNo[0]) {
				// bind the key to the first parameter of the insert, the key value
				rc = sqlite3_bind_text (insertStmt, 1, PluData.GetSqliteKey (i), 14, SQLITE_STATIC);
				TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

				// bind the PLU data to the second parameter of the insert, the data value
				rc = sqlite3_bind_blob (insertStmt, 2, PluData.GetSqliteBlob (i), PluData.GetSqliteBlobSize (i), SQLITE_STATIC);
				TRACE1("   sqlite3_bind_blob() bind blob value %d\n", rc);

				// perform the actual insert with the modified prepared statement
				rc = sqlite3_step (insertStmt);
				TRACE2("   sqlite3_step() step insert (%d is SQLITE_DONE) %d\n", SQLITE_DONE, rc);

				// reset the prepared statement so that we do our next set of binds.
				rc = sqlite3_reset (insertStmt);
				TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);
				// This is a valid PLU number so add it to our list.
				PluDataList.Add (tempPluKey);
				PluDataCount++;
			}
		}
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (insertStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return m_sLastError;
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

short  CListerPlu::BuildPluArray (void)
{
	RetrieveList ();
	int iCount = PluDataList.GetCount ();

	return 0;
}