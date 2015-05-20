#pragma once
#include "param.h"

class CParamMdc : public CParam
{
public:
	enum MdcBit {MdcBitD = 1, MdcBitC = 2, MdcBitB = 3, MdcBitA = 4, MdcNibbleLower = 5, MdcNibbleUpper = 6, MdcByte = 7};

	CParamMdc(void);
	virtual ~CParamMdc(void);
	virtual short PullParam (void);
	virtual short PushParam (void);
	virtual void ClearParam(void) { memset (abMDCData, 0, sizeof(abMDCData)); m_bDataRead = 0; }

	unsigned short GetMdcValue (unsigned short usAddress, MdcBit usBit);

public:
	BYTE   abMDCData[MAX_MDC_SIZE];		/* Buffer of MDC Data       */
};
