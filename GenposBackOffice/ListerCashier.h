#pragma once
#include "lister.h"
#include "ParamCashier.h"
#include "TotalCashier.h"

class CListerCashier : public CLister
{
public:
	CListerCashier(void);
	virtual ~CListerCashier(void);

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
