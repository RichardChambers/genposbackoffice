#pragma once
#include "param.h"

class CParamCoupon : public CParam
{
public:
	CParamCoupon(CouponNo couponNo = 0);
	virtual ~CParamCoupon(void);

	virtual short PullParam (void);
	virtual short PullParam (CouponNo couponNo);
	virtual short PushParam (void);
	virtual CouponNo setParamCashier (CouponNo couponNo) { CouponNo oldCoupon = m_paraCoupon.uchCpnNo; m_paraCoupon.uchCpnNo = couponNo; return oldCoupon; }

public:
	CPNIF    m_paraCoupon;
};
