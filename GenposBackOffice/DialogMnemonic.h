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

	CParamMnemonic *m_MnemonicList;

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
