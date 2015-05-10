#pragma once
#include "afxwin.h"


// CDialogLan dialog

class CDialogLan : public CDialog
{
	DECLARE_DYNAMIC(CDialogLan)

public:
	CDialogLan(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogLan();

// Dialog Data
	enum { IDD = IDD_DIALOGLAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_csHostName;
	CString m_csHostMemo;
};
