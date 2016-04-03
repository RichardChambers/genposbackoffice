#pragma once
#include "param.h"

class CParamCashier : public CParam
{
public:
	CParamCashier(void);
	CParamCashier(CashierId cashierNo);
	~CParamCashier(void);

	short PullParam (void);
	short PullParam (CashierId cashierNo);
	short PushParam (void);
	void ClearParam(void) { memset (&m_paraCashier, 0, sizeof(m_paraCashier)); memset (&m_jobETK, 0, sizeof(m_jobETK)); m_bDataRead = 0; }
	CashierId setParamCashier (CashierId cashierNo) { CashierId oldCashier = m_paraCashier.ulCashierNo; m_paraCashier.ulCashierNo = cashierNo; return oldCashier; }
	char * GetSqliteKey (int i) { return NULL; }
	void * GetSqliteBlob (int i) { return NULL; }
	int  GetSqliteBlobSize (int i) { return 0; }

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
