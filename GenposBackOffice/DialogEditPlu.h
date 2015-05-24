#pragma once

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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_displayMnemonic;
};
