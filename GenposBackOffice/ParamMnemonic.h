#pragma once
#include "param.h"

#include "resource.h"

class CParamMnemonic : public CParam
{
public:
	struct MnemoSizes {
		unsigned long  ulIdPromptStart;
		unsigned short usClass;
		unsigned short usMaxCount;
		unsigned short usMaxLength;
		MnemoSizes(unsigned short xClass = 0, unsigned short xMaxCount = 0, unsigned short xMaxLen = 0, unsigned long xIdPrompt = 0) : ulIdPromptStart(xIdPrompt), usClass(xClass), usMaxCount(xMaxCount), usMaxLength(xMaxLen) { }
	};

	static const unsigned long  m_ulSignature = 0x5f4c7b2a;  // bit pattern to check on CArchive data integrity

	CParamMnemonic(void);
	virtual ~CParamMnemonic(void);
	virtual short PullParam (void) = 0;
	virtual short PullParam (unsigned short usAddress) = 0;
	virtual short PushParam (void) = 0;
	virtual short PushParam (unsigned short usAddress) = 0;
	virtual void ClearParam(void) = 0;
	virtual char * GetSqliteKey (int i) = 0;
	virtual void * GetSqliteBlob (int i) = 0;
	virtual int  GetSqliteBlobSize (int i) = 0;

	virtual void Serialize (CArchive &ar) = 0;

	virtual unsigned short GetMnemonicValue (CString &mnemonic) = 0;
	virtual unsigned short SetMnemonicValue (const CString &mnemonic) = 0;

	static unsigned short GetPromptText (unsigned short usAddress, LPWSTR mnemonic) { mnemonic[0] = 0; return 0; }
	static MnemoSizes GetMnemonicSizes (void) { return MnemoSizes (); }

public:

protected:
	SHORT       m_sLastError;
	SHORT       m_bDataRead;
};

class CParamTransaction : public CParamMnemonic
{
public:
	CParamTransaction(void);
	~CParamTransaction(void);
	short PullParam (void);
	short PullParam (unsigned short usAddress);
	short PushParam (void);
	short PushParam (unsigned short usAddress);
	void ClearParam(void);
	char * GetSqliteKey (int i) { return NULL; }
	void * GetSqliteBlob (int i) { return &abTransMnemonic[0]; }
	int  GetSqliteBlobSize (int i) { return sizeof(abTransMnemonic[0]) * PARA_TRANSMNEMO_LEN; }

	void Serialize (CArchive &ar);

	unsigned short GetMnemonicValue (CString &mnemonic);
	unsigned short SetMnemonicValue (const CString &mnemonic);

	static unsigned short GetPromptText (unsigned short usAddress, LPWSTR mnemonic);
	static MnemoSizes GetMnemonicSizes (void);

private:
	WCHAR abTransMnemonic[PARA_TRANSMNEMO_LEN + 1];

};

class CParamLeadThru : public CParamMnemonic
{
public:
	CParamLeadThru(void);
	~CParamLeadThru(void);
	short PullParam (void);
	short PullParam (unsigned short usAddress);
	short PushParam (void);
	short PushParam (unsigned short usAddress);
	void ClearParam(void);
	char * GetSqliteKey (int i) { return NULL; }
	void * GetSqliteBlob (int i) { return &abTransMnemonic[0]; }
	int  GetSqliteBlobSize (int i) { return sizeof(abTransMnemonic[0]) * PARA_TRANSMNEMO_LEN; }

	virtual void Serialize (CArchive &ar);

	unsigned short GetMnemonicValue (CString &mnemonic);
	unsigned short SetMnemonicValue (const CString &mnemonic);

	static unsigned short GetPromptText (unsigned short usAddress, LPWSTR mnemonic);
	static MnemoSizes GetMnemonicSizes (void);

private:
	WCHAR abTransMnemonic[PARA_LEADTHRU_LEN + 1];
};
