// DialogMnemonic.cpp : implementation file
//

#include "stdafx.h"

#include <Commctrl.h>

#include "GenposBackOffice.h"
#include "DialogMnemonic.h"


// CDialogMnemonic dialog

IMPLEMENT_DYNAMIC(CDialogMnemonic, CDialog)

CDialogMnemonic::CDialogMnemonic(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMnemonic::IDD, pParent)
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
		lvColumn.cx = 120;
		lvColumn.pszText = L"Full Name";
		nCol = m_listctrl.InsertColumn(0, &lvColumn);

		lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.cx = 100;
		lvColumn.pszText = L"Profession";
		m_listctrl.InsertColumn(1, &lvColumn);

		lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.cx = 80;
		lvColumn.pszText = L"Fav Sport";
		m_listctrl.InsertColumn(2, &lvColumn);

		lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.cx = 75;
		lvColumn.pszText = L"Hobby";
		m_listctrl.InsertColumn(3, &lvColumn);

		LVITEM lvItem = {0};
		int nItem;

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = 0;
		lvItem.iSubItem = 0;
		lvItem.pszText = L"Sandra C. Anschwitz";
		nItem = m_listctrl.InsertItem(&lvItem);

		m_listctrl.SetItemText(nItem, 1, L"Singer");
		m_listctrl.SetItemText(nItem, 2, L"HandBall");
		m_listctrl.SetItemText(nItem, 3, L"Beach");

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = 1;
		lvItem.iSubItem = 0;
		lvItem.pszText = L"Roger A. Miller";
		nItem = m_listctrl.InsertItem(&lvItem);

		m_listctrl.SetItemText(nItem, 1, L"Footballer");
		m_listctrl.SetItemText(nItem, 2, L"Tennis");
		m_listctrl.SetItemText(nItem, 3, L"Teaching");

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = 2;
		lvItem.iSubItem = 0;
		lvItem.pszText = L"Marie-Julie W. Gross";
		nItem = m_listctrl.InsertItem(&lvItem);

		m_listctrl.SetItemText(nItem, 1, L"Student");
		m_listctrl.SetItemText(nItem, 2, L"Boxing");
		m_listctrl.SetItemText(nItem, 3, L"Programming");

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = 3;
		lvItem.iSubItem = 0;
		lvItem.pszText = L"Ella Pius Roger";
		nItem = m_listctrl.InsertItem(&lvItem);

		m_listctrl.SetItemText(nItem, 1, L"Architect");
		m_listctrl.SetItemText(nItem, 2, L"Ping-Pong");
		m_listctrl.SetItemText(nItem, 3, L"Songo");

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
