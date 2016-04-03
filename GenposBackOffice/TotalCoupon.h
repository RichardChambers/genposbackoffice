#pragma once
#include "total.h"

class CTotalCoupon : public CTotal
{
public:
	CTotalCoupon(CTotal::TtlType type, CouponNo couponNo = 0);
	~CTotalCoupon(void);

	TtlClassStruct *getTotalStructPtr (void) { return (TtlClassStruct *)&m_ttlCoupon; }
	CouponNo setTotalCoupon (CouponNo couponNo) { CouponNo oldCoupon = m_ttlCoupon.usCpnNumber; m_ttlCoupon.usCpnNumber = couponNo; return oldCoupon; }
	short getTotalStructLine (short &sPos, CString &csLine, TtlLineType lineType);
	short getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType);

public:
    TTLCPN  m_ttlCoupon;
};
