#include "StdAfx.h"
#include "ListerCashier.h"

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

short   CListerCashier::GetCurrentListItem (void)
{
	short  sRet = -1;

	if (CashierDataIndex < CashierDataCount) {
		sRet = CashierData.PullParam (CashierNoList[CashierDataIndex]);
	}

	bCashierData = (sRet == 0);
	return -1;
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
