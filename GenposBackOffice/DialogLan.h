#pragma once
#include "afxwin.h"
#include "afxcmn.h"


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
	CLanConnectionData  m_LanData;
};
