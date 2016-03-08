#pragma once
#include "param.h"

class CParamMnemonic : public CParam
{
public:
	struct sizes {
		unsigned short usMaxCount;
		unsigned short usMaxLength;
	};

	CParamMnemonic(void);
	virtual ~CParamMnemonic(void);
	virtual short PullParam (void) = 0;
	virtual short PushParam (void) = 0;
	virtual void ClearParam(void) = 0;

	virtual unsigned short GetMnemonicValue (unsigned short usAddress, CString &mnemonic) = 0;
	virtual unsigned short SetMnemonicValue (unsigned short usAddress, const CString &mnemonic) = 0;

	virtual unsigned short GetPromptText (unsigned short usAddress, CString &mnemonic) = 0;
	virtual sizes GetMnemonicSizes (void) = 0;

public:

protected:
	SHORT  m_sLastError;
	SHORT  m_bDataRead;

};

class CParamTransaction : public CParamMnemonic
{
public:
	CParamTransaction(void);
	virtual ~CParamTransaction(void);
	virtual short PullParam (void);
	virtual short PushParam (void);
	virtual void ClearParam(void);

	virtual unsigned short GetMnemonicValue (unsigned short usAddress, CString &mnemonic);
	virtual unsigned short SetMnemonicValue (unsigned short usAddress, const CString &mnemonic);

	virtual unsigned short GetPromptText (unsigned short usAddress, CString &mnemonic);
	virtual sizes GetMnemonicSizes (void);

private:
	WCHAR abTransMnemonic[MAX_TRANSM_NO][20];

};

class CParamLeadThru : public CParamMnemonic
{
public:
	CParamLeadThru(void);
	virtual ~CParamLeadThru(void);
	virtual short PullParam (void);
	virtual short PushParam (void);
	virtual void ClearParam(void);

	virtual unsigned short GetMnemonicValue (unsigned short usAddress, CString &mnemonic);
	virtual unsigned short SetMnemonicValue (unsigned short usAddress, const CString &mnemonic);

	virtual unsigned short GetPromptText (unsigned short usAddress, CString &mnemonic);
	virtual sizes GetMnemonicSizes (void);

private:
	WCHAR abTransMnemonic[MAX_LEAD_NO][20];

};
