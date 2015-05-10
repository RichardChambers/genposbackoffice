// DialogLanLogin.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogLanLogin.h"


// CDialogLanLogin dialog

IMPLEMENT_DYNAMIC(CDialogLanLogin, CDialog)

CDialogLanLogin::CDialogLanLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogLanLogin::IDD, pParent)
	, m_csHostName(_T(""))
	, m_csTermNo(_T("1"))
	, m_csHostPassword(_T(""))
	, m_dwIpAddress(0)
{

}

CDialogLanLogin::~CDialogLanLogin()
{
}

void CDialogLanLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_HOSTNAME, m_csHostName);
	DDX_Text(pDX, IDC_EDIT_TERM_NO, m_csTermNo);
	DDV_MaxChars(pDX, m_csTermNo, 2);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csHostPassword);
	DDV_MaxChars(pDX, m_csHostPassword, 10);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_dwIpAddress);

	if (pDX->m_bSaveAndValidate) {
		CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
		if (p->GetCheck()) {
			BYTE f1, f2, f3, f4;
			CIPAddressCtrl *p2 = (CIPAddressCtrl *)GetDlgItem (IDC_IPADDRESS1);
			p2->GetAddress(f1, f2, f3, f4);
			m_csHostSession.Format (_T("%d.%d.%d.%d"), f1, f2, f3, f4);
		} else {
			m_csHostSession.Format (_T("%s-%s"), m_csHostName, m_csTermNo);
		}
	}
}


BEGIN_MESSAGE_MAP(CDialogLanLogin, CDialog)
	ON_BN_CLICKED(IDC_CHECK_USE_IP_ADDRESS, &CDialogLanLogin::OnBnClickedCheckUseDhcp)
END_MESSAGE_MAP()


// CDialogLanLogin message handlers

void CDialogLanLogin::OnBnClickedCheckUseDhcp()
{
	CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
	CIPAddressCtrl *p2 = (CIPAddressCtrl *)GetDlgItem (IDC_IPADDRESS1);
	p2->EnableWindow(p->GetCheck ());
}
