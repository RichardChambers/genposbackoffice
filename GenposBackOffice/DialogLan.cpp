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
{

}

CDialogLan::~CDialogLan()
{
}

void CDialogLan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOSTNAME, m_csHostName);
	DDX_Text(pDX, IDC_EDIT_HOSTMEMO, m_csHostMemo);
}


BEGIN_MESSAGE_MAP(CDialogLan, CDialog)
END_MESSAGE_MAP()


// CDialogLan message handlers
