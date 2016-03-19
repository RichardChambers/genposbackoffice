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
	, m_bUseIpAddress(0)
{

}

CDialogLanLogin::~CDialogLanLogin()
{
}

void CDialogLanLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOSTNAME, m_csHostName);
	DDV_MaxChars(pDX, m_csHostName, 16);
	DDX_Text(pDX, IDC_EDIT_TERM_NO, m_csTermNo);
	DDV_MaxChars(pDX, m_csTermNo, 2);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csHostPassword);
	DDV_MaxChars(pDX, m_csHostPassword, 10);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_dwIpAddress);

	if (pDX->m_bSaveAndValidate) {
		CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
		m_bUseIpAddress = p->GetCheck();
		if (m_bUseIpAddress) {
			BYTE f1, f2, f3, f4;
			CIPAddressCtrl *p2 = (CIPAddressCtrl *)GetDlgItem (IDC_IPADDRESS1);
			p2->GetAddress(f1, f2, f3, f4);
			m_csHostSession.Format (_T("%d.%d.%d.%d"), f1, f2, f3, f4);
		} else {
			m_csHostSession.Format (_T("%s-%s"), m_csHostName, m_csTermNo);
		}
	} else {
		CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
		p->SetCheck (m_bUseIpAddress);
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

BOOL CDialogLanLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
