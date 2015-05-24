// DialogPlu.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogPlu.h"
#include "DialogEditPlu.h"


// CDialogPlu dialog

IMPLEMENT_DYNAMIC(CDialogPlu, CDialog)

CDialogPlu::CDialogPlu(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPlu::IDD, pParent)
{

}

CDialogPlu::~CDialogPlu()
{
}

void CDialogPlu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PLU, m_ListBox);
	if (!pDX->m_bSaveAndValidate) {
		myList.RetrieveList ();
		int  iItem, iItemCount;
		iItemCount = myList.PluDataList.GetCount ();
		for (iItem = 0; iItem < iItemCount; iItem++) {
			CParamPlu::ParamPluKey jj = myList.PluDataList.GetAt(iItem);
			jj.auchPluNo[13] = 0;   // eliminate check sum digit
			CString listItem;
			listItem.Format (_T("%-13s %2d"), jj.auchPluNo, jj.uchPluAdj);
			m_ListBox.AddString (listItem);
		}
	}
}


BEGIN_MESSAGE_MAP(CDialogPlu, CDialog)
	ON_LBN_DBLCLK(IDC_LIST_PLU, &CDialogPlu::OnLbnDblclkListPlu)
END_MESSAGE_MAP()


// CDialogPlu message handlers

void CDialogPlu::OnLbnDblclkListPlu()
{
	int iItem = m_ListBox.GetCurSel ();
	CParamPlu::ParamPluKey tempPluKey = myList.PluDataList.GetAt(iItem);
	CParamPlu myPlu;

	myPlu.PullParam (tempPluKey);
	CDialogEditPlu myEdit (myPlu);

	if (myEdit.DoModal () == IDOK) {
		myPlu.m_paraPlu[0] = myEdit.m_paramPlu.m_paraPlu[0];
		myPlu.PushParam ();
	}
}
