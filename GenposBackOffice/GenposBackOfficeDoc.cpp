// GenposBackOfficeDoc.cpp : implementation of the CGenposBackOfficeDoc class
//

#include "stdafx.h"
#include "GenposBackOffice.h"

#include "GenposBackOfficeDoc.h"
#include "CntrItem.h"

#include <R20_PC2172.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGenposBackOfficeDoc

IMPLEMENT_DYNCREATE(CGenposBackOfficeDoc, COleDocument)

BEGIN_MESSAGE_MAP(CGenposBackOfficeDoc, COleDocument)
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, &COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, &COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, &COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_VIEW_LANCONNECTION, &CGenposBackOfficeDoc::OnViewLanconnection)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LANCONNECTION, &CGenposBackOfficeDoc::OnUpdateViewLanconnection)
	ON_COMMAND(ID_TERMINAL_LOGINTO, &CGenposBackOfficeDoc::OnTerminalLoginto)
	ON_UPDATE_COMMAND_UI(ID_TERMINAL_LOGINTO, &CGenposBackOfficeDoc::OnUpdateViewLanconnection)
	ON_COMMAND(ID_TERMINAL_LOGOUT, &CGenposBackOfficeDoc::OnTerminalLogout)
	ON_UPDATE_COMMAND_UI(ID_TERMINAL_LOGOUT, &CGenposBackOfficeDoc::OnUpdateViewLanconnection)
	ON_COMMAND(ID_TERMINAL_TOTALRETRIEVE, &CGenposBackOfficeDoc::OnTerminalTotalretrieve)
END_MESSAGE_MAP()


// CGenposBackOfficeDoc construction/destruction

CGenposBackOfficeDoc::CGenposBackOfficeDoc() :
	m_bLanOpen(FALSE), m_bLanLogInto(FALSE), m_sLanLastError(0),
	totalRegFinCurDay(CTotal::TtlTypeCurDay)
{
	// Use OLE compound files
	EnableCompoundFile();

	// temporary default text
	m_csHostName = _T("HostName");
	m_csHostMemo = _T("host memo");
}

CGenposBackOfficeDoc::~CGenposBackOfficeDoc()
{
}

