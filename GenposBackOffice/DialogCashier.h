#pragma once
#include "afxwin.h"

#include "ListerCashier.h"

// CDialogCashier dialog

class CDialogCashier : public CDialog
{
	DECLARE_DYNAMIC(CDialogCashier)

public:
	CDialogCashier(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogCashier();

// Dialog Data
	enum { IDD = IDD_DIALOGCASHIER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	CListerCashier  myList;
};
