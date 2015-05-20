#include "StdAfx.h"
#include "TotalIndRegFin.h"

CTotalIndRegFin::CTotalIndRegFin(CTotal::TtlType type, short sTermNo/* = 0 */) : CTotal(CLASS_TTLINDFIN, type)
{
	m_ttlRegFin.usTerminalNumber = sTermNo;
	m_mdcResetInd = NOT_EOD;
	m_mdcResetEndOfDay = EOD_INDFIN;
}

CTotalIndRegFin::~CTotalIndRegFin(void)
{
}

short CTotalIndRegFin::getTotalStructLine (short &sPos, CString &csLine, CTotal::TtlLineType lineType)
{
	return 0;
}

short CTotalIndRegFin::getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType)
{
	return 0;
}

