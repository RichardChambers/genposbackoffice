
// Dialog utility classes

#pragma once
#include "afxwin.h"


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


class CEditInt : public CEdit
{
public:
	int GetWindowTextAsInt (void);
	void SetWindowTextAsInt (int iValue);
};
