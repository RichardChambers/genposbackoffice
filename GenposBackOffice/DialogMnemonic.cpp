// DialogMnemonic.cpp : implementation file
//

#include "stdafx.h"

#include <Commctrl.h>

#include "GenposBackOffice.h"
#include "DialogMnemonic.h"


// CDialogMnemonic dialog

IMPLEMENT_DYNAMIC(CDialogMnemonic, CDialog)

CDialogMnemonic::CDialogMnemonic(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMnemonic::IDD, pParent), m_MnemonicList(0)
{

}

CDialogMnemonic::CDialogMnemonic(CListerMnemonic *para, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMnemonic::IDD, pParent), m_MnemonicList(para)
{

}

CDialogMnemonic::~CDialogMnemonic()
{
}

void CDialogMnemonic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);

	if (!pDX->m_bSaveAndValidate) {
		LVCOLUMN lvColumn;
		int nCol;

		m_listctrl.SetExtendedStyle (m_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

		lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.cx = 160;
		lvColumn.pszText = L"Prompt";
		nCol = m_listctrl.InsertColumn(0, &lvColumn);

		lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.cx = 160;
		lvColumn.pszText = L"Mnemonic";
		m_listctrl.InsertColumn(1, &lvColumn);

		LVITEM lvItem = {0};
		int nItem;

		WCHAR   wcsPrompt[128];
		CString csMnemonic;
		unsigned short usAddress = 1;

		for (CListerMnemonic *p = m_MnemonicList; p && p->GetPromptText (usAddress, wcsPrompt); ) {
			p->GetMnemonicValue (usAddress, csMnemonic);
			lvItem.mask = LVIF_TEXT;
			lvItem.iItem = usAddress;
			lvItem.iSubItem = 0;
			lvItem.pszText = wcsPrompt;
			nItem = m_listctrl.InsertItem(&lvItem);

			m_listctrl.SetItemText(nItem, 1, csMnemonic);
			usAddress++;
		}
	}
}


BEGIN_MESSAGE_MAP(CDialogMnemonic, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDialogMnemonic::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CDialogMnemonic message handlers


void CDialogMnemonic::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		*pResult = 0;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
