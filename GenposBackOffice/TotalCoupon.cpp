#include "StdAfx.h"
#include "TotalCoupon.h"

CTotalCoupon::CTotalCoupon(CTotal::TtlType type, CouponNo couponNo /* = 0 */) : CTotal(CLASS_TTLCPN, type)
{
	m_ttlCoupon.usCpnNumber = couponNo;
	m_mdcResetInd = NOT_EOD;
	m_mdcResetEndOfDay = EOD_COUPON;
}

CTotalCoupon::~CTotalCoupon(void)
{
}
