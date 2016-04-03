#pragma once
#include "lister.h"
#include "ParamMnemonic.h"

class CListerMnemonic :
	public CLister
{
public:
	CListerMnemonic(void);
	virtual ~CListerMnemonic(void);

	virtual  short    RetrieveList (void) = 0;
	virtual  short    RetrieveList (sqlite3 *db) = 0;
	virtual  CLister *getListObjectPtr (void) = 0;
	virtual  short    GetCurrentListItem (void) = 0;
	virtual  short    GetNextListItem (void) = 0;
	virtual  short    GetFirstListItem (void) = 0;
	virtual  short    GetCurrentListTotal(void) = 0;
	virtual  short    GetNextListTotal (void) = 0;
	virtual  short    GetFirstListTotal (void) = 0;
	virtual  short    GetCurrentListItemTotal (void) = 0;
	virtual  short    GetCurrentListTotalItem (void) = 0;

	virtual unsigned short GetMnemonicValue (unsigned short usAddress, CString &mnemonic) = 0;
	virtual unsigned short SetMnemonicValue (unsigned short usAddress, const CString &mnemonic) = 0;

	virtual unsigned short GetPromptText (unsigned short usAddress, LPWSTR mnemonic) = 0;

};

class CListerTransaction : public CListerMnemonic
{
public:
	CListerTransaction(void);
	~CListerTransaction(void);

	 short    RetrieveList (void);
	 short    RetrieveList (sqlite3 *db);
	 CLister *getListObjectPtr (void) { return this; }
	 short    GetCurrentListItem (void);
	 short    GetNextListItem (void);
	 short    GetFirstListItem (void);
	 short    GetCurrentListTotal(void);
	 short    GetNextListTotal (void);
	 short    GetFirstListTotal (void);
	 short    GetCurrentListItemTotal (void);
	 short    GetCurrentListTotalItem (void);

	unsigned short GetMnemonicValue (unsigned short usAddress, CString &mnemonic);
	unsigned short SetMnemonicValue (unsigned short usAddress, const CString &mnemonic);

	unsigned short GetPromptText (unsigned short usAddress, LPWSTR mnemonic);

private:
	CParamTransaction abTransMnemonic[MAX_TRANSM_NO];
};


class CListerLeadThru : public CListerMnemonic
{
public:
	CListerLeadThru(void);
	~CListerLeadThru(void);

	 short    RetrieveList (void);
	 short    RetrieveList (sqlite3 *db);
	 CLister *getListObjectPtr (void) { return this; }
	 short    GetCurrentListItem (void);
	 short    GetNextListItem (void);
	 short    GetFirstListItem (void);
	 short    GetCurrentListTotal(void);
	 short    GetNextListTotal (void);
	 short    GetFirstListTotal (void);
	 short    GetCurrentListItemTotal (void);
	 short    GetCurrentListTotalItem (void);

	unsigned short GetMnemonicValue (unsigned short usAddress, CString &mnemonic);
	unsigned short SetMnemonicValue (unsigned short usAddress, const CString &mnemonic);

	unsigned short GetPromptText (unsigned short usAddress, LPWSTR mnemonic);

private:
	CParamLeadThru abTransMnemonic[MAX_LEAD_NO];
};
