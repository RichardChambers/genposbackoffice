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
}

CParamTransaction::~CParamTransaction(void)
{
}

short CParamTransaction::PullParam (void)
{
	USHORT  usReadOffset = 0;
	USHORT  usActualRead = 0;

	for (int iLoop = 0; iLoop < MAX_TRANSM_NO; iLoop++) {
		m_sLastError = ::CliParaAllRead (CLASS_PARATRANSMNEMO, (UCHAR *)(&abTransMnemonic[iLoop][0]), sizeof( abTransMnemonic[iLoop] ), usReadOffset, &usActualRead);
		usReadOffset += usActualRead;
	}
	m_bDataRead = 1;
	return m_sLastError;
}

short CParamTransaction::PushParam (void)
{
	USHORT  usWriteOffset = 0;
	USHORT  usActualWrite = 0;

	for (int iLoop = 0; iLoop < MAX_TRANSM_NO; iLoop++) {
		m_sLastError = ::CliParaAllWrite (CLASS_PARATRANSMNEMO, (UCHAR *)(&abTransMnemonic[iLoop][0]), sizeof( abTransMnemonic[iLoop] ), usWriteOffset, &usActualWrite);
		usWriteOffset += usActualWrite;
	}
	return m_sLastError;
}

void CParamTransaction::ClearParam (void)
{
	memset (abTransMnemonic, 0, sizeof( abTransMnemonic ));
}

unsigned short CParamTransaction::GetMnemonicValue (unsigned short usAddress, CString &mnemonic)
{
	WCHAR  tempBuf[20 + 1] = {0};

	memcpy (tempBuf, abTransMnemonic[usAddress], 20 * sizeof(WCHAR));
	mnemonic = tempBuf;
	return 0;
}

unsigned short CParamTransaction::SetMnemonicValue (unsigned short usAddress, const CString &mnemonic)
{
	WCHAR  tempBuf[20 + 1] = {0};

	wcsncpy (tempBuf, mnemonic, 20);
	memcpy (abTransMnemonic[usAddress], tempBuf, 20 * sizeof(WCHAR));
	return 0;
}

unsigned short CParamTransaction::GetPromptText (unsigned short usAddress, CString &mnemonic)
{

	return 0;
}

CParamMnemonic::sizes CParamTransaction::GetMnemonicSizes (void)
{
	CParamMnemonic::sizes n = {MAX_TRANSM_NO, 20};

	return n;
}


// -----------------------------------------------------------------------------------------

CParamLeadThru::CParamLeadThru(void)
{
}

CParamLeadThru::~CParamLeadThru(void)
{
}

short CParamLeadThru::PullParam (void)
{
	USHORT  usReadOffset = 0;
	USHORT  usActualRead = 0;

	for (int iLoop = 0; iLoop < MAX_LEAD_NO; iLoop++) {
		m_sLastError = ::CliParaAllRead (CLASS_PARALEADTHRU, (UCHAR *)(&abTransMnemonic[iLoop][0]), sizeof( abTransMnemonic[iLoop] ), usReadOffset, &usActualRead);
		usReadOffset += usActualRead;
	}
	m_bDataRead = 1;
	return m_sLastError;
}

short CParamLeadThru::PushParam (void)
{
	USHORT  usWriteOffset = 0;
	USHORT  usActualWrite = 0;

	for (int iLoop = 0; iLoop < MAX_LEAD_NO; iLoop++) {
		m_sLastError = ::CliParaAllWrite (CLASS_PARALEADTHRU, (UCHAR *)(&abTransMnemonic[iLoop][0]), sizeof( abTransMnemonic[iLoop] ), usWriteOffset, &usActualWrite);
		usWriteOffset += usActualWrite;
	}
	return m_sLastError;
}

void CParamLeadThru::ClearParam (void)
{
	memset (abTransMnemonic, 0, sizeof( abTransMnemonic ));
}

unsigned short CParamLeadThru::GetMnemonicValue (unsigned short usAddress, CString &mnemonic)
{
	WCHAR  tempBuf[20 + 1] = {0};

	memcpy (tempBuf, abTransMnemonic[usAddress], 20 * sizeof(WCHAR));
	mnemonic = tempBuf;
	return 0;
}

unsigned short CParamLeadThru::SetMnemonicValue (unsigned short usAddress, const CString &mnemonic)
{
	WCHAR  tempBuf[20 + 1] = {0};

	wcsncpy (tempBuf, mnemonic, 20);
	memcpy (abTransMnemonic[usAddress], tempBuf, 20 * sizeof(WCHAR));
	return 0;
}

unsigned short CParamLeadThru::GetPromptText (unsigned short usAddress, CString &mnemonic)
{

	return 0;
}

CParamMnemonic::sizes CParamLeadThru::GetMnemonicSizes (void)
{
	CParamMnemonic::sizes n = {MAX_TRANSM_NO, 20};

	return n;
}
