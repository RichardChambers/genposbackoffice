#include "StdAfx.h"
#include "ParamCashier.h"

CParamCashier::CParamCashier(CashierId cashierNo)
{
	m_paraCashier.ulCashierNo = cashierNo;
}

CParamCashier::~CParamCashier(void)
{
}

short CParamCashier::RetrieveParam (void)
{
   m_sLastError = ::SerCasIndRead( &m_paraCashier );

   return m_sLastError;
}
