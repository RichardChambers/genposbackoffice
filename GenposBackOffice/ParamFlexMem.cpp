#include "StdAfx.h"
#include "ParamFlexMem.h"

CParamFlexMem::CParamFlexMem(void)
{
	memset (m_paraFlexMem, 0, sizeof(m_paraFlexMem));
}

CParamFlexMem::~CParamFlexMem(void)
{
}

short CParamFlexMem::PullParam (void)
{
	USHORT  usReadOffset = 0;
	USHORT  usActualRead = 0;

	m_sLastError = ::CliParaAllRead (CLASS_PARAFLEXMEM, (UCHAR *)m_paraFlexMem, sizeof( m_paraFlexMem ), usReadOffset, &usActualRead);
	m_bDataRead = (m_sLastError == 0);
	return m_sLastError;
}

short CParamFlexMem::PushParam (void)
{
	USHORT  usReadOffset = 0;
	USHORT  usActualRead = 0;

	m_sLastError = ::CliParaAllWrite (CLASS_PARAFLEXMEM, (UCHAR *)m_paraFlexMem, sizeof( m_paraFlexMem ), usReadOffset, &usActualRead);
	return m_sLastError;
}

short CParamFlexMem::SummaryToText (CString &csMemo)
{
	wchar_t *pFormat = L"Guest Check System:\n\t%s \nMax # of Guest Checks\t\t\t%8d\t \n\tMax # of Items in G.C.\t\t%8d\t \n\tMax # of Items in Transaction\t%8d\n \nMax # of Departments\t\t\t%8d \n\tPTD - %d \nMax # of PLU\t\t\t\t%8d \n\tPTD - %d \nMax # of Operators\t\t\t%8d \n\tPTD - %d \nMax # of Coupons\t\t\t%8d \n\tPTD - %d \nMax # of EJ\t\t\t\t%8d \n\tO/R - %d \nMax # of Employees\t\t\t%8d \nMax # of Control Strings\t\t\t%8d \nMax # of PPI\t\t\t\t%8d \nProgrammable Report Size\t\t%8d";
	wchar_t *szGCSys, *pGcSystem [] = {
		L"Pre-GuestCheck Buffering",
		L"Pre-GuestCheck UnBuffering",
		L"Post GuestCheck Buffering",
		L"Store/Recall Buffering",
		L""
	};

	int  nGcSysMax = sizeof(pGcSystem)/sizeof(pGcSystem[0]);
	int  nGcSysType = m_paraFlexMem[8].uchPTDFlag;
	szGCSys = (nGcSysType < nGcSysMax) ? pGcSystem[nGcSysType] : pGcSystem[nGcSysMax - 1];

	csMemo.Format (pFormat,
		   	  szGCSys,
			  m_paraFlexMem[8].ulRecordNumber,
			  m_paraFlexMem[7].ulRecordNumber,
			  m_paraFlexMem[6].ulRecordNumber,
			  m_paraFlexMem[0].ulRecordNumber,
			  m_paraFlexMem[0].uchPTDFlag,
			  m_paraFlexMem[1].ulRecordNumber,
			  m_paraFlexMem[1].uchPTDFlag,
			  m_paraFlexMem[3].ulRecordNumber,
			  m_paraFlexMem[3].uchPTDFlag,
			  m_paraFlexMem[9].ulRecordNumber,
			  m_paraFlexMem[9].uchPTDFlag,
			  m_paraFlexMem[4].ulRecordNumber,
              m_paraFlexMem[4].uchPTDFlag,
			  m_paraFlexMem[5].ulRecordNumber,
			  m_paraFlexMem[10].ulRecordNumber,
			  m_paraFlexMem[12].ulRecordNumber,
			  m_paraFlexMem[11].ulRecordNumber);

	return 0;
}

void CParamFlexMem::Serialize (CArchive &ar)
{
	UCHAR* pBuff = (UCHAR*) &m_paraFlexMem;

	if (ar.IsStoring())
	{
		ar << sizeof(m_paraFlexMem);
		for(int i = 0; i < sizeof(m_paraFlexMem); i++){
			ar<<pBuff[i];
		}
	}
	else
	{
		m_bDataRead = 1;

		ULONG mySize;
		memset(&m_paraFlexMem, 0, sizeof(m_paraFlexMem));
		ar>>mySize;

		// check if the object stored is larger than the object in the
		// version of the application being used to prevent
		// overwrite memory and cause application failure.
		ULONG  xMySize = mySize;
		UCHAR  ucTemp;

		if (xMySize > sizeof (m_paraFlexMem)) {
			xMySize = sizeof (m_paraFlexMem);
		}
		UINT y = 0;
		for(y = 0; y < xMySize;y++){
			ar>>pBuff[y];
		}
		for(; y < mySize;y++){
			ar>>ucTemp;
		}
	}
}