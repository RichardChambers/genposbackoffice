#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDialogMnemonic dialog

class CDialogMnemonic : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMnemonic)

public:
	CDialogMnemonic(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogMnemonic();

// Dialog Data
	enum { IDD = IDD_DIALOGMNEMONIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listctrl;

	struct MnemonicItem {
		WCHAR   prompt[64];
		WCHAR   text[32];
	};

	struct MnemoicList {
		MnemonicItem  items[32];
		MnemonicItem * GetFirstListItem() { iOffset = 0; return items; }
		MnemonicItem * GetNextListItem() { return items + iOffset; }
		int iOffset;
	} * m_myList;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
