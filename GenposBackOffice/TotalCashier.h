#pragma once
#include "total.h"

class CTotalCashier : public CTotal
{
public:
	CTotalCashier(CTotal::TtlType type, CashierId cashierNo = 0);
	~CTotalCashier(void);

	TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlCashier; }
	CashierId setTotalCashier (CashierId cashierNo) { CashierId oldCashier = m_ttlCashier.ulCashierNumber; m_ttlCashier.ulCashierNumber = cashierNo; return oldCashier; }
	short getTotalStructLine (short &sPos, CString &csLine, TtlLineType lineType);
	short getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType);

public:

	static const CTotalText transtable[];

public:

    TTLCASHIER   m_ttlCashier;
};
