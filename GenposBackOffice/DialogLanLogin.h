#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDialogLanLogin dialog

class CDialogLanLogin : public CDialog
{
	DECLARE_DYNAMIC(CDialogLanLogin)

public:
	CDialogLanLogin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogLanLogin();

// Dialog Data
	enum { IDD = IDD_DIALOGLANLOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CLanConnectionData  m_LanData;
	afx_msg void OnBnClickedCheckUseDhcp();
	virtual BOOL OnInitDialog();
};
