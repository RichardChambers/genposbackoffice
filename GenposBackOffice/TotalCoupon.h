#pragma once
#include "total.h"

class CTotalCoupon : public CTotal
{
public:
	CTotalCoupon(CTotal::TtlType type, CouponNo couponNo = 0);
	virtual ~CTotalCoupon(void);
	virtual TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlCoupon; }
	virtual CouponNo setTotalCoupon (CouponNo couponNo) { CouponNo oldCoupon = m_ttlCoupon.usCpnNumber; m_ttlCoupon.usCpnNumber = couponNo; return oldCoupon; }

public:
    TTLCPN  m_ttlCoupon;
};
