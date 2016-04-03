#pragma once
#include "param.h"

class CParamFlexMem : public CParam
{
public:
	CParamFlexMem(void);
	~CParamFlexMem(void);
	short PullParam (void);
	short PushParam (void);
	void ClearParam(void) { memset (m_paraFlexMem, 0, sizeof(m_paraFlexMem)); m_bDataRead = 0; }
	char * GetSqliteKey (int i) { return NULL; }
	void * GetSqliteBlob (int i) { return NULL; }
	int  GetSqliteBlobSize (int i) { return 0; }

	short SummaryToText (CString &csMemo);
	void Serialize (CArchive &ar);

public:
    FLEXMEM m_paraFlexMem[ FLEX_ADR_MAX ];
};
