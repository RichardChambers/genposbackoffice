#include "StdAfx.h"
#include "TotalRegFin.h"
#include "Resource.h"

CTotalRegFin::CTotalRegFin(CTotal::TtlType type) : CTotal(CLASS_TTLREGFIN, type)
{
	m_mdcResetInd = NOT_EOD;
	m_mdcResetEndOfDay = EOD_REGFIN;
}

CTotalRegFin::~CTotalRegFin(void)
{
}

#define CTOTALREGFINOFFSET(x) #x , offsetof(TTLREGFIN, x)

const CTotalRegFin::CTotalText CTotalRegFin::transtable[] = {
	{IDS_TOTALCASHIER_PLUSVOID, CTotal::TtlVarTypeLongLong, CTOTALREGFINOFFSET(CGGTotal)},
	{IDS_TOTALCASHIER_PLUSVOID, CTotal::TtlVarTypeLong, CTOTALREGFINOFFSET(lNetTotal)},
	{IDS_TOTALCASHIER_PLUSVOID, CTotal::TtlVarTypeTotal, CTOTALREGFINOFFSET(PlusVoid)},
	{IDS_TOTALCASHIER_PRESELECTVOID, CTotal::TtlVarTypeTotal, CTOTALREGFINOFFSET(PreselectVoid)},
	{IDS_TOTALCASHIER_TRANSACTIONRETURN, CTotal::TtlVarTypeTotal, CTOTALREGFINOFFSET(TransactionReturn)},
	{IDS_TOTALCASHIER_TRANSACTIONEXCHNG, CTotal::TtlVarTypeTotal, CTOTALREGFINOFFSET(TransactionExchng)},
	{IDS_TOTALCASHIER_TRANSACTIONREFUND, CTotal::TtlVarTypeTotal, CTOTALREGFINOFFSET(TransactionRefund)},
	{IDS_TOTALCASHIER_CONSCOUPON, CTotal::TtlVarTypeTotal, CTOTALREGFINOFFSET(ConsCoupon)}
};

short CTotalRegFin::getTotalStructLine (short &iPos, CString &csLine, CTotal::TtlLineType lineType)
{
	short  sRetStatus = -1;

	if (iPos < sizeof(transtable)/sizeof(transtable[0])) {
		TtlMember  val = *((TtlMember *) (((UCHAR *)&m_ttlRegFin) + transtable[iPos].iOffset));

		CreateString (csLine, lineType, transtable[iPos], val);
		sRetStatus = 0;
	}

	return sRetStatus;
}

short CTotalRegFin::getTotalStructLine (int idsPos, CString &csLine, CTotal::TtlLineType lineType)
{
	short  sPos = 0;

	for (sPos = 0; sPos < sizeof(transtable)/sizeof(transtable[0]); sPos++) {
		if (transtable[sPos].idString == idsPos) {
			return getTotalStructLine (sPos, csLine, lineType);
		}
	}
	return -1;
}
