#pragma once
#include "param.h"

class CParamPlu : public CParam
{
public:
#if     defined(WIN32) && _MSC_VER >= 800
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif
	struct ParamPluKey {
		WCHAR   auchPluNo[OP_PLU_LEN];      /* for temporary */
		UCHAR   uchPluAdj;
		ULONG   ulCounter;
	};
#if     defined(WIN32) && _MSC_VER >= 800
#pragma pack(pop)
#else
#pragma pack()
#endif
	CParamPlu(void);
	virtual ~CParamPlu(void);

	virtual short PullParam (void);
	virtual short PullParam (ParamPluKey &pluNo);
	virtual short PushParam (void);
	virtual void ClearParam(void) { memset (&m_paraPlu, 0, sizeof(m_paraPlu)); m_bDataRead = 0; }
	ParamPluKey  GetPluKey (int i) { ParamPluKey j; j = *((ParamPluKey *)(m_paraPlu + i)); return j; }

public:
#if     defined(WIN32) && _MSC_VER >= 800
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif
	PLUIF    m_paraPlu[CLI_PLU_MAX_NO];
#if     defined(WIN32) && _MSC_VER >= 800
#pragma pack(pop)
#else
#pragma pack()
#endif
};
