#pragma once
#include "lister.h"

#include "ParamPlu.h"

class CListerPlu : public CLister
{
public:
	CListerPlu(void);
	virtual ~CListerPlu(void);

	virtual  short   RetrieveList (void);
	virtual  CLister *getListObjectPtr (void) { return this; }
	virtual  short   GetCurrentListItem (void);
	virtual  short   GetNextListItem (void);
	virtual  short   GetFirstListItem (void);
	virtual  short    GetCurrentListTotal(void);
	virtual  short    GetNextListTotal (void);
	virtual  short    GetFirstListTotal (void);
	virtual  short    GetCurrentListItemTotal (void);
	virtual  short    GetCurrentListTotalItem (void);
	virtual  short    BuildPluArray (void);

public:
	BOOL      bPluData;
	short     PluDataCount;
	short     PluDataIndex;
	CParamPlu  PluData;

	CArray <CParamPlu::ParamPluKey, CParamPlu::ParamPluKey &> PluDataList;

};
