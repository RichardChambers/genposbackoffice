// DialogLan.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogLan.h"


// CDialogLan dialog

IMPLEMENT_DYNAMIC(CDialogLan, CDialog)

CDialogLan::CDialogLan(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogLan::IDD, pParent)
	, m_csHostName(_T(""))
	, m_csHostMemo(_T(""))
	, m_dwIpAddress(0)
	, m_bUseIpAddress(0)
	, m_bSavePassword(0)
{

}

CDialogLan::~CDialogLan()
{
}

void CDialogLan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOSTNAME, m_csHostName);
	DDV_MaxChars(pDX, m_csHostName, 16);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csHostPassword);
	DDV_MaxChars(pDX, m_csHostPassword, 10);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_dwIpAddress);
	DDX_Text(pDX, IDC_EDIT_HOSTMEMO, m_csHostMemo);

	if (pDX->m_bSaveAndValidate) {
		CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
		m_bUseIpAddress = p->GetCheck();
		p = (CButton *)GetDlgItem (IDC_CHECK_SAVE_PW);
		m_bSavePassword = p->GetCheck();
	} else {
		CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
		p->SetCheck (m_bUseIpAddress);
		p = (CButton *)GetDlgItem (IDC_CHECK_SAVE_PW);
		p->SetCheck (m_bSavePassword);
	}
}


BEGIN_MESSAGE_MAP(CDialogLan, CDialog)
END_MESSAGE_MAP()


// CDialogLan message handlers
