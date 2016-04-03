#pragma once
#include "param.h"

class CParamMajorDept : public CParam
{
public:
	CParamMajorDept(void);
	~CParamMajorDept(void);

	short PullParam (void);
	short PullParam (MajorDeptNo majordeptNo, MinorDeptNo minordeptNo);
	short PushParam (void);
	void ClearParam(void) { memset (&m_paraMajorDept, 0, sizeof(m_paraMajorDept)); m_bDataRead = 0; }
	char * GetSqliteKey (int i) { return NULL; }
	void * GetSqliteBlob (int i) { return NULL; }
	int  GetSqliteBlobSize (int i) { return 0; }

	MajorDeptNo setParamCashier (MajorDeptNo majordeptNo) { MajorDeptNo oldMajorDept = m_paraMajorDept.uchMajorDeptNo; m_paraMajorDept.uchMajorDeptNo = majordeptNo; return oldMajorDept; }

public:
	MDEPTIF    m_paraMajorDept;
};

class CParamMinorDept : public CParam
{
public:
	CParamMinorDept(void);
	~CParamMinorDept(void);

	short PullParam (void);
	short PullParam (MinorDeptNo minordeptNo);
	short PushParam (void);
	void ClearParam(void) { memset (&m_paraDept, 0, sizeof(m_paraDept)); m_bDataRead = 0; }
	char * GetSqliteKey (int i) { return NULL; }
	void * GetSqliteBlob (int i) { return NULL; }
	int  GetSqliteBlobSize (int i) { return 0; }

	MinorDeptNo setParamCashier (MinorDeptNo minordeptNo) { MinorDeptNo oldMinorDept = m_paraDept.usDeptNo; m_paraDept.usDeptNo = minordeptNo; return oldMinorDept; }

public:
	DEPTIF     m_paraDept;
};
