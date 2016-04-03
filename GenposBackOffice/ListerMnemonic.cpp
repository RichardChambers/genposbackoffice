#include "StdAfx.h"
#include "ListerMnemonic.h"

CListerMnemonic::CListerMnemonic(void)
{
}

CListerMnemonic::~CListerMnemonic(void)
{
}

// -----------------------------------------------------------

CListerTransaction::CListerTransaction(void)
{
}

CListerTransaction::~CListerTransaction(void)
{
}

 short    CListerTransaction::RetrieveList (void)
 {
	for (int iLoop = 0; iLoop < MAX_TRANSM_NO; iLoop++) {
		short sLastError = abTransMnemonic[iLoop].PullParam(iLoop + 1);
	}

	return 0;
 }

 short    CListerTransaction::RetrieveList (sqlite3 *db)
 {
	int     rc;
	char    *aszSqlInsert = "insert into TransMnemoTable values (?, ?);";
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

CListerLeadThru::CListerLeadThru(void)
{
}

CListerLeadThru::~CListerLeadThru(void)
{
}

 short    CListerLeadThru::RetrieveList (void)
 {
	for (int iLoop = 0; iLoop < MAX_LEAD_NO; iLoop++) {
		short sLastError = abTransMnemonic[iLoop].PullParam(iLoop + 1);
	}

	return 0;
 }

 short    CListerLeadThru::RetrieveList (sqlite3 *db)
 {
	int     rc;
	char    *aszSqlInsert = "insert into LeadthruMnemoTable values (?, ?);";
	sqlite3_stmt  *insertStmt;
	rc = sqlite3_prepare(db, aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare() \"%s\" %d\n", aszSqlInsert, rc);

	for (int iLoop = 0; iLoop < MAX_LEAD_NO; iLoop++) {

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


