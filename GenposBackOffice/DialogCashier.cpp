// DialogCashier.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogCashier.h"
#include "DialogCashierEdit.h"

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
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CDialogCashier::OnBnClickedButtonEdit)
END_MESSAGE_MAP()


// CDialogCashier message handlers

void CDialogCashier::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here

	int iSel = m_ListBox.GetCurSel ();

	if (iSel != LB_ERR) {
		CDialogCashierEdit myDialog;

		myDialog.DoModal ();
	}
}
