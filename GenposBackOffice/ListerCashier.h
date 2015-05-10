#pragma once
#include "lister.h"

class CListerCashier :
	public CLister
{
public:
	CListerCashier(void);
	virtual ~CListerCashier(void);

	virtual  short   RetrieveList (void);

public:
	ULONG     CashierNoList[CAS_NUMBER_OF_MAX_CASHIER];
};
