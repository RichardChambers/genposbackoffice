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

short CParamPlu::RetrieveNextSet (bool bStart)
{
	m_sCount = 0;

	if (bStart) {
		memset (m_paraPlu, 0, sizeof(m_paraPlu));
	} else {
		// The PLU read may return zero to 5 PLUs. We clear the PLU number area
		// so that we can detect if any PLUs were actually retrieved.
		// A read that is past the end of the PLUs stored will return a negative value.
		// However there is the possibility that before the read returns a negative
		// value it may return a zero error code but no PLUs.
		ClearPluKey();
	}

	m_sLastError = ::SerOpPluAllRead(m_paraPlu, 0);

	if (m_sLastError >= 0) {
		for (int i = 0; i < CLI_PLU_MAX_NO; i++) {
			if (m_paraPlu[i].auchPluNo[0]) {
				++m_sCount;
			}
		}
	}

	return m_sCount;
}