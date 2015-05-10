#pragma once
#include "totalregfin.h"

class CTotalIndRegFin : public CTotal
{
public:
	CTotalIndRegFin(CTotal::TtlType type, short sTermNo = 0);
	virtual ~CTotalIndRegFin(void);
	virtual TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlRegFin; }
	virtual short setTotalTerminal (short sTerm) { short oldTerm = m_ttlRegFin.usTerminalNumber; m_ttlRegFin.usTerminalNumber = sTerm; return oldTerm; }

public:
    TTLREGFIN   m_ttlRegFin;
};
