// DialogLanLogin.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "GenposBackOfficeDoc.h"
#include "DialogLanLogin.h"


// CDialogLanLogin dialog

IMPLEMENT_DYNAMIC(CDialogLanLogin, CDialog)

CDialogLanLogin::CDialogLanLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogLanLogin::IDD, pParent)
{

}

CDialogLanLogin::~CDialogLanLogin()
{
}

void CDialogLanLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOSTNAME, m_LanData.m_csHostName);
	DDV_MaxChars(pDX, m_LanData.m_csHostName, 16);
	DDX_Text(pDX, IDC_EDIT_TERM_NO, m_LanData.m_csLastTermNo);
	DDV_MaxChars(pDX, m_LanData.m_csLastTermNo, 2);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_LanData.m_csHostSessionPassword);
	DDV_MaxChars(pDX, m_LanData.m_csHostSessionPassword, 10);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_LanData.m_dwHostSessionIpAddress);

	if (pDX->m_bSaveAndValidate) {
		CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
		m_LanData.m_bUseIpAddress = p->GetCheck();
		if (m_LanData.m_bUseIpAddress) {
			BYTE f1, f2, f3, f4;
			CIPAddressCtrl *p2 = (CIPAddressCtrl *)GetDlgItem (IDC_IPADDRESS1);
			p2->GetAddress(f1, f2, f3, f4);
			m_LanData.m_csHostSession.Format (_T("%d.%d.%d.%d"), f1, f2, f3, f4);
		} else {
			m_LanData.m_csHostSession.Format (_T("%s-%s"), m_LanData.m_csHostName, m_LanData.m_csLastTermNo);
		}
	} else {
		CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
		p->SetCheck (m_LanData.m_bUseIpAddress);
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
