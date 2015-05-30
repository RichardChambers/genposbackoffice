// DialogCoupon.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogCoupon.h"


// CDialogCoupon dialog

IMPLEMENT_DYNAMIC(CDialogCoupon, CDialog)

CDialogCoupon::CDialogCoupon(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCoupon::IDD, pParent), m_myList(0)
{

}

CDialogCoupon::~CDialogCoupon()
{
}

void CDialogCoupon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COUPONS, m_ListBox);
	if (!pDX->m_bSaveAndValidate) {
		if (m_myList) {
			for (m_myList->GetFirstListItem(); m_myList->bCouponData; m_myList->GetNextListItem ()) {
				CString listItem;
				listItem.Format (_T("%8d : %-20s"), m_myList->CouponData.m_paraCoupon.uchCpnNo, m_myList->CouponData.m_paraCoupon.ParaCpn.aszCouponMnem);
				m_ListBox.AddString (listItem);
			}
		}
	}
}


BEGIN_MESSAGE_MAP(CDialogCoupon, CDialog)
END_MESSAGE_MAP()


// CDialogCoupon message handlers
