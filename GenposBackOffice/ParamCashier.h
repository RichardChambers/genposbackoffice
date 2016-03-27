#pragma once
#include "param.h"

class CParamCashier : public CParam
{
public:
	CParamCashier(void);
	CParamCashier(CashierId cashierNo);
	virtual ~CParamCashier(void);

	virtual short PullParam (void);
	virtual short PullParam (CashierId cashierNo);
	virtual short PushParam (void);
	virtual void ClearParam(void) { memset (&m_paraCashier, 0, sizeof(m_paraCashier)); memset (&m_jobETK, 0, sizeof(m_jobETK)); m_bDataRead = 0; }
	virtual CashierId setParamCashier (CashierId cashierNo) { CashierId oldCashier = m_paraCashier.ulCashierNo; m_paraCashier.ulCashierNo = cashierNo; return oldCashier; }

public:
	short    m_sLastErrorCas;
	short    m_sLastErrorEtk;

	CASIF    m_paraCashier;
	ETK_JOB  m_jobETK;
	WCHAR    m_auchETKName[ ETK_MAX_NAME_SIZE + 1 ];

	struct CASIF_ETK {
		CASIF    m_paraCashier;
		ETK_JOB  m_jobETK;
	};
};
