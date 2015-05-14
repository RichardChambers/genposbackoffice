#pragma once
#include "param.h"

class CParamMajorDept : public CParam
{
public:
	CParamMajorDept(void);
	virtual ~CParamMajorDept(void);

	virtual short PullParam (void);
	virtual short PullParam (MajorDeptNo majordeptNo, MinorDeptNo minordeptNo);
	virtual short PushParam (void);
	virtual MajorDeptNo setParamCashier (MajorDeptNo majordeptNo) { MajorDeptNo oldMajorDept = m_paraMajorDept.uchMajorDeptNo; m_paraMajorDept.uchMajorDeptNo = majordeptNo; return oldMajorDept; }

public:
	MDEPTIF    m_paraMajorDept;
	DEPTIF     m_paraDept;
};
