#include "StdAfx.h"
#include "ListerCashier.h"

CListerCashier::CListerCashier(void)
{
}

CListerCashier::~CListerCashier(void)
{
}

short   CListerCashier::RetrieveList (void)
{
	m_sLastError = ::SerCasAllIdRead( sizeof(CashierNoList), CashierNoList );

	return m_sLastError;
}
