#include "StdAfx.h"
#include "ParamMnemonic.h"

CParamMnemonic::CParamMnemonic(void) :
	m_sLastError(0), m_bDataRead(0)
{
}


CParamMnemonic::~CParamMnemonic(void)
{
}

// -----------------------------------------------------------------------------------------

CParamTransaction::CParamTransaction(void)
{
	memset (abTransMnemonic, 0, sizeof(abTransMnemonic));
}

CParamTransaction::~CParamTransaction(void)
{
}

short CParamTransaction::PullParam (unsigned short usAddress)
{
	USHORT  usReadLen = PARA_TRANSMNEMO_LEN * sizeof(abTransMnemonic[0]);
	USHORT  usActualRead = 0;
	USHORT  usReadOffset = (usAddress - 1) * usReadLen;

	m_sLastError = ::CliParaAllRead (CLASS_PARATRANSMNEMO, (UCHAR *)(&abTransMnemonic[0]), usReadLen, usReadOffset, &usActualRead);
	m_bDataRead = 1;
	return m_sLastError;
}

short CParamTransaction::PullParam (void)
{
	return PullParam (1);
}

short CParamTransaction::PushParam (unsigned short usAddress)
{
	USHORT  usReadOffset = (usAddress - 1) * PARA_TRANSMNEMO_LEN;
	USHORT  usReadLen = PARA_TRANSMNEMO_LEN * sizeof(abTransMnemonic[0]);
	USHORT  usActualRead = 0;

	m_sLastError = ::CliParaAllWrite (CLASS_PARATRANSMNEMO, (UCHAR *)(&abTransMnemonic[0]), usReadLen, usReadOffset, &usActualRead);
	m_bDataRead = 1;
	return m_sLastError;
}

short CParamTransaction::PushParam (void)
{
	return PullParam (1);
}


void CParamTransaction::ClearParam (void)
{
	memset (abTransMnemonic, 0, sizeof( abTransMnemonic ));
}

void CParamTransaction::Serialize (CArchive &ar)
{
	if (ar.IsStoring())
	{
		int nMax = MAX_TRANSM_NO;
		int nLen = PARA_TRANSMNEMO_LEN;

		ar << CParamMnemonic::m_ulSignature;

		ar << nMax;
		ar << nLen;
		for (int i = 0; i < nMax; i++) {
			ar << abTransMnemonic[i];
		}
	} else {
		unsigned long ulSignature = 0;
		int nMax = 0;
		int nLen = 0;

		ar >> ulSignature;
		TRACE2(" Serialize Transaction - Read - ulSignature 0x%8.8x == 0x%8.8x\n", ulSignature, CParamMnemonic::m_ulSignature);

		ar >> nMax;
		ar >> nLen;
		TRACE2(" Serialize Transaction - Read - nMax %d nLen %d\n", nMax, nLen);

		for (int i = 0; i < nMax; i++) {
			ar >> abTransMnemonic[i];
		}
	}
}

unsigned short CParamTransaction::GetMnemonicValue (CString & mnemonic)
{
	unsigned short  usRet = 1;
	mnemonic = abTransMnemonic;
	return usRet;
}

unsigned short CParamTransaction::SetMnemonicValue (const CString &mnemonic)
{
	memset (abTransMnemonic, 0, sizeof(abTransMnemonic));
	wcsncpy (abTransMnemonic, mnemonic, PARA_TRANSMNEMO_LEN);
	return 0;
}

unsigned short CParamTransaction::GetPromptText (unsigned short usAddress, LPWSTR mnemonic)
{
	unsigned short usRet = 0;

	if (usAddress < MAX_TRANSM_NO) {
		LoadString (GetModuleHandle(NULL), usAddress + IDS_MNEMONIC_TRANSM_NO, mnemonic, 68);
		usRet = 1;
	}

	return usRet;
}

CParamMnemonic::MnemoSizes CParamTransaction::GetMnemonicSizes (void)
{
	return 	CParamMnemonic::MnemoSizes (CLASS_PARALEADTHRU, MAX_TRANSM_NO, PARA_LEADTHRU_LEN, IDS_MNEMONIC_TRANSM_NO);
}


