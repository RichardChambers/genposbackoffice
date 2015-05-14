#pragma once
#include "lister.h"

#include "ParamCoupon.h"
#include "TotalCoupon.h"

class CListerCoupon : public CLister
{
public:
	CListerCoupon(void);
	virtual ~CListerCoupon(void);

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
