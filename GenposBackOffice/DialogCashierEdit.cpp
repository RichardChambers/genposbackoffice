// DialogCashierEdit.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogCashierEdit.h"


// DialogCashierEdit dialog

IMPLEMENT_DYNAMIC(CDialogCashierEdit, CDialog)

CDialogCashierEdit::CDialogCashierEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCashierEdit::IDD, pParent)
{

}

CDialogCashierEdit::~CDialogCashierEdit()
{
}

void CDialogCashierEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CASHIERNAME, m_csCashierName);
}


BEGIN_MESSAGE_MAP(CDialogCashierEdit, CDialog)
END_MESSAGE_MAP()


// DialogCashierEdit message handlers
