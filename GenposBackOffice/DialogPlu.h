#pragma once

#include "ListerPlu.h"
#include "afxwin.h"

// CDialogPlu dialog

class CDialogPlu : public CDialog
{
	DECLARE_DYNAMIC(CDialogPlu)

public:
	CDialogPlu(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogPlu();

// Dialog Data
	enum { IDD = IDD_DIALOGPLU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	CListerPlu  myList;
	afx_msg void OnLbnDblclkListPlu();
};
