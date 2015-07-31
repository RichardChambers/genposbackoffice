#pragma once
#include "afxwin.h"


// DialogCashierEdit dialog

class CDialogCashierEdit : public CDialog
{
	DECLARE_DYNAMIC(CDialogCashierEdit)

public:
	CDialogCashierEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogCashierEdit();

// Dialog Data
	enum { IDD = IDD_DIALOGCASHIEREDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// cashier name edit
	CEdit m_csCashierName;
};
