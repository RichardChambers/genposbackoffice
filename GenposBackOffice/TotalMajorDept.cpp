#include "StdAfx.h"
#include "TotalMajorDept.h"

CTotalMajorDept::CTotalMajorDept(CTotal::TtlType type, MajorDeptNo deptNo/* = 0 */) : CTotal(CLASS_TTLDEPT, type)
{
	m_ttlDept.usDEPTNumber = deptNo;
	m_mdcResetInd = NOT_EOD;
	m_mdcResetEndOfDay = EOD_DEPT;
}

CTotalMajorDept::~CTotalMajorDept(void)
{
}
