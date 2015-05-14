#pragma once

#include "ListerCoupon.h"
#include "afxwin.h"

// CDialogCoupon dialog

class CDialogCoupon : public CDialog
{
	DECLARE_DYNAMIC(CDialogCoupon)

public:
	CDialogCoupon(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogCoupon();

// Dialog Data
	enum { IDD = IDD_DIALOGCOUPON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListerCoupon  myList;
	CListBox m_ListBox;
};
