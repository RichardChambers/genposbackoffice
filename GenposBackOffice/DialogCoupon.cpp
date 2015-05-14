// DialogCoupon.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogCoupon.h"


// CDialogCoupon dialog

IMPLEMENT_DYNAMIC(CDialogCoupon, CDialog)

CDialogCoupon::CDialogCoupon(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCoupon::IDD, pParent)
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
		myList.RetrieveList ();
		for (myList.GetFirstListItem(); myList.bCouponData; myList.GetNextListItem ()) {
			CString listItem;
			listItem.Format (_T("%8d : %-20s"), myList.CouponData.m_paraCoupon.uchCpnNo, myList.CouponData.m_paraCoupon.ParaCpn.aszCouponMnem);
			m_ListBox.AddString (listItem);
		}
	}
}


BEGIN_MESSAGE_MAP(CDialogCoupon, CDialog)
END_MESSAGE_MAP()


// CDialogCoupon message handlers
