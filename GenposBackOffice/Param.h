#pragma once

#include "R20_PC2172.h"

#include "a_globals.h"

class CParam
{
public:
	struct ParamClassStruct {
		UCHAR       uchMajorClass;      /* Major Class Data definition */
		UCHAR       uchMinorClass;      /* Minor Class Data definition */
	};

	CParam(void);
	virtual ~CParam(void);
	virtual ParamClassStruct *getParamStructPtr (void) = 0;
	virtual short RetrieveParam (void) = 0;

public:
	short     m_sLastError;

};
