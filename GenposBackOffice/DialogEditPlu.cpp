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

}

CDialogEditPlu::CDialogEditPlu(CParamPlu &myPlu)
	: CDialog(CDialogEditPlu::IDD, NULL)
{
	m_paramPlu = myPlu;
	TCHAR  tcsMnemonic[21] = {0};
	_tcsncpy (tcsMnemonic, m_paramPlu.m_paraPlu[0].ParaPlu.auchPluName, 20);
	m_displayMnemonic = tcsMnemonic;
}

CDialogEditPlu::~CDialogEditPlu()
{
}

void CDialogEditPlu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MNEMONIC, m_displayMnemonic);

	if (pDX->m_bSaveAndValidate) {
		_tcsncpy (m_paramPlu.m_paraPlu[0].ParaPlu.auchPluName, m_displayMnemonic, 20);
	}
}


BEGIN_MESSAGE_MAP(CDialogEditPlu, CDialog)
END_MESSAGE_MAP()


// CDialogEditPlu message handlers
