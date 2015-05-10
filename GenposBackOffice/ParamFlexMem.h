#pragma once
#include "param.h"

class CParamFlexMem : public CParam
{
public:
	CParamFlexMem(void);
	~CParamFlexMem(void);
	virtual short PullParam (void);
	virtual short PushParam (void);

public:
    FLEXMEM m_paraFlexMem[ FLEX_ADR_MAX ];
};
