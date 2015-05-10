#include "StdAfx.h"
#include "Total.h"

CTotal::CTotal(CTotal::TtlClass major, CTotal::TtlType type /* = CTotal::TtlTypeNone */ ) :
	m_bTotalRetrieved(FALSE), m_sLastError(0), m_ttlClass(major), m_ttlType(type)
{
}

CTotal::~CTotal(void)
{
}

short CTotal::RetrieveTotal (void)
{
	// we are using the TtlClassStruct as a standard struct since all of the
	// total structs have the same first few members
	TtlClassStruct *pTotalStruct = getTotalStructPtr ();

	pTotalStruct->uchMajorClass = m_ttlClass;
	pTotalStruct->uchMinorClass = DetermineMinorClass(m_ttlType);

	m_sLastError = ::SerTtlTotalRead( pTotalStruct );

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