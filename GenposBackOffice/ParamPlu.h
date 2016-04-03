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
	~CParamPlu(void);

	short PullParam (void);
	short PullParam (ParamPluKey &pluNo);
	short PushParam (void);
	void ClearParam(void) { memset (&m_paraPlu, 0, sizeof(m_paraPlu)); m_bDataRead = 0; }
	char       * GetSqliteKey (int i) { for (int j = 0; j < 14; j++) m_SqliteKey[j] = (char)m_paraPlu[i].auchPluNo[j]; return &m_SqliteKey[0]; }
	void       * GetSqliteBlob (int i) {return m_paraPlu + i; }
	int          GetSqliteBlobSize (int i) { return sizeof(m_paraPlu[0]); }

	ParamPluKey  GetPluKey (int i) { ParamPluKey j; j = *((ParamPluKey *)(m_paraPlu + i)); return j; }
	void         ClearPluKey (void) { for (int i = 0; i < CLI_PLU_MAX_NO; i++) { memset (m_paraPlu[i].auchPluNo, 0, sizeof(m_paraPlu[i].auchPluNo)); } }
	short        RetrieveNextSet (bool bStart);

public:
	short   m_sCount;
	char    m_SqliteKey[14];

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
