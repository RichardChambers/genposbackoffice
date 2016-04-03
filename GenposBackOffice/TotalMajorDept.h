#pragma once
#include "total.h"

class CTotalMajorDept :
	public CTotal
{
public:
	CTotalMajorDept(CTotal::TtlType type, MajorDeptNo deptNo = 0);
	~CTotalMajorDept(void);

	TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlDept; }
	MajorDeptNo setTotalCoupon (MajorDeptNo deptNo) { MajorDeptNo oldDeptNo = m_ttlDept.usDEPTNumber; m_ttlDept.usDEPTNumber = deptNo; return oldDeptNo; }
	short getTotalStructLine (short &sPos, CString &csLine, TtlLineType lineType);
	short getTotalStructLine (int idsPos, CString &csLine, TtlLineType lineType);

public:
    TTLDEPT m_ttlDept;
};
