#include "StdAfx.h"
#include "TotalCashier.h"

CTotalCashier::CTotalCashier(CTotal::TtlType type, CashierId cashierNo /* = 0 */) : CTotal(CLASS_TTLCASHIER, type)
{
	m_ttlCashier.ulCashierNumber = cashierNo;
	m_mdcResetInd = NOT_EOD;
	m_mdcResetEndOfDay = EOD_COUPON;
}

CTotalCashier::~CTotalCashier(void)
{
}