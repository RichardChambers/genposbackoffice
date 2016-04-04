// DialogEditPlu.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "DialogEditPlu.h"


// CDialogEditPlu dialog

IMPLEMENT_DYNAMIC(CDialogEditPlu, CDialog)

CDialogEditPlu::CDialogEditPlu(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogEditPlu::IDD, pParent)
	, m_displayMnemonic(_T(""))
{
	m_TabItem[1].mask = TCIF_TEXT;
	m_TabItem[1].pszText = _T("Tab 1");
	m_TabItem[2].mask = TCIF_TEXT;
	m_TabItem[2].pszText = _T("Tab 2");
	m_TabItem[3].mask = TCIF_TEXT;
	m_TabItem[3].pszText = _T("Tab 3");
}

CDialogEditPlu::CDialogEditPlu(CParamPlu &myPlu)
	: CDialog(CDialogEditPlu::IDD, NULL)
{
	m_paramPlu = myPlu;
	wchar_t  tcsMnemonic[OP_PLU_NAME_SIZE + 1] = {0};
	wcsncpy (tcsMnemonic, m_paramPlu.m_paraPlu[0].ParaPlu.auchPluName, OP_PLU_NAME_SIZE);
	m_displayMnemonic = tcsMnemonic;

	m_TabItem[1].mask = TCIF_TEXT;
	m_TabItem[1].pszText = _T("Tab 1");
	m_TabItem[2].mask = TCIF_TEXT;
	m_TabItem[2].pszText = _T("Tab 2");
	m_TabItem[3].mask = TCIF_TEXT;
	m_TabItem[3].pszText = _T("Tab 3");
}

CDialogEditPlu::~CDialogEditPlu()
{
}


const CDialogEditPlu::TabToStatus CDialogEditPlu::m_TabItemOneStatus[] = {
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

void CDialogEditPlu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MNEMONIC, m_displayMnemonic);
	DDX_Control(pDX, IDC_TAB_CONTROL_EDIT_STATUS, m_TabCtrl);

#if 0
	if (pDX->m_bSaveAndValidate) {
		wcsncpy (m_paramPlu.m_paraPlu[0].ParaPlu.auchPluName, m_displayMnemonic, OP_PLU_NAME_SIZE);
	}
#else
	//  blocking out the edit dialog still needs work.
	if (pDX->m_bSaveAndValidate) {
		wcsncpy (m_paramPlu.m_paraPlu[0].ParaPlu.auchPluName, m_displayMnemonic, OP_PLU_NAME_SIZE);
		for (int i = 0; i < sizeof(m_TabItemOneStatus)/sizeof(m_TabItemOneStatus[0]); i++) {
			int iTab = m_TabItemOneStatus[i].sTabItem;
			int iDlg = m_TabItemOneStatus[i].iDlgItem;
			int iOffset = m_TabItemOneStatus[i].sOffset;
#if 0
			CButton *p = (CButton *) m_TabCtrl.m_pDialogData[iTab].pDialog->GetDlgItem(iDlg);
			if (p->GetCheck()) {
				m_paraCashier.fbCashierStatus[iOffset] |= m_TabItemOneStatus[i].uchBit;
			} else {
				m_paraCashier.fbCashierStatus[iOffset] &= ~(m_TabItemOneStatus[i].uchBit);
			}
#endif
		}
	} else {
		m_TabCtrl.InsertItemDialogTemplate (IDD_DIALOGEDITPLU_TAB_ONE, 1, &m_TabItem[1]);
		m_TabCtrl.InsertItemDialogTemplate (IDD_DIALOGEDITPLU_TAB_TWO, 2, &m_TabItem[2]);
//		m_TabCtrl.InsertItemDialogTemplate (IDD_DIALOGEDITPLU_TAB_THRE, 3, &m_TabItem[3]);
		for (int i = 0; i < sizeof(m_TabItemOneStatus)/sizeof(m_TabItemOneStatus[0]); i++) {
			int iTab = m_TabItemOneStatus[i].sTabItem;
			int iDlg = m_TabItemOneStatus[i].iDlgItem;
			int iOffset = m_TabItemOneStatus[i].sOffset;
#if 0
			CButton *p = (CButton *) m_TabCtrl.m_pDialogData[iTab].pDialog->GetDlgItem(iDlg);
			if (m_paraCashier.fbCashierStatus[iOffset] & m_TabItemOneStatus[i].uchBit) {
				p->SetCheck (1);
			} else {
				p->SetCheck (0);
			}
#endif
		}
		m_TabCtrl.m_pDialogData[1].pDialog->ShowWindow (TRUE);
	}
#endif
}


BEGIN_MESSAGE_MAP(CDialogEditPlu, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL_EDIT_STATUS, &CDialogEditPlu::OnTcnSelchangeTabControlEditStatus)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_CONTROL_EDIT_STATUS, &CDialogEditPlu::OnTcnSelchangingTabControlEditStatus)
END_MESSAGE_MAP()


// CDialogEditPlu message handlers

void CDialogEditPlu::OnTcnSelchangeTabControlEditStatus(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	int i = TabCtrl_GetCurSel(pNMHDR->hwndFrom);
	m_TabCtrl.m_pDialogData[i + 1].pDialog->ShowWindow (TRUE);
}

void CDialogEditPlu::OnTcnSelchangingTabControlEditStatus(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	int i = TabCtrl_GetCurSel(pNMHDR->hwndFrom);
	m_TabCtrl.m_pDialogData[i + 1].pDialog->ShowWindow (FALSE);
}
