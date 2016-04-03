#pragma once
#include "lister.h"
#include "ParamCashier.h"
#include "TotalCashier.h"

class CListerCashier : public CLister
{
public:
	CListerCashier(void);
	~CListerCashier(void);

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

	short  BuildCashierArray (void);

public:
	BOOL      bCashierData;
	short     CashierDataCount;
	short     CashierDataIndex;
	BOOL      bCashierTotal;
	short     CashierTotalCount;
	short     CashierTotalIndex;
	ULONG     CashierNoList[CAS_NUMBER_OF_MAX_CASHIER];
	CParamCashier  CashierData;
	CTotalCashier  CashierTotal;

	CArray <CParamCashier, CParamCashier &> CashierDataList;
};
