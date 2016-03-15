
#include "stdafx.h"
#include "TabCtrlDialog.h"


/*
 *  InsertItemDialogTemplate ()
 *
 *  Insert into a tab control a tab pane based on the specified dialog template.  The
 *  dialog template describes what the tab pane looks like so far as controls, etc.
 *
 *  NOTE: The STYLE description must be WS_CHILD and not WS_POPUP.  Also the dialog
 *        needs to have as its top coordinate some distance in pixels so that the
 *        various tab descriptions are visible.  For instance an example dialog
 *        template in the resource file may look like:
 *            IDD_CASHIER_TAB_ONE DIALOGEX 0, 10, 178, 113
 *            STYLE DS_SETFONT | DS_FIXEDSYS | WS_CHILD
 *            FONT 8, "MS Shell Dlg", 400, 0, 0x1
 *            BEGIN
 *                LTEXT           "Dialog Tab one",IDC_STATIC,6,44,90,17
 *            END
 *
**/
CTabCtrlDialog::CTabCtrlDialog() {
	for (int i = 0; i < 10; i++) {
		m_pDialogData[i].pDialog = 0;
	}
}

CTabCtrlDialog::~CTabCtrlDialog() {
	for (int i = 0; i < 10; i++) {
		if (m_pDialogData[i].pDialog) delete m_pDialogData[i].pDialog;
	}
}


void CTabCtrlDialog::InsertItemDialogTemplate (UINT nIDTemplate, int nItem, TCITEM* pTabCtrlItem)
{
	InsertItem (nItem, pTabCtrlItem);
	m_pDialogData[nItem].nIDTemplate = nIDTemplate;
	m_pDialogData[nItem].pDialog = new CDialog ();
	if (m_pDialogData[nItem].pDialog) {
		m_pDialogData[nItem].pDialog->Create (nIDTemplate, this);
		m_pDialogData[nItem].pDialog->ShowWindow (FALSE);
	}
}


int CEditInt::GetWindowTextAsInt (void)
{
	CString csJ;
	GetWindowText (csJ);
	return _ttoi (csJ);
}

void CEditInt::SetWindowTextAsInt (int iValue)
{
	CString csJ;
	csJ.Format (_T("%d"), iValue);
	SetWindowText (csJ);
}
