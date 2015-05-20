#include "StdAfx.h"
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

#define CTOTALCASHIEROFFSET(x) #x , (int)&(((TTLCASHIER *)NULL)->x)

const CTotalCashier::CTotalCashierText CTotalCashier::transtable[] = {
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

	if (iPos < sizeof(CTotalCashier::transtable)/sizeof(CTotalCashier::transtable[0])) {
		ULONG  ulValue = *((ULONG *) (((UCHAR *)&m_ttlCashier) + CTotalCashier::transtable[iPos].iOffset));
		TOTAL  totValue = *((TOTAL *) (((UCHAR *)&m_ttlCashier) + CTotalCashier::transtable[iPos].iOffset));
		int    iType = CTotalCashier::transtable[iPos].iType;
		CString  csLineString;  csLineString.LoadString(CTotalCashier::transtable[iPos].idString);
		char     *aszTag = transtable[iPos].aszTag;

		switch (lineType)
		{
			case TtlLineTypeText:
				switch (iType) {
					case CTotal::TtlVarTypeLong:
						csLine.Format(_T("%-25s  %8d"), csLineString, ulValue);
						break;
					case CTotal::TtlVarTypeTotal:
						csLine.Format(_T("%-25s  %8d   %6d"), csLineString, totValue.lAmount, totValue.sCounter);
						break;
				}
				sRetStatus = 0;
				break;
			case TtlLineTypeTextXml:
				sRetStatus = 0;
				break;
			case TtlLineTypeTextJson:
				switch (iType) {
					case CTotal::TtlVarTypeLong:
						csLine.Format(_T("{\"%S\" : %8d}"), aszTag, ulValue);
						break;
					case CTotal::TtlVarTypeTotal:
						csLine.Format(_T("{ \"%S\" : { \"lAmount\" : %8d, \"sCount\" : %6d } }"), aszTag, totValue.lAmount, totValue.sCounter);
						break;
				}
				sRetStatus = 0;
				break;
			case TtlLineTypeTextCsv:
				switch (iType) {
					case CTotal::TtlVarTypeLong:
						csLine.Format(_T("%S, %8d}"), aszTag, ulValue);
						break;
					case CTotal::TtlVarTypeTotal:
						csLine.Format(_T("%S, %8d, %6d"), aszTag, totValue.lAmount, totValue.sCounter);
						break;
				}
				sRetStatus = 0;
				break;
		}
	}

	return sRetStatus;
}

short CTotalCashier::getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType)
{
	short  sPos = 0;

	for (sPos = 0; sPos < sizeof(CTotalCashier::transtable)/sizeof(CTotalCashier::transtable[0]); sPos++) {
		if (CTotalCashier::transtable[sPos].idString == idsPos) {
			return getTotalStructLine (sPos, csLine, lineType);
		}
	}

	return -1;
}