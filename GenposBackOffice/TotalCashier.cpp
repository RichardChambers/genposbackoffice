#include "StdAfx.h"
#include <stddef.h>

#include "TotalCashier.h"
#include "Resource.h"

CTotalCashier::CTotalCashier(CTotal::TtlType type, CashierId cashierNo /* = 0 */) : CTotal(CLASS_TTLCASHIER, type)
{
	m_ttlCashier.ulCashierNumber = cashierNo;
	m_mdcResetInd = NOT_EOD;
	m_mdcResetEndOfDay = EOD_COUPON;
}

CTotalCashier::~CTotalCashier(void)
{
}

#define CTOTALCASHIEROFFSET(x) #x , offsetof(TTLCASHIER, x)

const CTotalCashier::CTotalText CTotalCashier::transtable[] = {
	{IDS_TOTALCASHIER_CASHIER_NO, CTotal::TtlVarTypeLong, CTOTALCASHIEROFFSET(ulCashierNumber)},
	{IDS_TOTALCASHIER_PLUSVOID, CTotal::TtlVarTypeTotal, CTOTALCASHIEROFFSET(PlusVoid)},
	{IDS_TOTALCASHIER_PRESELECTVOID, CTotal::TtlVarTypeTotal, CTOTALCASHIEROFFSET(PreselectVoid)},
	{IDS_TOTALCASHIER_TRANSACTIONRETURN, CTotal::TtlVarTypeTotal, CTOTALCASHIEROFFSET(TransactionReturn)},
	{IDS_TOTALCASHIER_TRANSACTIONEXCHNG, CTotal::TtlVarTypeTotal, CTOTALCASHIEROFFSET(TransactionExchng)},
	{IDS_TOTALCASHIER_TRANSACTIONREFUND, CTotal::TtlVarTypeTotal, CTOTALCASHIEROFFSET(TransactionRefund)},
	{IDS_TOTALCASHIER_CONSCOUPON, CTotal::TtlVarTypeTotal, CTOTALCASHIEROFFSET(ConsCoupon)}
};

short CTotalCashier::getTotalStructLine (short &iPos, CString &csLine, CTotal::TtlLineType lineType)
{
	short  sRetStatus = -1;

	if (iPos < sizeof(transtable)/sizeof(transtable[0])) {
		TtlMember  val = *((TtlMember *) (((UCHAR *)&m_ttlCashier) + transtable[iPos].iOffset));

		CreateString (csLine, lineType, transtable[iPos], val);
		sRetStatus = 0;
	}

	return sRetStatus;
}

short CTotalCashier::getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType)
{
	short  sPos = 0;

	for (sPos = 0; sPos < sizeof(transtable)/sizeof(transtable[0]); sPos++) {
		if (transtable[sPos].idString == idsPos) {
			return getTotalStructLine (sPos, csLine, lineType);
		}
	}

	return -1;
}