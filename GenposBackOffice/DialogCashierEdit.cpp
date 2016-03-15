// DialogCashierEdit.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogCashierEdit.h"


// DialogCashierEdit dialog

IMPLEMENT_DYNAMIC(CDialogCashierEdit, CDialog)

const CDialogCashierEdit::TabToStatus CDialogCashierEdit::m_TabItemOneStatus[] = {
		{ 1, IDC_TAB_CONTROL_EDIT_ST01, 0, CAS_TRAINING_CASHIER },
		{ 1, IDC_TAB_CONTROL_EDIT_ST02, 0, CAS_NOT_GUEST_CHECK_OPEN },
		{ 1, IDC_TAB_CONTROL_EDIT_ST03, 0, CAS_NOT_NON_GUEST_CHECK },
		{ 1, IDC_TAB_CONTROL_EDIT_ST04, 0, CAS_NOT_CLOSE_OWN_CHECK },
		{ 1, IDC_TAB_CONTROL_EDIT_ST05, 0, CAS_NOT_CLOSE_ANY_CHECK },
		{ 1, IDC_TAB_CONTROL_EDIT_ST06, 0, CAS_NOT_TRANSFER_FROM },
		{ 1, IDC_TAB_CONTROL_EDIT_ST07, 0, CAS_NOT_TRANSFER_TO},
		{ 1, IDC_TAB_CONTROL_EDIT_ST08, 1, CAS_SECRET_CODE },
		{ 1, IDC_TAB_CONTROL_EDIT_ST09, 1, CAS_FINALIZE_GCF },
		{ 1, IDC_TAB_CONTROL_EDIT_ST10, 1, CAS_FINALIZE_NON_GCF },
		{ 1, IDC_TAB_CONTROL_EDIT_ST11, 1, CAS_NOT_SURROGATE },
		{ 2, IDC_TAB_CONTROL_EDIT_ST01, 1, 0x01 },
		{ 2, IDC_TAB_CONTROL_EDIT_ST02, 1, 0x01 },
		{ 2, IDC_TAB_CONTROL_EDIT_ST03, 1, CAS_USE_TEAM },
		{ 2, IDC_TAB_CONTROL_EDIT_ST04, 1, CAS_NOT_CAS_INT },
		{ 2, IDC_TAB_CONTROL_EDIT_ST05, 2, CAS_OPEN_CASH_DRAWER_SIGN_IN },
		{ 2, IDC_TAB_CONTROL_EDIT_ST06, 2, CAS_OPEN_CASH_DRAWER_SIGN_OUT },
		{ 2, IDC_TAB_CONTROL_EDIT_ST07, 2, CAS_MSR_MANUAL_SIGN_IN },
		{ 2, IDC_TAB_CONTROL_EDIT_ST08, 2, CAS_AUTO_SIGN_OUT_DISABLED },
		{ 2, IDC_TAB_CONTROL_EDIT_ST09, 2, CAS_PIN_REQIRED_FOR_SIGNIN },
		{ 2, IDC_TAB_CONTROL_EDIT_ST10, 2, CAS_PIN_REQIRED_FOR_TIMEIN },
		{ 2, IDC_TAB_CONTROL_EDIT_ST10, 3, CAS_PIN_REQIRED_FOR_SUPR }
	};

CDialogCashierEdit::CDialogCashierEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCashierEdit::IDD, pParent)
{
	m_TabItem[1].mask = TCIF_TEXT;
	m_TabItem[1].pszText = _T("Tab 1");
	m_TabItem[2].mask = TCIF_TEXT;
	m_TabItem[2].pszText = _T("Tab 2");
	m_TabItem[3].mask = TCIF_TEXT;
	m_TabItem[3].pszText = _T("Tab 3");
}

CDialogCashierEdit::~CDialogCashierEdit()
{
}

void CDialogCashierEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CASHIER_NAME, m_csCashierName);
	DDX_Control(pDX, IDC_EDIT_CASHIER_SUPNO, m_SupervisorId);
	DDX_Control(pDX, IDC_EDIT_CASHIER_TEAMNO, m_TeamNumber);
	DDX_Control(pDX, IDC_EDIT_CASHIER_GCSTART, m_GuestCheckStart);
	DDX_Control(pDX, IDC_EDIT_CASHIER_GCEND, m_GuestCheckEnd);
	DDX_Control(pDX, IDC_TAB_CONTROL_EDIT_STATUS, m_TabCtrl);
	if (pDX->m_bSaveAndValidate) {
		m_csCashierName.GetWindowText (m_paraCashier.auchCashierName, 20);
		m_paraCashier.usSupervisorID = m_SupervisorId.GetWindowTextAsInt();
		m_paraCashier.uchTeamNo = m_TeamNumber.GetWindowTextAsInt();
		m_paraCashier.usGstCheckStartNo = m_GuestCheckStart.GetWindowTextAsInt();
		m_paraCashier.usGstCheckEndNo = m_GuestCheckEnd.GetWindowTextAsInt();
		for (int i = 0; i < sizeof(m_TabItemOneStatus)/sizeof(m_TabItemOneStatus[0]); i++) {
			int iTab = m_TabItemOneStatus[i].sTabItem;
			int iDlg = m_TabItemOneStatus[i].iDlgItem;
			int iOffset = m_TabItemOneStatus[i].sOffset;
			CButton *p = (CButton *) m_TabCtrl.m_pDialogData[iTab].pDialog->GetDlgItem(iDlg);
			if (p->GetCheck()) {
				m_paraCashier.fbCashierStatus[iOffset] |= m_TabItemOneStatus[i].uchBit;
			} else {
				m_paraCashier.fbCashierStatus[iOffset] &= ~(m_TabItemOneStatus[i].uchBit);
			}
		}
	} else {
		m_csCashierName.SetWindowText(m_paraCashier.auchCashierName);
		m_SupervisorId.SetWindowTextAsInt (m_paraCashier.usSupervisorID);
		m_TeamNumber.SetWindowTextAsInt (m_paraCashier.uchTeamNo);
		m_GuestCheckStart.SetWindowTextAsInt (m_paraCashier.usGstCheckStartNo);
		m_GuestCheckEnd.SetWindowTextAsInt (m_paraCashier.usGstCheckEndNo);
		m_TabCtrl.InsertItemDialogTemplate (IDD_DIALOGCASHIEREDIT_TAB_ONE, 1, &m_TabItem[1]);
		m_TabCtrl.InsertItemDialogTemplate (IDD_DIALOGCASHIEREDIT_TAB_TWO, 2, &m_TabItem[2]);
		m_TabCtrl.InsertItemDialogTemplate (IDD_DIALOGCASHIEREDIT_TAB_THRE, 3, &m_TabItem[3]);
		for (int i = 0; i < sizeof(m_TabItemOneStatus)/sizeof(m_TabItemOneStatus[0]); i++) {
			int iTab = m_TabItemOneStatus[i].sTabItem;
			int iDlg = m_TabItemOneStatus[i].iDlgItem;
			int iOffset = m_TabItemOneStatus[i].sOffset;
			CButton *p = (CButton *) m_TabCtrl.m_pDialogData[iTab].pDialog->GetDlgItem(iDlg);
			if (m_paraCashier.fbCashierStatus[iOffset] & m_TabItemOneStatus[i].uchBit) {
				p->SetCheck (1);
			} else {
				p->SetCheck (0);
			}
		}
		m_TabCtrl.m_pDialogData[1].pDialog->ShowWindow (TRUE);
	}
}


BEGIN_MESSAGE_MAP(CDialogCashierEdit, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL_EDIT_STATUS, &CDialogCashierEdit::OnTcnSelchangeTabControlEditStatus)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_CONTROL_EDIT_STATUS, &CDialogCashierEdit::OnTcnSelchangingTabControlEditStatus)
END_MESSAGE_MAP()


// DialogCashierEdit message handlers

BOOL  CDialogCashierEdit::ImportCasif (CASIF *pCashier)
{
	m_paraCashier = *pCashier;
	return TRUE;
}

BOOL  CDialogCashierEdit::ExportCasif (CASIF *pCashier)
{
	*pCashier = m_paraCashier;
	return TRUE;
}

void CDialogCashierEdit::OnTcnSelchangeTabControlEditStatus(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	int i = TabCtrl_GetCurSel(pNMHDR->hwndFrom);
	m_TabCtrl.m_pDialogData[i + 1].pDialog->ShowWindow (TRUE);
}

void CDialogCashierEdit::OnTcnSelchangingTabControlEditStatus(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	int i = TabCtrl_GetCurSel(pNMHDR->hwndFrom);
	m_TabCtrl.m_pDialogData[i + 1].pDialog->ShowWindow (FALSE);
}
