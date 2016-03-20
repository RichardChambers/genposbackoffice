#pragma once


// CDialogTenderKeyEdit dialog

class CDialogTenderKeyEdit : public CDialog
{
	DECLARE_DYNAMIC(CDialogTenderKeyEdit)

public:
	CDialogTenderKeyEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTenderKeyEdit();

// Dialog Data
	enum { IDD = IDD_DIALOGTENDEREDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
