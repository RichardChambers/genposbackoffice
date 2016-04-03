#pragma once
#include "param.h"

class CParamCoupon : public CParam
{
public:
	CParamCoupon(CouponNo couponNo = 0);
	~CParamCoupon(void);

	short PullParam (void);
	short PullParam (CouponNo couponNo);
	short PushParam (void);
	void ClearParam(void) { memset (&m_paraCoupon, 0, sizeof(m_paraCoupon)); m_bDataRead = 0; }
	CouponNo setParamCashier (CouponNo couponNo) { CouponNo oldCoupon = m_paraCoupon.uchCpnNo; m_paraCoupon.uchCpnNo = couponNo; return oldCoupon; }
	char * GetSqliteKey (int i) { return NULL; }
	void * GetSqliteBlob (int i) { return NULL; }
	int  GetSqliteBlobSize (int i) { return 0; }

public:
	CPNIF    m_paraCoupon;
};
