#pragma once
#include "totalregfin.h"

class CTotalIndRegFin : public CTotal
{
public:
	CTotalIndRegFin(CTotal::TtlType type, short sTermNo = 0);
	~CTotalIndRegFin(void);

	TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlRegFin; }
	short setTotalTerminal (short sTerm) { short oldTerm = m_ttlRegFin.usTerminalNumber; m_ttlRegFin.usTerminalNumber = sTerm; return oldTerm; }
	short getTotalStructLine (short &sPos, CString &csLine, TtlLineType lineType);
	short getTotalStructLine (int idsPos, CString &csLine, TtlLineType lineType);

public:
    TTLREGFIN   m_ttlRegFin;
};
