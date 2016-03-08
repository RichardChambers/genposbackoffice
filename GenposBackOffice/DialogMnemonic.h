#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "ParamMnemonic.h"

// CDialogMnemonic dialog

class CDialogMnemonic : public CDialog
{
	DECLARE_DYNAMIC(CDialogMnemonic)

public:
	CDialogMnemonic(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogMnemonic();
	CDialogMnemonic(CParamMnemonic *para, CWnd* pParent = NULL);

// Dialog Data
	enum { IDD = IDD_DIALOGMNEMONIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CParamMnemonic *m_para;

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
