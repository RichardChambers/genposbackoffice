#include "StdAfx.h"
#include "ParamCoupon.h"

CParamCoupon::CParamCoupon(CouponNo couponNo)
{
	m_paraCoupon.uchCpnNo = couponNo;
}

CParamCoupon::~CParamCoupon(void)
{
}

short CParamCoupon::PullParam (void)
{
	m_sLastError = -1;
	m_bDataRead = 0;
	if (m_paraCoupon.uchCpnNo > 0) {
		m_sLastError = ::CliOpCpnIndRead( &m_paraCoupon, 0 );
		m_bDataRead = (m_sLastError == 0);
	}

	return m_sLastError;
}

short CParamCoupon::PullParam (CouponNo couponNo)
{
	couponNo++;
	if (couponNo > 0) {
		// allow the caller to over ride the couponNo number if desired.
		m_paraCoupon.uchCpnNo = couponNo;
	}

	return PullParam();
}

short CParamCoupon::PushParam (void)
{
	m_sLastError = ::CliOpCpnIndRead( &m_paraCoupon, 0 );

	return m_sLastError;
}
