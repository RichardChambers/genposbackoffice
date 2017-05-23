#include "StdAfx.h"
#include "ListerCashier.h"

char const * const CListerCashier::aszSqlDrop = "drop table CashierTable;";
char const * const CListerCashier::aszSqlCreate = "create table CashierTable (akey character(10) primary key not null, avalue blob);";
char const * const CListerCashier::aszSqlInsert = "insert into CashierTable values (?1, ?2);";
char const * const CListerCashier::aszSqlUpdate = "update CashierTable set avalue = ?2 where akey == ?1;";
char const * const CListerCashier::aszSqlDelete = "delete from CashierTable where akey == ?1;";
char const * const CListerCashier::aszSqlSelect = "select avalue from CashierTable where akey == ?1;";

CListerCashier::CListerCashier(void) :
	bCashierData(FALSE),
	CashierDataCount(0), CashierDataIndex(0),
	bCashierTotal(FALSE),
	CashierTotalCount(0), CashierTotalIndex(0),
	CashierData(0), CashierTotal(CTotal::TtlTypeNone)
{
}

CListerCashier::~CListerCashier(void)
{
}

short   CListerCashier::RetrieveList (sqlite3 *db)
{
	m_sLastError = ::SerCasAllIdRead( sizeof(CashierNoList), CashierNoList );
	if (m_sLastError > 0) {
		CashierDataCount = m_sLastError;
		CashierTotalCount = m_sLastError;
	} else {
		CashierDataCount = 0;
		CashierTotalCount = 0;
	}

	return m_sLastError;
}

/*
 *  RetrieveAndStoreOnly (sqlite3 *db) - retrieve data from GenPOS and build the
 *  database table
 *  This function does a persistent storage of the data retrieved.
 *  The data retrieves is not kept in the memory resident area.
*/
short    CListerCashier::RetrieveAndStoreOnly (sqlite3 *db)
{
	int     rc;
	// read from GenPOS and keep reading Cashiers until there are no more.
	// for each Cashier returned by GenPOS we will create a database record.
	sqlite3_stmt  *insertStmt;
	rc = sqlite3_prepare(db, CListerCashier::aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare() \"%S\" %d\n", CListerCashier::aszSqlInsert, rc);

	ULONG     CashierNoList[CAS_NUMBER_OF_MAX_CASHIER];

	short     CashierDataCount = ::SerCasAllIdRead( sizeof(CashierNoList), CashierNoList );
	
	CParamCashier  CashierData;

	short     CashierDataIndex = 0;
	while (CashierDataIndex < CashierDataCount) {
		CParamCashier::CASIF_ETK  dataBlob = {0};
		char       xKey[14] = {0};

		if (CashierData.PullParam (CashierNoList[CashierDataIndex]) < 0)
			break;

		// convert the PLU number, stored as wchar_t, to char to create the table key.
		sprintf_s (xKey, 14, "%10.10d", CashierData.m_paraCashier.ulCashierNo);
		dataBlob.m_paraCashier = CashierData.m_paraCashier;
		dataBlob.m_jobETK = CashierData.m_jobETK;

		// bind the key to the first parameter of the insert, the key value
		rc = sqlite3_bind_text (insertStmt, 1, xKey, 10, SQLITE_STATIC);
		TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

		// bind the PLU data to the second parameter of the insert, the data value
		rc = sqlite3_bind_blob (insertStmt, 2, &dataBlob, sizeof(dataBlob), SQLITE_STATIC);
		TRACE1("   sqlite3_bind_blob() bind blob value %d\n", rc);

		// perform the actual insert with the modified prepared statement
		rc = sqlite3_step (insertStmt);
		TRACE2("   sqlite3_step() step insert (%d is SQLITE_DONE) %d\n", SQLITE_DONE, rc);

		// reset the prepared statement so that we do our next set of binds.
		rc = sqlite3_reset (insertStmt);
		TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);

		CashierDataIndex++;
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (insertStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 1;
}

short   CListerCashier::GetCurrentListItem (void)
{
	short  sRet = -1;

	if (CashierDataIndex < CashierDataCount) {
		sRet = CashierData.PullParam (CashierNoList[CashierDataIndex]);
	}

	bCashierData = (sRet == 0);
	return sRet;
}

short   CListerCashier::GetNextListItem (void)
{
	if (CashierDataIndex <= CashierDataCount) {
		// we use <= in order to allow the index to go one past the max
		// we depend on GetCurrentListItem() to indicate past end of list.
		CashierDataIndex++;
	}

	return GetCurrentListItem (); 
}

short   CListerCashier::GetFirstListItem (void)
{
	CashierDataIndex = 0;

	return GetCurrentListItem ();
}

short   CListerCashier::GetCurrentListTotal (void)
{
	short  sRet = -1;

	if (CashierTotalIndex < CashierTotalCount) {
		CashierTotal.setTotalCashier (CashierNoList[CashierTotalIndex]);
		sRet = CashierTotal.RetrieveTotal ();
	}

	bCashierTotal = (sRet == 0);
	return -1;
}

short   CListerCashier::GetNextListTotal (void)
{
	if (CashierTotalIndex <= CashierTotalCount) {
		// we use <= in order to allow the index to go one past the max
		// we depend on GetCurrentListItem() to indicate past end of list.
		CashierTotalIndex++;
	}

	return GetCurrentListTotal (); 
}

short   CListerCashier::GetFirstListTotal (void)
{
	CashierTotalIndex = 0;

	return GetCurrentListTotal ();
}

short   CListerCashier::GetCurrentListItemTotal (void)
{
	CashierTotalIndex = CashierDataIndex;

	return GetCurrentListTotal ();
}

short   CListerCashier::GetCurrentListTotalItem (void)
{
	CashierDataIndex = CashierTotalIndex;

	return GetCurrentListItem ();
}
