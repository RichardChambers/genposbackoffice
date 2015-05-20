#pragma once
#include "param.h"

class CParamFlexMem : public CParam
{
public:
	CParamFlexMem(void);
	~CParamFlexMem(void);
	virtual short PullParam (void);
	virtual short PushParam (void);
	virtual void ClearParam(void) { memset (m_paraFlexMem, 0, sizeof(m_paraFlexMem)); m_bDataRead = 0; }

	short SummaryToText (CString &csMemo);
	void Serialize (CArchive &ar);

public:
    FLEXMEM m_paraFlexMem[ FLEX_ADR_MAX ];
};
