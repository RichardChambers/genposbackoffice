#pragma once
#include "total.h"

class CTotalRegFin : public CTotal
{
public:
	CTotalRegFin(CTotal::TtlType type = CTotal::TtlTypeNone);
	~CTotalRegFin(void);

	TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlRegFin; }
	short setTotalTerminal (short sTerm) { short oldTerm = m_ttlRegFin.usTerminalNumber; m_ttlRegFin.usTerminalNumber = sTerm; return oldTerm; }
	short getTotalStructLine (short &sPos, CString &csLine, TtlLineType lineType);
	short getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType);

	static const CTotalText transtable[];

public:
    TTLREGFIN   m_ttlRegFin;
};
