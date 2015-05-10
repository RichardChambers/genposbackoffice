#pragma once
#include "param.h"

class CParamCashier :
	public CParam
{
public:
	CParamCashier(CashierId cashierNo);
	virtual ~CParamCashier(void);

	virtual ParamClassStruct *getParamStructPtr (void) { return (ParamClassStruct *)&m_paraCashier; };
	virtual short RetrieveParam (void);
	virtual CashierId setTotalCashier (CashierId cashierNo) { CashierId oldCashier = m_paraCashier.ulCashierNo; m_paraCashier.ulCashierNo = cashierNo; return oldCashier; }

public:
	CASIF    m_paraCashier;
};
