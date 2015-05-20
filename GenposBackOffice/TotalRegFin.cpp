#include "StdAfx.h"
#include "TotalRegFin.h"

CTotalRegFin::CTotalRegFin(CTotal::TtlType type) : CTotal(CLASS_TTLREGFIN, type)
{
	m_mdcResetInd = NOT_EOD;
	m_mdcResetEndOfDay = EOD_REGFIN;
}

CTotalRegFin::~CTotalRegFin(void)
{
}


short CTotalRegFin::getTotalStructLine (short &sPos, CString &csLine, CTotal::TtlLineType lineType)
{
	return 0;
}

short CTotalRegFin::getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType)
{
	return 0;
}
