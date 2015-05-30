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

	CListerCoupon  *SetListCoupon (CListerCoupon  *p) { CListerCoupon  *pSave = m_myList; m_myList = p; return pSave; }
// Dialog Data
	enum { IDD = IDD_DIALOGCOUPON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListerCoupon  *m_myList;
	CListBox m_ListBox;
};
