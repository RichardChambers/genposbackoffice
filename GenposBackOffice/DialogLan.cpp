// DialogLan.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "GenposBackOfficeDoc.h"
#include "DialogLan.h"


// CDialogLan dialog

IMPLEMENT_DYNAMIC(CDialogLan, CDialog)

CDialogLan::CDialogLan(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogLan::IDD, pParent)
{

}

CDialogLan::~CDialogLan()
{
}

void CDialogLan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOSTNAME, m_LanData.m_csHostName);
	DDV_MaxChars(pDX, m_LanData.m_csHostName, 16);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_LanData.m_csHostSessionPassword);
	DDV_MaxChars(pDX, m_LanData.m_csHostSessionPassword, 10);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_LanData.m_dwHostSessionIpAddress);
	DDX_Text(pDX, IDC_EDIT_HOSTMEMO, m_LanData.m_csHostMemo);

	if (pDX->m_bSaveAndValidate) {
		CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
		m_LanData.m_bUseIpAddress = p->GetCheck();
		p = (CButton *)GetDlgItem (IDC_CHECK_SAVE_PW);
		m_LanData.m_bSavePassword = p->GetCheck();
	} else {
		CButton *p = (CButton *)GetDlgItem (IDC_CHECK_USE_IP_ADDRESS);
		p->SetCheck (m_LanData.m_bUseIpAddress);
		p = (CButton *)GetDlgItem (IDC_CHECK_SAVE_PW);
		p->SetCheck (m_LanData.m_bSavePassword);
	}
}


BEGIN_MESSAGE_MAP(CDialogLan, CDialog)
END_MESSAGE_MAP()


// CDialogLan message handlers
