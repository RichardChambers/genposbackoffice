// DialogCashier.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogCashier.h"

// CDialogCashier dialog

IMPLEMENT_DYNAMIC(CDialogCashier, CDialog)

CDialogCashier::CDialogCashier(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCashier::IDD, pParent), m_myList(0)
{

}

CDialogCashier::~CDialogCashier()
{
}

void CDialogCashier::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CASHIERS, m_ListBox);

	if (!pDX->m_bSaveAndValidate) {
		if (m_myList) {
			for (m_myList->GetFirstListItem(); m_myList->bCashierData; m_myList->GetNextListItem ()) {
				CString listItem;
				listItem.Format (_T("%8d : %-20s"), m_myList->CashierData.m_paraCashier.ulCashierNo, m_myList->CashierData.m_paraCashier.auchCashierName);
				m_ListBox.AddString (listItem);
			}
		}
	}
}


BEGIN_MESSAGE_MAP(CDialogCashier, CDialog)
END_MESSAGE_MAP()


// CDialogCashier message handlers
