// GenposBackOfficeDoc.cpp : implementation of the CGenposBackOfficeDoc class
//

#include "stdafx.h"
#include "GenposBackOffice.h"

#include "GenposBackOfficeDoc.h"
#include "CntrItem.h"

#include "DialogCashier.h"
#include "DialogCoupon.h"
#include "DialogPlu.h"
#include "DialogMnemonic.h"

#include <R20_PC2172.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLanConnectionData::CLanConnectionData () :
		m_csHostName(L"")
		, m_csLastTermNo(L"")
		, m_csHostMemo(L"")
		, m_csHostSession(L"")
		, m_bSavePassword(0)
		, m_csHostSessionPassword(L"")
		, m_dwHostSessionIpAddress(0)
		, m_bUseIpAddress(0)
{
}

CLanConnectionData & CLanConnectionData::operator = (const CLanConnectionData & other)
{
	if (this != &other) {
		m_csHostName = other.m_csHostName;
		m_csLastTermNo = other.m_csLastTermNo;
		m_csHostMemo = other.m_csHostMemo;
		m_csHostSession = other.m_csHostSession;
		m_bSavePassword = other.m_bSavePassword;
		m_csHostSessionPassword = other.m_csHostSessionPassword;
		m_dwHostSessionIpAddress = other.m_dwHostSessionIpAddress;
		m_bUseIpAddress = other.m_bUseIpAddress;
	}

	return *this;
}


/*
 *  CArchive & operator <<() - write (serialize) CLanConnectionData to an archive.
 *
 *  This function provides the mechanism for writing the data of a CLanConnectionData
 *  object to an archive during serialization.
 *
 *  If the m_bSavePassword flag is set then write the actual password to the archive.
 *  If the m_bSavePassword flag is not set then write an empty string to the archive.
*/
CArchive & operator << (CArchive & rhs, const CLanConnectionData & other)
{
	CString dummyPassword(L"");

	rhs << other.m_csHostName;
	rhs << other.m_csHostMemo;
	rhs << other.m_bUseIpAddress;
	rhs << other.m_dwHostSessionIpAddress;
	rhs << other.m_bSavePassword;
	if (other.m_bSavePassword) {
		// we are to save the password into the archive so write it.
		rhs << other.m_csHostSessionPassword;
	} else {
		// do not save the password in the archive so write the empty string instead.
		rhs << dummyPassword;
	}
	return rhs;
}

/*
 *  CArchive & operator >>() - read (serialize) CLanConnectionData from an archive.
 *
 *  This function provides the mechanism for reading the data of a CLanConnectionData
 *  object previously written to an archive from the archive during serialization.
 *
*/
CArchive & operator >> (CArchive & rhs, CLanConnectionData & other)
{
	rhs >> other.m_csHostName;
	rhs >> other.m_csHostMemo;
	rhs >> other.m_bUseIpAddress;
	rhs >> other.m_dwHostSessionIpAddress;
	rhs >> other.m_bSavePassword;
	rhs >> other.m_csHostSessionPassword;
	return rhs;
}


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
	ON_COMMAND(ID_TERMINAL_FLEXMRETRIEVE, &CGenposBackOfficeDoc::OnTerminalFlexmretrieve)
	ON_COMMAND(ID_TERMINAL_CASHIERRETRIEVE, &CGenposBackOfficeDoc::OnTerminalCashierretrieve)
	ON_COMMAND(ID_TERMINAL_COUPONRETRIEVE, &CGenposBackOfficeDoc::OnTerminalCouponretrieve)
	ON_COMMAND(ID_TERMINAL_EJRETRIEVE, &CGenposBackOfficeDoc::OnTerminalEJretrieve)
	ON_COMMAND(ID_TERMINAL_PLURETRIEVE, &CGenposBackOfficeDoc::OnTerminalPluretrieve)
	ON_COMMAND(ID_TERMINAL_LOCKKEYBOARD, &CGenposBackOfficeDoc::OnTerminalLockkeyboard)
	ON_COMMAND(ID_TERMINAL_UNLOCKKEYBOARD, &CGenposBackOfficeDoc::OnTerminalUnlockkeyboard)
	ON_COMMAND(ID_TERMINAL_SETTINGSRETRIEVE, &CGenposBackOfficeDoc::OnTerminalSettingsretrieve)
	ON_COMMAND(ID_EDIT_CASHIEREDIT, &CGenposBackOfficeDoc::OnEditCashieredit)
	ON_COMMAND(ID_EDIT_COUPONEDIT, &CGenposBackOfficeDoc::OnEditCouponedit)
	ON_COMMAND(ID_EDIT_PLUEDIT, &CGenposBackOfficeDoc::OnEditPluedit)
	ON_COMMAND(ID_EDIT_MNEMONICEDIT, &CGenposBackOfficeDoc::OnEditMnemonicedit)
