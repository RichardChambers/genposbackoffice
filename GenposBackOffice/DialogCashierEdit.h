#pragma once
#include "afxwin.h"

#include "R20_PC2172.h"

class CEditInt : public CEdit
{
public:
	int GetWindowTextAsInt (void);
	void SetWindowTextAsInt (int iValue);
};

class CTabCtrlDialog : public CTabCtrl
{
public:
	CTabCtrlDialog();
	~CTabCtrlDialog();
	void InsertItemDialogTemplate (UINT nIDTemplate, int nItem, TCITEM* pTabCtrlItem);

public:
	struct {
		UINT     nIDTemplate;
		CDialog  *pDialog;
	}  m_pDialogData[10];
};

// DialogCashierEdit dialog

class CDialogCashierEdit : public CDialog
{
	DECLARE_DYNAMIC(CDialogCashierEdit)

public:
	CDialogCashierEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogCashierEdit();

	BOOL  ImportCasif (CASIF *pCashier);
	BOOL  ExportCasif (CASIF *pCashier);

// Dialog Data
	enum { IDD = IDD_DIALOGCASHIEREDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CASIF   m_paraCashier;

	// cashier name edit
	CEdit m_csCashierName;
	CEditInt m_SupervisorId;
	CEditInt m_TeamNumber;
	CEditInt m_GuestCheckStart;
	CEditInt m_GuestCheckEnd;
	CTabCtrlDialog m_TabCtrl;

	TCITEM  m_TabItem[6];          // tab control tabs array.  first element not used.

	struct TabToStatus {
		short  sTabItem;
		int    iDlgItem;
		short  sOffset;
		UCHAR  uchBit;
	};

	static const struct TabToStatus m_TabItemOneStatus[];

public:
	afx_msg void OnTcnSelchangeTabCashierEditStatus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangingTabCashierEditStatus(NMHDR *pNMHDR, LRESULT *pResult);
};
