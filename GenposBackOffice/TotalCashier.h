#pragma once
#include "total.h"

class CTotalCashier : public CTotal
{
public:
	CTotalCashier(CTotal::TtlType type, CashierId cashierNo = 0);
	virtual ~CTotalCashier(void);
	virtual TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlCashier; }
	virtual CashierId setTotalCashier (CashierId cashierNo) { CashierId oldCashier = m_ttlCashier.ulCashierNumber; m_ttlCashier.ulCashierNumber = cashierNo; return oldCashier; }

public:
    TTLCASHIER   m_ttlCashier;
};