BOOL CGenposBackOfficeDoc::OnNewDocument()
{
	TRACE2 ("%S(%d): -- OnNewDocument() Entry.\n", __FILE__, __LINE__);

	if (!COleDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CGenposBackOfficeDoc serialization

void CGenposBackOfficeDoc::Serialize(CArchive& ar)
{
	TRACE2 ("%S(%d): -- Serialize() Entry.\n", __FILE__, __LINE__);

	// WARNING:  Make sure that storing of the archive is the same
	//           variables and in the same order as opening and reading the archive!
	if (ar.IsStoring())
	{
		TRACE1 ("  Serialize() Storing %s.\n", ar.m_strFileName);
		ar << m_csHostName;
		ar << m_csHostMemo;
	}
	else
	{
		TRACE1 ("  Serialize() Reading %s.\n", ar.m_strFileName);
		ar >> m_csHostName;
		ar >> m_csHostMemo;
	}

	// Calling the base class COleDocument enables serialization
	//  of the container document's COleClientItem objects.
	COleDocument::Serialize(ar);

	if (!ar.IsStoring()) {
		POSITION pos = GetStartPosition();
		while (pos) {
			CDocItem *doc = GetNextItem(pos);
		}
	}
}


// CGenposBackOfficeDoc diagnostics

#ifdef _DEBUG
void CGenposBackOfficeDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CGenposBackOfficeDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

#include "DialogLan.h"
#include "DialogLanLogin.h"

// CGenposBackOfficeDoc commands

void CGenposBackOfficeDoc::OnViewLanconnection()
{
	TRACE2 ("%S(%d): -- OnViewLanconnection() Entry.\n", __FILE__, __LINE__);

	CDialogLan dialogLan;

	dialogLan.m_csHostName = m_csHostName;
	dialogLan.m_csHostMemo = m_csHostMemo;
	if (dialogLan.DoModal() == IDOK) {
		m_csHostName = dialogLan.m_csHostName;
		m_csHostMemo = dialogLan.m_csHostMemo;
		SetModifiedFlag ();
		UpdateAllViews (NULL);
	}
}

void CGenposBackOfficeDoc::OnUpdateViewLanconnection(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(1);
}

void CGenposBackOfficeDoc::OnTerminalLoginto()
{
	TRACE2 ("%S(%d): -- OnTerminalLoginto() Entry.\n", __FILE__, __LINE__);

	CDialogLanLogin dialogLanLogin;

	dialogLanLogin.m_csHostName = m_csHostName;
	dialogLanLogin.m_csTermNo = m_csLastTermNo;
	if (dialogLanLogin.DoModal() == IDOK) {
		m_csLastTermNo = dialogLanLogin.m_csTermNo;
		m_csHostSession = dialogLanLogin.m_csHostSession;
		m_csHostSessionPassword = dialogLanLogin.m_csHostPassword;
		if (m_bLanOpen) {
			m_sLanLastError = ::PcifCloseEx(PCIF_FUNC_OPEN_LAN, NULL);
			TRACE1 ("  OnTerminalLoginto   >> ::PcifCloseEx() = %d\n", m_sLanLastError );
		}
		m_bLanOpen = FALSE;

		// --- open serial port with user specified configuration ---
		m_sLanLastError = ::PcifOpenEx( PCIF_FUNC_OPEN_LAN, NULL );
		m_bLanOpen = ( m_sLanLastError == PCIF_SUCCESS ) ? TRUE : FALSE;
		TRACE1 ("  OnTerminalLoginto   >> ::PcifOpenEx() = %d\n", m_sLanLastError );

		if (m_bLanOpen) {
			m_sLanLastError = ::IspHostLogOn( m_csHostSession, m_csHostSessionPassword );
			m_bLanLogInto = ( m_sLanLastError == PCIF_SUCCESS ) ? TRUE : FALSE;
			TRACE1 ("  OnTerminalLoginto   >> ::IspHostLogOn() = %d\n", m_sLanLastError );
		}
	}
}

void CGenposBackOfficeDoc::OnTerminalLogout()
{
	TRACE2 ("%S(%d): -- OnTerminalLogout() Entry.\n", __FILE__, __LINE__);
	if (m_bLanLogInto) {
		m_sLanLastError = ::IspLogOff( );
		TRACE1 ("  OnTerminalLoginto   >> ::IspLogOff() = %d\n", m_sLanLastError );
	}
	m_bLanLogInto = FALSE;
	if (m_bLanOpen) {
		m_sLanLastError = ::PcifCloseEx(PCIF_FUNC_OPEN_LAN, NULL);
	    TRACE1 ("  OnTerminalLogout   >> ::PcifCloseEx() = %d\n", m_sLanLastError );
	}
    m_bLanOpen = FALSE;
}

void CGenposBackOfficeDoc::OnTerminalTotalretrieve()
{
	TRACE2 ("%S(%d): -- OnTerminalTotalretrieve() Entry.\n", __FILE__, __LINE__);

	short  sRetrieveStatus = 0;

	if (m_bLanOpen && m_bLanLogInto) {
		sRetrieveStatus = totalRegFinCurDay.RetrieveTotal ();
		TRACE1("  totalRegFinCurDay.RetrieveTotal %d\n", sRetrieveStatus);
	}
}

void CGenposBackOfficeDoc::OnTerminalEndOfDay()
{
	TRACE2 ("%S(%d): -- OnTerminalEndOfDay() Entry.\n", __FILE__, __LINE__);

	short  sRetrieveStatus = 0;

	if (m_bLanOpen && m_bLanLogInto) {
		totalRegFinCurDay.ResetTotalEndOfDay ();
	}
}
