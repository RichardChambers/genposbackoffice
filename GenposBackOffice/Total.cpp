#include "StdAfx.h"
#include "Total.h"

CTotal::CTotal(CTotal::TtlClass major, CTotal::TtlType type /* = CTotal::TtlTypeNone */ ) :
	m_bTotalRetrieved(FALSE), m_sLastError(0), m_ttlClass(major), m_ttlType(type)
{
}

CTotal::~CTotal(void)
{
}

int CTotal::CreateString (CString &csLine, TtlLineType lineType, const CTotalText &totalLine, const TtlMember val)
{
	int sRetStatus = -1;

	csLine.Empty();
	
	int      iType = totalLine.iType;
	CString  csLineString;  csLineString.LoadString(totalLine.idString);
	char     *aszTag = totalLine.aszTag;

	switch (lineType)
	{
		case TtlLineTypeText:
			switch (iType) {
				case CTotal::TtlVarTypeShort:
					csLine.Format(_T("%-25s  %8d"), csLineString, val.sVal);
					break;
				case CTotal::TtlVarTypeLong:
					csLine.Format(_T("%-25s  %8d"), csLineString, val.lVal);
					break;
				case CTotal::TtlVarTypeLongLong:
					csLine.Format(_T("%-25s  %8lld"), csLineString, val.llVal);
					break;
				case CTotal::TtlVarTypeTotal:
					csLine.Format(_T("%-25s  %8d   %6d"), csLineString, val.tVal.lAmount, val.tVal.sCounter);
					break;
			}
			sRetStatus = 0;
			break;
		case TtlLineTypeTextXml:
			sRetStatus = 0;
			break;
		case TtlLineTypeTextJson:
			switch (iType) {
				case CTotal::TtlVarTypeShort:
					csLine.Format(_T("{\"%S\" : %8d}"), aszTag, val.sVal);
					break;
				case CTotal::TtlVarTypeLong:
					csLine.Format(_T("{\"%S\" : %8d}"), aszTag, val.lVal);
					break;
				case CTotal::TtlVarTypeLongLong:
					csLine.Format(_T("{\"%S\" : %8lld}"), aszTag, val.llVal);
					break;
				case CTotal::TtlVarTypeTotal:
					csLine.Format(_T("{ \"%S\" : { \"lAmount\" : %8d, \"sCount\" : %6d } }"), aszTag, val.tVal.lAmount, val.tVal.sCounter);
					break;
			}
			sRetStatus = 0;
			break;
		case TtlLineTypeTextCsv:
			switch (iType) {
				case CTotal::TtlVarTypeShort:
					csLine.Format(_T("%S, %8d}"), aszTag, val.sVal);
					break;
				case CTotal::TtlVarTypeLong:
					csLine.Format(_T("%S, %8d}"), aszTag, val.lVal);
					break;
				case CTotal::TtlVarTypeLongLong:
					csLine.Format(_T("%S, %8lld}"), aszTag, val.llVal);
					break;
				case CTotal::TtlVarTypeTotal:
					csLine.Format(_T("%S, %8d, %6d"), aszTag, val.tVal.lAmount, val.tVal.sCounter);
					break;
			}
			sRetStatus = 0;
			break;
	}

	return sRetStatus;
}

short CTotal::RetrieveTotal (void)
{
	// we are using the TtlClassStruct as a standard struct since all of the
	// total structs have the same first few members
	TtlClassStruct *pTotalStruct = getTotalStructPtr ();

	pTotalStruct->uchMajorClass = m_ttlClass;
	pTotalStruct->uchMinorClass = DetermineMinorClass(m_ttlType);

	m_sLastError = ::SerTtlTotalRead( pTotalStruct );

	TRACE2("   CTotal::RetrieveTotal:  0x%x %d\n", pTotalStruct->uchMajorClass, m_sLastError);

	m_bTotalRetrieved = (m_sLastError == TTL_SUCCESS);
	return m_sLastError;
}

short CTotal::ResetTotal (void)
{
	TtlClassStruct *pTotalStruct = getTotalStructPtr ();

	pTotalStruct->uchMajorClass = m_ttlClass;
	pTotalStruct->uchMinorClass = DetermineMinorClass(m_ttlType);

    m_sLastError = ::SerTtlTotalReset(pTotalStruct, m_mdcResetInd );
	m_bTotalReset = (m_sLastError == TTL_SUCCESS);
	return m_sLastError;
}

short CTotal::ResetTotalEndOfDay (void)
{
	TtlClassStruct *pTotalStruct = getTotalStructPtr ();

	pTotalStruct->uchMajorClass = CLASS_TTLEODRESET;
	pTotalStruct->uchMinorClass = DetermineMinorClass(m_ttlType);

    m_sLastError = ::SerTtlTotalReset(pTotalStruct, m_mdcResetEndOfDay );
	m_bTotalReset = (m_sLastError == TTL_SUCCESS);
	return m_sLastError;
}

unsigned char CTotal::DetermineMinorClass (TtlType type)
{
	unsigned char  uchMinorClass = 0;

	switch (type) {
		case TtlTypeCurDay:
			uchMinorClass = CLASS_TTLCURDAY;
			break;
		case TtlTypeSaveDay:
			uchMinorClass = CLASS_TTLSAVDAY;
			break;
		case TtlTypeCurPtd:
			uchMinorClass = CLASS_TTLCURPTD;
			break;
		case TtlTypeSavePtd:
			uchMinorClass = CLASS_TTLSAVPTD;
			break;
	}

	return uchMinorClass;
}