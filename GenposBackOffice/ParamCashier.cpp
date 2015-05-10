#include "StdAfx.h"
#include "ParamCashier.h"

CParamCashier::CParamCashier(CashierId cashierNo)
{
	m_paraCashier.ulCashierNo = cashierNo;
}

CParamCashier::~CParamCashier(void)
{
}

short CParamCashier::PullParam (CashierId cashierNo /* = 0 */)
{
	if (cashierNo > 0) {
		// allow the caller to over ride the cashier number if desired.
		m_paraCashier.ulCashierNo = cashierNo;
	}
	m_sLastErrorCas = ::SerCasIndRead( &m_paraCashier );
	memset (&m_jobETK, 0, sizeof(m_jobETK));
	m_sLastErrorEtk = ::SerEtkIndJobRead( m_paraCashier.ulCashierNo, &m_jobETK, m_auchETKName );

	m_sLastError = m_sLastErrorCas;
	return m_sLastError;
}

short CParamCashier::PushParam (void)
{
	m_sLastErrorCas = ::SerCasAssign( &m_paraCashier );
	m_sLastErrorEtk = ::SerEtkAssign( m_paraCashier.ulCashierNo, &m_jobETK, m_paraCashier.auchCashierName );

	m_sLastError = m_sLastErrorCas;
	return m_sLastError;
}
