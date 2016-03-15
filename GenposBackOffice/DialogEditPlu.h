#pragma once

#include "TabCtrlDialog.h"

#include "ParamPlu.h"

// CDialogEditPlu dialog

class CDialogEditPlu : public CDialog
{
	DECLARE_DYNAMIC(CDialogEditPlu)

public:
	CDialogEditPlu(CWnd* pParent = NULL);   // standard constructor
	CDialogEditPlu(CParamPlu &myPlu);
	virtual ~CDialogEditPlu();

// Dialog Data
	enum { IDD = IDD_DIALOGEDITPLU };

	CParamPlu  m_paramPlu;

	struct TabToStatus {
		short  sTabItem;
		int    iDlgItem;
		short  sOffset;
		UCHAR  uchBit;
	};

	static const struct TabToStatus m_TabItemOneStatus[];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnTcnSelchangeTabControlEditStatus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangingTabControlEditStatus(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
public:
	CString m_displayMnemonic;
	CTabCtrlDialog m_TabCtrl;

	TCITEM  m_TabItem[8];          // tab control tabs array.  first element not used.

};