// -----------------------------------------------------------------------------------------

CParamLeadThru::CParamLeadThru(void)
{
	memset (abTransMnemonic, 0, sizeof(abTransMnemonic));
}

CParamLeadThru::~CParamLeadThru(void)
{
}


short CParamLeadThru::PullParam (unsigned short usAddress)
{
	USHORT  usReadLen = PARA_LEADTHRU_LEN * sizeof(abTransMnemonic[0]);
	USHORT  usActualRead = 0;
	USHORT  usReadOffset = (usAddress - 1) * usReadLen;

	m_sLastError = ::CliParaAllRead (CLASS_PARALEADTHRU, (UCHAR *)(&abTransMnemonic[0]), usReadLen, usReadOffset, &usActualRead);
	m_bDataRead = 1;
	return m_sLastError;
}

short CParamLeadThru::PullParam (void)
{
	return PullParam (1);
}


short CParamLeadThru::PushParam (unsigned short usAddress)
{
	USHORT  usReadOffset = (usAddress - 1) * PARA_LEADTHRU_LEN;
	USHORT  usReadLen = PARA_LEADTHRU_LEN * sizeof(abTransMnemonic[0]);
	USHORT  usActualRead = 0;

	m_sLastError = ::CliParaAllWrite (CLASS_PARALEADTHRU, (UCHAR *)(&abTransMnemonic[0]), usReadLen, usReadOffset, &usActualRead);
	m_bDataRead = 1;
	return m_sLastError;
}

short CParamLeadThru::PushParam (void)
{
	return PushParam (1);
}

void CParamLeadThru::ClearParam (void)
{
	memset (abTransMnemonic, 0, sizeof( abTransMnemonic ));
}

void CParamLeadThru::Serialize (CArchive &ar)
{
	if (ar.IsStoring())
	{
		int nMax = MAX_LEAD_NO;
		int nLen = PARA_LEADTHRU_LEN;

		ar << CParamMnemonic::m_ulSignature;

		ar << nMax;
		ar << nLen;
		for (int i = 0; i < nMax; i++) {
			ar << abTransMnemonic[i];
		}
	} else {
		unsigned long ulSignature = 0;
		int nMax = 0;
		int nLen = 0;

		ar >> ulSignature;
		TRACE2(" Serialize Leadthru - Read - ulSignature 0x%8.8x == 0x%8.8x\n", ulSignature, CParamMnemonic::m_ulSignature);

		ar >> nMax;
		ar >> nLen;
		TRACE2(" Serialize Leadthru - Read - nMax %d nLen %d\n", nMax, nLen);

		for (int i = 0; i < nMax; i++) {
			ar >> abTransMnemonic[i];
		}
	}
}

unsigned short CParamLeadThru::GetMnemonicValue (CString &mnemonic)
{
	unsigned short usRet = 1;
	mnemonic = abTransMnemonic;
	return usRet;
}

unsigned short CParamLeadThru::SetMnemonicValue (const CString &mnemonic)
{
	memset (abTransMnemonic, 0, sizeof(abTransMnemonic));
	wcsncpy (abTransMnemonic, mnemonic, PARA_LEADTHRU_LEN);
	return 0;
}

unsigned short CParamLeadThru::GetPromptText (unsigned short usAddress, LPWSTR mnemonic)
{
	unsigned short usRet = 0;

	if (usAddress < MAX_LEAD_NO) {
		LoadString (GetModuleHandle(NULL), usAddress + IDS_MNEMONIC_LEADTHRU, mnemonic, 68);
		usRet = 1;
	}

	return usRet;
}

CParamMnemonic::MnemoSizes CParamLeadThru::GetMnemonicSizes (void)
{
	return 	CParamMnemonic::MnemoSizes (CLASS_PARALEADTHRU, MAX_LEAD_NO, PARA_LEADTHRU_LEN, IDS_MNEMONIC_LEADTHRU);
}
