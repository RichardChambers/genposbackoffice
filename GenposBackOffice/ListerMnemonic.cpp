#include "StdAfx.h"
#include "ListerMnemonic.h"

CListerMnemonic::CListerMnemonic(void)
{
}

CListerMnemonic::~CListerMnemonic(void)
{
}

// -----------------------------------------------------------

char const * const CListerTransaction::aszSqlDrop = "drop table TransMnemoTable;";
char const * const CListerTransaction::aszSqlCreate = "create table TransMnemoTable (akey int primary key not null, avalue blob);";
char const * const CListerTransaction::aszSqlInsert = "insert into TransMnemoTable values (?1, ?2);";
char const * const CListerTransaction::aszSqlUpdate = "update TransMnemoTable set avalue = ?2 where akey == ?1;";
char const * const CListerTransaction::aszSqlDelete = "delete from TransMnemoTable where akey == ?1;";
char const * const CListerTransaction::aszSqlSelect = "select avalue from TransMnemoTable where akey == ?1;";

CListerTransaction::CListerTransaction(void)
{
}

CListerTransaction::~CListerTransaction(void)
{
}

/*
 *  RetrieveList () - retrieve data from GenPOS and build the internal list
 *  This function does not do any kind of persistent storage of the data retrieved.
 *  The data retrieves is merely kept in the memory resident area.
*/
short    CListerTransaction::RetrieveList (sqlite3 *db)
{
	int     rc;
	sqlite3_stmt  *selectStmt;

	rc = sqlite3_prepare(db, aszSqlSelect, -1, &selectStmt, NULL);
	TRACE2("   sqlite3_prepare() \"%s\" %d\n", aszSqlSelect, rc);

	for (int iLoop = 0; iLoop < MAX_TRANSM_NO; iLoop++) {

		// bind the key to the first parameter of the select, the key value
		rc = sqlite3_bind_int (selectStmt, 1, iLoop + 1);
		TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

		// perform the actual select with the modified prepared statement
		rc = sqlite3_step (selectStmt);
		TRACE2("   sqlite3_step() step select (%d is SQLITE_ROW) %d\n", SQLITE_ROW, rc);

		if (rc == SQLITE_ROW) {
			const void *pBlob = sqlite3_column_blob (selectStmt, 0);
			memcpy (abTransMnemonic[iLoop].GetSqliteBlob(0), pBlob, abTransMnemonic[iLoop].GetSqliteBlobSize(0));
		}

		// reset the prepared statement so that we do our next set of binds.
		rc = sqlite3_reset (selectStmt);
		TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (selectStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 0;
}

short    CListerTransaction::RetrieveAndStoreAndList (sqlite3 *db)
{
	int     rc;
	sqlite3_stmt  *insertStmt;

	rc = sqlite3_prepare(db, aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare() \"%s\" %d\n", aszSqlInsert, rc);

	for (int iLoop = 0; iLoop < MAX_TRANSM_NO; iLoop++) {

		short sLastError = abTransMnemonic[iLoop].PullParam(iLoop + 1);

		// bind the key to the first parameter of the insert, the key value
		rc = sqlite3_bind_int (insertStmt, 1, iLoop + 1);
		TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

		// bind the PLU data to the second parameter of the insert, the data value
		rc = sqlite3_bind_blob (insertStmt, 2, abTransMnemonic[iLoop].GetSqliteBlob(0), abTransMnemonic[iLoop].GetSqliteBlobSize(0), SQLITE_STATIC);
		TRACE1("   sqlite3_bind_blob() bind blob value %d\n", rc);

		// perform the actual insert with the modified prepared statement
		rc = sqlite3_step (insertStmt);
		TRACE2("   sqlite3_step() step insert (%d is SQLITE_DONE) %d\n", SQLITE_DONE, rc);

		// reset the prepared statement so that we do our next set of binds.
		rc = sqlite3_reset (insertStmt);
		TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (insertStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 1;
}


/*
 *  RetrieveAndStoreOnly (sqlite3 *db) - retrieve data from GenPOS and build the
 *  database table
 *  This function does a persistent storage of the data retrieved.
 *  The data retrieves is not kept in the memory resident area.
*/
short    CListerTransaction::RetrieveAndStoreOnly (sqlite3 *db)
{
	int     rc;
	sqlite3_stmt  *insertStmt;
	rc = sqlite3_prepare(db, aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare() \"%s\" %d\n", aszSqlInsert, rc);

	CParamTransaction  myTransMnemo;

	for (int iLoop = 0; iLoop < MAX_TRANSM_NO; iLoop++) {

		short sLastError = myTransMnemo.PullParam(iLoop + 1);

		// bind the key to the first parameter of the insert, the key value
		rc = sqlite3_bind_int (insertStmt, 1, iLoop + 1);
		TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

		// bind the PLU data to the second parameter of the insert, the data value
		rc = sqlite3_bind_blob (insertStmt, 2, myTransMnemo.GetSqliteBlob(0), myTransMnemo.GetSqliteBlobSize(0), SQLITE_STATIC);
		TRACE1("   sqlite3_bind_blob() bind blob value %d\n", rc);

		// perform the actual insert with the modified prepared statement
		rc = sqlite3_step (insertStmt);
		TRACE2("   sqlite3_step() step insert (%d is SQLITE_DONE) %d\n", SQLITE_DONE, rc);

		// reset the prepared statement so that we do our next set of binds.
		rc = sqlite3_reset (insertStmt);
		TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (insertStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 1;
}


short    CListerTransaction::GetCurrentListItem (void)
{
	 return 0;
}


short    CListerTransaction::GetNextListItem (void)
{
	 return 0;
}


short    CListerTransaction::GetFirstListItem (void)
{
	 return 0;
}


short    CListerTransaction::GetCurrentListTotal(void)
{
	 return 0;
}


short    CListerTransaction::GetNextListTotal (void)
{
	 return 0;
}


short    CListerTransaction::GetFirstListTotal (void)
{
	 return 0;
}


short    CListerTransaction::GetCurrentListItemTotal (void)
{
	 return 0;
}


short    CListerTransaction::GetCurrentListTotalItem (void)
{
	 return 0;
}


unsigned short CListerTransaction::GetMnemonicValue (unsigned short usAddress, CString &mnemonic)
{
	 unsigned short usAddr = usAddress - 1;

	 if (usAddr < MAX_TRANSM_NO) {
		abTransMnemonic[usAddr].GetMnemonicValue (mnemonic);
		usAddr = usAddress + 1;   // increment to the next in the array return value of non-zero or true
	 } else {
		 usAddr = 0;              // indicate no more by return value of 0 or false.
	 }
	 return usAddr;
}


unsigned short CListerTransaction::SetMnemonicValue (unsigned short usAddress, const CString &mnemonic)
{
	 unsigned short usAddr = usAddress - 1;

	 if (usAddr < MAX_TRANSM_NO) {
		abTransMnemonic[usAddress].SetMnemonicValue (mnemonic);
	 }
	 return 0;
}


unsigned short CListerTransaction::GetPromptText (unsigned short usAddress, LPWSTR mnemonic)
{
	 return CParamTransaction::GetPromptText (usAddress, mnemonic);
}



// -----------------------------------------------------------

char const * const CListerLeadThru::aszSqlDrop = "drop table LeadthruMnemoTable;";
char const * const CListerLeadThru::aszSqlCreate = "create table LeadthruMnemoTable (akey int primary key not null, avalue blob);";
char const * const CListerLeadThru::aszSqlInsert = "insert into LeadthruMnemoTable values (?1, ?2);";
char const * const CListerLeadThru::aszSqlUpdate = "update LeadthruMnemoTable set avalue = ?2 where akey == ?1;";
char const * const CListerLeadThru::aszSqlDelete = "delete from LeadthruMnemoTable where akey == ?1;";
char const * const CListerLeadThru::aszSqlSelect = "select avalue from LeadthruMnemoTable where akey == ?1;";

CListerLeadThru::CListerLeadThru(void)
{
}

CListerLeadThru::~CListerLeadThru(void)
{
}


 short    CListerLeadThru::RetrieveList (sqlite3 *db)
 {
	int     rc;
	sqlite3_stmt  *selectStmt;

	rc = sqlite3_prepare(db, aszSqlSelect, -1, &selectStmt, NULL);
	TRACE2("   sqlite3_prepare() \"%s\" %d\n", aszSqlSelect, rc);

	for (int iLoop = 0; iLoop < MAX_LEAD_NO; iLoop++) {

		// bind the key to the first parameter of the select, the key value
		rc = sqlite3_bind_int (selectStmt, 1, iLoop + 1);
		TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

		// perform the actual select with the modified prepared statement
		rc = sqlite3_step (selectStmt);
		TRACE2("   sqlite3_step() step select (%d is SQLITE_ROW) %d\n", SQLITE_ROW, rc);

		if (rc == SQLITE_ROW) {
			const void *pBlob = sqlite3_column_blob (selectStmt, 0);
			memcpy (abTransMnemonic[iLoop].GetSqliteBlob(0), pBlob, abTransMnemonic[iLoop].GetSqliteBlobSize(0));
		}

		// reset the prepared statement so that we do our next set of binds.
		rc = sqlite3_reset (selectStmt);
		TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (selectStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 0;
 }


/*
 *  RetrieveAndStoreOnly (sqlite3 *db) - retrieve data from GenPOS and build the
 *  database table
 *  This function does a persistent storage of the data retrieved.
 *  The data retrieves is not kept in the memory resident area.
*/short    CListerLeadThru::RetrieveAndStoreOnly (sqlite3 *db)
{
	int     rc;
	sqlite3_stmt  *insertStmt;

	rc = sqlite3_prepare(db, aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare() \"%s\" %d\n", aszSqlInsert, rc);

	CParamLeadThru myLeadThru;
	for (int iLoop = 0; iLoop < MAX_LEAD_NO; iLoop++) {

		short sLastError = myLeadThru.PullParam(iLoop + 1);

		// bind the key to the first parameter of the insert, the key value
		rc = sqlite3_bind_int (insertStmt, 1, iLoop + 1);
		TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

		// bind the PLU data to the second parameter of the insert, the data value
		rc = sqlite3_bind_blob (insertStmt, 2, myLeadThru.GetSqliteBlob(0), myLeadThru.GetSqliteBlobSize(0), SQLITE_STATIC);
		TRACE1("   sqlite3_bind_blob() bind blob value %d\n", rc);

		// perform the actual insert with the modified prepared statement
		rc = sqlite3_step (insertStmt);
		TRACE2("   sqlite3_step() step insert (%d is SQLITE_DONE) %d\n", SQLITE_DONE, rc);

		// reset the prepared statement so that we do our next set of binds.
		rc = sqlite3_reset (insertStmt);
		TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (insertStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 1;
}

short    CListerLeadThru::GetCurrentListItem (void)
{
	 return 0;
}


short    CListerLeadThru::GetNextListItem (void)
{
	 return 0;
}


short    CListerLeadThru::GetFirstListItem (void)
{
	 return 0;
}


short    CListerLeadThru::GetCurrentListTotal(void)
{
	 return 0;
}


short    CListerLeadThru::GetNextListTotal (void)
{
	 return 0;
}


short    CListerLeadThru::GetFirstListTotal (void)
{
	 return 0;
}


short    CListerLeadThru::GetCurrentListItemTotal (void)
{
	 return 0;
}


short    CListerLeadThru::GetCurrentListTotalItem (void)
{
	 return 0;
}


unsigned short CListerLeadThru::GetMnemonicValue (unsigned short usAddress, CString &mnemonic)
{
	 unsigned short usAddr = usAddress - 1;

	 if (usAddr < MAX_LEAD_NO) {
		abTransMnemonic[usAddr].GetMnemonicValue (mnemonic);
		usAddr = usAddress + 1;   // increment to the next in the array return value of non-zero or true
	 } else {
		 usAddr = 0;              // indicate no more by return value of 0 or false.
	 }
	 return usAddr;
}


unsigned short CListerLeadThru::SetMnemonicValue (unsigned short usAddress, const CString &mnemonic)
{
	 unsigned short usAddr = usAddress - 1;

	 if (usAddr < MAX_LEAD_NO) {
		abTransMnemonic[usAddress].SetMnemonicValue (mnemonic);
	 }
	 return 0;
}


unsigned short CListerLeadThru::GetPromptText (unsigned short usAddress, LPWSTR mnemonic)
{
	 return CParamLeadThru::GetPromptText (usAddress, mnemonic);
}
