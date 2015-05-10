#pragma once


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
	CString m_csHostName;
	CString m_csTermNo;
	CString m_csHostSession;
	afx_msg void OnBnClickedCheckUseDhcp();
	CString m_csHostPassword;
	DWORD m_dwIpAddress;
};
