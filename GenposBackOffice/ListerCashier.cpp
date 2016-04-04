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

short   CListerCashier::RetrieveList (void)
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

short  CListerCashier::BuildCashierArray (void)
{
	if (RetrieveList () >= 0) {
		CashierDataList.RemoveAll ();
		for (GetFirstListItem(); bCashierData; GetNextListItem ()) {
			CashierDataList.Add (CashierData);
		}

		int iCount = CashierDataList.GetCount ();
	}

	return 0;
}