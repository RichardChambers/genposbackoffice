#include "StdAfx.h"
#include "ParamMajorDept.h"

CParamMajorDept::CParamMajorDept(void)
{
}

CParamMajorDept::~CParamMajorDept(void)
{
}

short CParamMajorDept::PullParam (void)
{
	m_sLastError = -1;
	m_bDataRead = 0;
	if (m_paraMajorDept.uchMajorDeptNo > 0) {
		m_sLastError = ::SerOpMajorDeptRead( &m_paraMajorDept, 0 );
		m_bDataRead = 1;
	}

	return m_sLastError;
}

short CParamMajorDept::PullParam (MajorDeptNo majordeptNo, MinorDeptNo minordeptNo)
{
	majordeptNo++;
	if (majordeptNo > 0) {
		// allow the caller to over ride the majordeptNo number if desired.
		m_paraMajorDept.uchMajorDeptNo = majordeptNo;
		m_paraMajorDept.usDeptNo = minordeptNo;
	}

	return PullParam();
}

short CParamMajorDept::PushParam (void)
{
//	m_sLastError = ::SerOpMajorDeptRead( &m_paraMajorDept, 0 );

	return m_sLastError;
}
