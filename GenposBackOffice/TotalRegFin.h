#pragma once
#include "total.h"

class CTotalRegFin : public CTotal
{
public:
	CTotalRegFin(CTotal::TtlType type = CTotal::TtlTypeNone);
	virtual ~CTotalRegFin(void);
	virtual TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlRegFin; }
	virtual short setTotalTerminal (short sTerm) { short oldTerm = m_ttlRegFin.usTerminalNumber; m_ttlRegFin.usTerminalNumber = sTerm; return oldTerm; }
	virtual short getTotalStructLine (short &sPos, CString &csLine, TtlLineType lineType);
	virtual short getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType);

public:
    TTLREGFIN   m_ttlRegFin;
};