END_MESSAGE_MAP()


// CGenposBackOfficeDoc construction/destruction

CGenposBackOfficeDoc::CGenposBackOfficeDoc() :
	m_bLanOpen(FALSE), m_bLanLogInto(FALSE), m_bKeyBoardLock(FALSE),
	m_sLanLastError(0),
	totalRegFinCurDay(CTotal::TtlTypeCurDay),
	totalCashierCurDay(CTotal::TtlTypeCurDay)
{
	// Use OLE compound files
	EnableCompoundFile();

	// temporary default text
	m_LanData.m_csHostName = _T("HostName");
	m_LanData.m_csHostMemo = _T("host memo");
	m_LanThread = dynamic_cast<CLanThread *>(AfxBeginThread(RUNTIME_CLASS(CLanThread), THREAD_PRIORITY_NORMAL, 0, 0));
	m_LanInProgress = 0;
}

CGenposBackOfficeDoc::~CGenposBackOfficeDoc()
{
}

BOOL CGenposBackOfficeDoc::OnNewDocument()
{
	TRACE2 ("** %S(%d): -- OnNewDocument() Entry.\n", __FILE__, __LINE__);

	if (!COleDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	paramFlexMem.ClearParam ();
	paramMdc.ClearParam ();
	listCashier.CashierDataList.SetSize(0);

	return TRUE;
}




// CGenposBackOfficeDoc serialization

void CGenposBackOfficeDoc::Serialize(CArchive& ar)
{
	TRACE2 ("** %S(%d): -- Serialize() Entry.\n", __FILE__, __LINE__);

	// WARNING:  Make sure that storing of the archive is the same
	//           variables and in the same order as opening and reading the archive!
	if (ar.IsStoring())
	{
		TRACE1 ("  ** Serialize() Storing %s.\n", ar.m_strFileName);
		ar << m_LanData;
	}
	else
	{
		TRACE1 ("  ** Serialize() Reading %s.\n", ar.m_strFileName);
		ar >> m_LanData;
	}

	paramFlexMem.Serialize (ar);
	if (!ar.IsStoring()) {
		paramFlexMem.SummaryToText (m_csHostFlexMem);
	}

	listCashier.CashierDataList.Serialize (ar);

	int iCount = listCashier.CashierDataList.GetCount ();

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
	TRACE2 ("** %S(%d): -- OnViewLanconnection() Entry.\n", __FILE__, __LINE__);

	CDialogLan dialogLan;

	dialogLan.m_LanData = m_LanData;
	if (dialogLan.DoModal() == IDOK) {
		m_LanData = dialogLan.m_LanData;
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
	TRACE2 ("** %S(%d): -- OnTerminalLoginto() Entry.\n", __FILE__, __LINE__);

	CDialogLanLogin dialogLanLogin;

	dialogLanLogin.m_LanData = m_LanData;
	if (dialogLanLogin.DoModal() == IDOK) {
		m_LanData = dialogLanLogin.m_LanData;
		if (m_bLanOpen) {
			m_sLanLastError = ::PcifCloseEx(PCIF_FUNC_CLOSE_LAN, NULL);
			TRACE1 ("  ** OnTerminalLoginto   >> ::PcifCloseEx() = %d\n", m_sLanLastError );
			m_bLanLogInto = (m_sLanLastError == PCIF_SUCCESS);
		}

		// --- open serial port with user specified configuration ---
		m_sLanLastError = ::PcifOpenEx( PCIF_FUNC_OPEN_LAN, NULL );
		m_bLanOpen = ( m_sLanLastError == PCIF_SUCCESS );
		TRACE1 ("  ** OnTerminalLoginto   >> ::PcifOpenEx() = %d\n", m_sLanLastError );

		if (m_bLanOpen) {
			m_sLanLastError = ::IspHostLogOn( m_LanData.m_csHostSession, m_LanData.m_csHostSessionPassword );
			m_bLanLogInto = ( m_sLanLastError == PCIF_SUCCESS );
			TRACE1 ("  ** OnTerminalLoginto   >> ::IspHostLogOn() = %d\n", m_sLanLastError );
			if (m_bLanLogInto && paramFlexMem.m_bDataRead == 0) {
				paramFlexMem.PullParam ();
			}
		}
	}

	UpdateAllViews (NULL);
}

void CGenposBackOfficeDoc::OnTerminalLogout()
{
	TRACE2 ("** %S(%d): -- OnTerminalLogout() Entry.\n", __FILE__, __LINE__);
	OnTerminalUnlockkeyboard();
	if (m_bLanLogInto) {
		m_sLanLastError = ::IspLogOff( );
		TRACE1 ("  ** OnTerminalLoginto   >> ::IspLogOff() = %d\n", m_sLanLastError );
		m_bLanLogInto = (m_sLanLastError == PCIF_SUCCESS);
	}
	if (m_bLanOpen) {
		m_sLanLastError = ::PcifCloseEx(PCIF_FUNC_CLOSE_LAN, NULL);
	    TRACE1 ("  ** OnTerminalLogout   >> ::PcifCloseEx() = %d\n", m_sLanLastError );
		m_bLanOpen = !(m_sLanLastError == PCIF_SUCCESS);
	}

	UpdateAllViews (NULL);
}

void CGenposBackOfficeDoc::OnTerminalTotalretrieve()
{
	TRACE2 ("** %S(%d): -- OnTerminalTotalretrieve() Entry.\n", __FILE__, __LINE__);

	short  sRetrieveStatus = 0;
	CString  mTotalCashierLine;

	if (m_bLanOpen && m_bLanLogInto) {
		short mPos = 0;
		TRACE0("Retrieve Regular Financial Total\n");
		sRetrieveStatus = totalRegFinCurDay.RetrieveTotal ();
		TRACE1("  ** totalRegFinCurDay.RetrieveTotal %d\n", sRetrieveStatus);
		short sRet;
		do {
			sRet = totalRegFinCurDay.getTotalStructLine (mPos, mTotalCashierLine, CTotal::TtlLineTypeText);
			TRACE2("  line %d - %s\n", mPos, mTotalCashierLine);
			mPos++;
		} while (sRet == 0);

		mPos = 0;
		do {
			sRet = totalRegFinCurDay.getTotalStructLine (mPos, mTotalCashierLine, CTotal::TtlLineTypeTextJson);
			TRACE2("  line %d - %s\n", mPos, mTotalCashierLine);
			mPos++;
		} while (sRet == 0);

		totalCashierCurDay.setTotalCashier (1);
		TRACE0("Retrieve Cashier Total\n");
		sRetrieveStatus = totalCashierCurDay.RetrieveTotal ();
		TRACE1("  ** totalCashierCurDay.RetrieveTotal %d\n", sRetrieveStatus);

		mPos = 0;
		do {
			sRet = totalCashierCurDay.getTotalStructLine (mPos, mTotalCashierLine, CTotal::TtlLineTypeText);
			TRACE2("  line %d - %s\n", mPos, mTotalCashierLine);
			mPos++;
		} while (sRet == 0);

		mPos = 0;
		do {
			sRet = totalCashierCurDay.getTotalStructLine (mPos, mTotalCashierLine, CTotal::TtlLineTypeTextJson);
			TRACE2("  line %d - %s\n", mPos, mTotalCashierLine);
			mPos++;
		} while (sRet == 0);
	}
}

void CGenposBackOfficeDoc::OnTerminalEndOfDay()
{
	TRACE2 ("** %S(%d): -- OnTerminalEndOfDay() Entry.\n", __FILE__, __LINE__);

	short  sRetrieveStatus = 0;

	if (m_bLanOpen && m_bLanLogInto) {
		totalRegFinCurDay.ResetTotalEndOfDay ();
	}
}

void CGenposBackOfficeDoc::OnTerminalFlexmretrieve()
{
	if (m_bLanOpen && m_bLanLogInto) {
		paramFlexMem.PullParam ();
		paramMdc.PullParam ();

		paramFlexMem.SummaryToText (m_csHostFlexMem);
		SetModifiedFlag ();
		UpdateAllViews (NULL);
	}
}

void CGenposBackOfficeDoc::OnTerminalCashierretrieve()
{
	if (m_bLanOpen && m_bLanLogInto) {
		listCashier.BuildCashierArray ();
	}
}

void CGenposBackOfficeDoc::OnTerminalCouponretrieve()
{
	if (m_bLanOpen && m_bLanLogInto) {
		listCoupon.RetrieveList ();
	}
}

void CGenposBackOfficeDoc::OnTerminalEJretrieve()
{
	static  char filePath[512] = {0};

	CFileDialog fileDialog(TRUE, L"*.txt");
	if (fileDialog.DoModal () == IDOK) {
		CString mFileName = fileDialog.GetFileName();
		for (int i = 0; i < mFileName.GetLength(); i++) {
			filePath[i] = mFileName.GetAt(i);
		}
		filePath[mFileName.GetLength()] = 0;
		if (m_bLanOpen && m_bLanLogInto && m_LanInProgress == 0) {
			m_LanInProgress = 1;
			m_LanThread->PostThreadMessage (ID_TERMINAL_EJRETRIEVE, (WPARAM)filePath, (LPARAM)&m_LanInProgress);
		} else if (m_LanInProgress != 0) {
			AfxMessageBox (L"Retrieval of data from Terminal already started.");
		}
	}
}

BOOL CGenposBackOfficeDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!COleDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// Use this file as the marker for where the document root folder begins.
	// The file that is opened or is saved is in the folder which is the
	// document database directory tree. The directory tree is where we will
	// store the various files for this cluster which is described by the file
	// we are opening.  From the file we are opening, determine the path to the
	// folder where the file is located as that is the root folder for where all
	// of the data files are stored.
	m_currentRootFolder = lpszPathName;
	const TCHAR  *tcsText = lpszPathName + _tcslen(lpszPathName);

	for ( ; tcsText >= lpszPathName; ) {
		if (*tcsText == _T('\\') || *tcsText == _T('/')) {
			break;
		}
		tcsText--;
	}

	int iLen = tcsText - lpszPathName + 1;
	m_currentRootFolder.Truncate (iLen);

	return TRUE;
}

void CGenposBackOfficeDoc::OnTerminalPluretrieve()
{
	if (m_bLanOpen && m_bLanLogInto) {
		listPlu.RetrieveList ();
	}
}

void CGenposBackOfficeDoc::OnTerminalLockkeyboard()
{
	if (m_bLanOpen && m_bLanLogInto && ~m_bKeyBoardLock) {
		m_sLanLastError = ::IspLockKeyBoard ();
	    TRACE1 ("  ** OnTerminalLockkeyboard   >> ::IspLockKeyBoard() = %d\n", m_sLanLastError );
		m_bKeyBoardLock = (m_sLanLastError == PCIF_SUCCESS);
	}
}

void CGenposBackOfficeDoc::OnTerminalUnlockkeyboard()
{
	if (m_bLanOpen && m_bLanLogInto && m_bKeyBoardLock) {
		m_sLanLastError = ::IspUnLockKeyBoard ();
	    TRACE1 ("  ** OnTerminalUnlockkeyboard   >> ::IspUnLockKeyBoard() = %d\n", m_sLanLastError );
		m_bKeyBoardLock = !(m_sLanLastError == PCIF_SUCCESS);
	}
}

void CGenposBackOfficeDoc::OnTerminalSettingsretrieve()
{
	// TODO: Add your command handler code here
	if (m_bLanOpen && m_bLanLogInto) {
		paramFlexMem.PullParam ();
		paramFlexMem.SummaryToText (m_csHostFlexMem);
		paramMdc.PullParam ();
		paramTrans.PullParam ();
		paramLeadThru.PullParam ();

		listPlu.RetrieveList ();
		listCoupon.RetrieveList ();
		listCashier.BuildCashierArray ();

		SetModifiedFlag ();
		UpdateAllViews (NULL);
	}
}

void CGenposBackOfficeDoc::OnEditCashieredit()
{
	if (m_bLanOpen && m_bLanLogInto) {
		CDialogCashier dialogCashier;
		dialogCashier.SetListCashier (&listCashier);
		dialogCashier.DoModal ();
	}
}

void CGenposBackOfficeDoc::OnEditCouponedit()
{
	if (m_bLanOpen && m_bLanLogInto) {
		CDialogCoupon dialogCoupon;
		dialogCoupon.SetListCoupon (&listCoupon);
		dialogCoupon.DoModal ();
	}
}

void CGenposBackOfficeDoc::OnEditPluedit()
{
	if (m_bLanOpen && m_bLanLogInto) {
		CDialogPlu dialogPlu;
		dialogPlu.SetListPlu (&listPlu);
		dialogPlu.DoModal ();
	}
}

void CGenposBackOfficeDoc::OnEditMnemonicedit()
{
	if (m_bLanOpen && m_bLanLogInto) {
		CDialogMnemonic dialogMnemonic(&paramTrans);
//		dialogMnemonic.SetListPlu (&listPlu);
		dialogMnemonic.DoModal ();
	}
}

