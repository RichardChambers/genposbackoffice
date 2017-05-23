#pragma once
#include "lister.h"

#include "ParamPlu.h"

class CListerPlu : public CLister
{
public:
	CListerPlu(void);
	~CListerPlu(void);

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

	static short    RetrieveAndStoreOnly (sqlite3 *db);

public:
	static char const * const aszSqlDrop;
	static char const * const aszSqlCreate;
	static char const * const aszSqlInsert;
	static char const * const aszSqlUpdate;
	static char const * const aszSqlDelete;
	static char const * const aszSqlSelect;
	static char const * const aszSqlSelectSet;
	static char const * const aszSqlSelectSetKeyOnly;
	static char const * const aszSqlSelectAll;
	static char const * const aszSqlSelectAllKeyOnly;

public:
	BOOL      bPluData;
	short     PluDataCount;
	short     PluDataIndex;
	CParamPlu  PluData;

	CArray <CParamPlu::ParamPluKey, CParamPlu::ParamPluKey &> PluDataList;

};
