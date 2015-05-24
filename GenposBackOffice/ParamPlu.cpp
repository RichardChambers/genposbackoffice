#include "StdAfx.h"
#include "ParamPlu.h"

CParamPlu::CParamPlu(void)
{
}

CParamPlu::~CParamPlu(void)
{
}



short CParamPlu::PullParam (void)
{
	m_sLastError = ::CliOpPluIndRead(m_paraPlu, 0);
	m_bDataRead = ! (m_sLastError < 0);

	return m_sLastError;
}

short CParamPlu::PullParam (ParamPluKey &pluNo)
{
//	if (cashierNo > 0) {
		// allow the caller to over ride the cashier number if desired.
//		m_paraCashier.ulCashierNo = cashierNo;
		*(ParamPluKey *)m_paraPlu = pluNo;
		return PullParam();
//	}

	return -1;
}

short CParamPlu::PushParam (void)
{
	m_sLastError = ::SerOpPluAssign( m_paraPlu, 0 );

	return m_sLastError;
}
