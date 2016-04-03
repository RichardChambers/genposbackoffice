#pragma once
#include "lister.h"

#include "ParamPlu.h"

class CListerPlu : public CLister
{
public:
	CListerPlu(void);
	~CListerPlu(void);

	short   RetrieveList (void);
	short   RetrieveList (sqlite3 *db);
	CLister *getListObjectPtr (void) { return this; }
	short   GetCurrentListItem (void);
	short   GetNextListItem (void);
	short   GetFirstListItem (void);
	short    GetCurrentListTotal(void);
	short    GetNextListTotal (void);
	short    GetFirstListTotal (void);
	short    GetCurrentListItemTotal (void);
	short    GetCurrentListTotalItem (void);
	short    BuildPluArray (void);

public:
	BOOL      bPluData;
	short     PluDataCount;
	short     PluDataIndex;
	CParamPlu  PluData;

	CArray <CParamPlu::ParamPluKey, CParamPlu::ParamPluKey &> PluDataList;

};
