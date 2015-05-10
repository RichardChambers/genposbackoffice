#pragma once

#include "R20_PC2172.h"

#include "a_globals.h"

class CLister
{
public:
	CLister(void);
	virtual ~CLister(void);

	virtual  short   RetrieveList (void) = 0;

public:
	short     m_sLastError;
};
