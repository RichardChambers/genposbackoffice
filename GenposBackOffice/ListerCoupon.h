#pragma once
#include "lister.h"

#include "ParamCoupon.h"
#include "TotalCoupon.h"

class CListerCoupon : public CLister
{
public:
	CListerCoupon(void);
	~CListerCoupon(void);

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

public:
	BOOL      bCouponData;
	short     CouponDataCount;
	short     CouponDataIndex;
	BOOL      bCouponTotal;
	short     CouponTotalCount;
	short     CouponTotalIndex;
	CParamCoupon  CouponData;
	CTotalCoupon  CouponTotal;
};
