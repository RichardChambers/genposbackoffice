#pragma once
#include "total.h"

class CTotalCashier : public CTotal
{
public:
	CTotalCashier(CTotal::TtlType type, CashierId cashierNo = 0);
	virtual ~CTotalCashier(void);
	virtual TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlCashier; }
	virtual CashierId setTotalCashier (CashierId cashierNo) { CashierId oldCashier = m_ttlCashier.ulCashierNumber; m_ttlCashier.ulCashierNumber = cashierNo; return oldCashier; }
	virtual short getTotalStructLine (short &sPos, CString &csLine, TtlLineType lineType);
	virtual short getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType);

public:
	struct CTotalCashierText {
		int                 idString;
		CTotal::TtlVarType  iType;
		char                *aszTag;
		int                 iOffset;
	};

	static const CTotalCashierText transtable[];

public:

    TTLCASHIER   m_ttlCashier;
};
