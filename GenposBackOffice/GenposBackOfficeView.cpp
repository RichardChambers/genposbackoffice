// GenposBackOfficeView.cpp : implementation of the CGenposBackOfficeView class
//

#include "stdafx.h"
#include "GenposBackOffice.h"

#include "GenposBackOfficeDoc.h"
#include "CntrItem.h"
#include "GenposBackOfficeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGenposBackOfficeView

IMPLEMENT_DYNCREATE(CGenposBackOfficeView, CView)

BEGIN_MESSAGE_MAP(CGenposBackOfficeView, CView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, &CGenposBackOfficeView::OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, &CGenposBackOfficeView::OnCancelEditCntr)
	ON_COMMAND(ID_FILE_PRINT, &CGenposBackOfficeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CGenposBackOfficeView construction/destruction

CGenposBackOfficeView::CGenposBackOfficeView() : m_firstTextLine (10, 50, 350, 75), m_lineIncrement(0, 25)
{
	m_pSelection = NULL;

	LOGFONT lf = {0};
	// request a 12-pixel-height font
	// request a face name "Arial"
	lf.lfHeight = 18;
	_tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("Arial"), 7);

	// create the font 
	VERIFY(m_ViewFont.CreateFontIndirect(&lf));
}

CGenposBackOfficeView::~CGenposBackOfficeView()
{
}

BOOL CGenposBackOfficeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGenposBackOfficeView drawing

void CGenposBackOfficeView::OnDraw(CDC* pDC)
{
	if (!pDC)
		return;

	CGenposBackOfficeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFont* def_font = pDC->SelectObject(&m_ViewFont);

	if (pDoc->m_bLanOpen) {
		// enable the buttons we need to use when logged into a terminal
		cbuttonLogOut.EnableWindow (1);
		cbuttonFlexMem.EnableWindow (1);
		cbuttonSettingsRetrieve.EnableWindow (1);
	} else {
		// disable the buttons we need to use when logged into a terminal
		cbuttonLogOut.EnableWindow (0);
		cbuttonFlexMem.EnableWindow (0);
		cbuttonSettingsRetrieve.EnableWindow (0);
	}

    // --- get client area of this view ---
	// these provide the physical sizes of the display device rather than
	// the client rectangle sizes.  used for printing to determine the
	// size and resolution of the page to be printed.
	int  vertRes = pDC->GetDeviceCaps (VERTRES);
	int  hortRes = pDC->GetDeviceCaps (HORZRES);
    CRect   rcClient;
	if (pDC->m_bPrinting) {
		rcClient.bottom = vertRes;
		rcClient.right = hortRes;
		rcClient.left = 0;
		rcClient.top = 0;
	} else {
		GetClientRect( &rcClient );
	}

	//  We will divide up the client rectangle into several different sections.
	//  The basic layout is that cluster description information is on the left
	//  and the provisioning related description is on the right. The provisioning
	//  related data is from the flexible memory data that has been pulled from
	//  the terminal.

	CRect  currentLine(m_firstTextLine);
	CPoint incrementLine(m_lineIncrement);
	if (pDC->m_bPrinting) {
		currentLine.top += 50;
		currentLine.left += 50;
		currentLine.right += 50;
		currentLine.right *= 4;
		currentLine.bottom *= 4;
		incrementLine.y += 200;
	}
	if (!pDoc->m_csHostFlexMem.IsEmpty()) {
		CRect rectFlexMem(currentLine);
		rectFlexMem.left += currentLine.right + 20;
		rectFlexMem.right += currentLine.right + 100;
		rectFlexMem.bottom += 700;
		if (pDC->m_bPrinting) {
			rectFlexMem.right += 1000;
			rectFlexMem.bottom += 2000;
		}
		pDC->DrawText (pDoc->m_csHostFlexMem, rectFlexMem, DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_EXPANDTABS);
	}
	pDC->DrawText (pDoc->m_currentRootFolder, currentLine, DT_LEFT | DT_VCENTER);
	currentLine += incrementLine;
	pDC->DrawText (pDoc->m_LanData.m_csHostName, currentLine, DT_LEFT | DT_VCENTER);
	currentLine += incrementLine;
	currentLine.bottom += 300;
	currentLine.right  += 50;
	pDC->DrawText (pDoc->m_LanData.m_csHostMemo, currentLine, DT_LEFT | DT_VCENTER | DT_WORDBREAK);

	currentLine.top += 300;
	currentLine += incrementLine;

	// TODO: also draw all OLE items in the document
	POSITION pos = pDoc->GetStartPosition ();
	CRect rect(currentLine);
	rect.bottom += 20;
	CPoint  lineincrement(m_lineIncrement); lineincrement.y += 22;
	while (pos) {
		CSize size;
		CGenposBackOfficeCntrItem *cDoc = (CGenposBackOfficeCntrItem *)pDoc->GetNextItem(pos);
		if (SUCCEEDED(cDoc->GetExtent(&size, cDoc->m_nDrawAspect)))
		{
			pDC->HIMETRICtoLP(&size);
			rect.right = size.cx + 10;
			rect.bottom = size.cy + 10;
		}
		cDoc->Draw(pDC, rect);
	}


	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CGenposBackOfficeCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.
	if (m_pSelection != NULL)
	{
		CSize size;
		CRect rect(currentLine);
		rect.bottom += 20;
		
		if (SUCCEEDED(m_pSelection->GetExtent(&size, m_pSelection->m_nDrawAspect)))
		{
			pDC->HIMETRICtoLP(&size);
			rect.right = size.cx + 10;
			rect.bottom = size.cy + 10;
		}
		m_pSelection->Draw(pDC, rect);
	}

	pDC->SelectObject(def_font);
}

void CGenposBackOfficeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

	int  rectButtonWidth = 85;
	CRect  rectButton(10, 0, 10 + rectButtonWidth, 40);
	cbuttonLanConnection.Create (_T("Lan Setting"), 0, rectButton, this, ID_VIEW_LANCONNECTION);
	cbuttonLanConnection.ShowWindow (SW_SHOW);

	rectButton.left += rectButtonWidth + 25;
	rectButton.right += rectButtonWidth + 25;
	cbuttonLogIn.Create (_T("Log In"), 0, rectButton, this, ID_TERMINAL_LOGINTO);
	cbuttonLogIn.ShowWindow (SW_SHOW);

	rectButton.left += rectButtonWidth + 5;
	rectButton.right += rectButtonWidth + 5;
	cbuttonLogOut.Create (_T("Log Out"), 0, rectButton, this, ID_TERMINAL_LOGOUT);
	cbuttonLogOut.ShowWindow (SW_SHOW);
	cbuttonLogOut.EnableWindow (0);

	rectButton.left = 350;
	rectButton.right = rectButton.left + rectButtonWidth;
	cbuttonFlexMem.Create (_T("Flex Mem"), 0, rectButton, this, ID_TERMINAL_FLEXMRETRIEVE);
	cbuttonFlexMem.ShowWindow (SW_SHOW);
	cbuttonFlexMem.EnableWindow (0);

	rectButton.left += rectButtonWidth + 5;
	rectButton.right += rectButtonWidth + 5;
	cbuttonSettingsRetrieve.Create (_T("Retrieve"), 0, rectButton, this, ID_TERMINAL_SETTINGSRETRIEVE);
	cbuttonSettingsRetrieve.ShowWindow (SW_SHOW);
	cbuttonSettingsRetrieve.EnableWindow (0);
}


// CGenposBackOfficeView printing

BOOL CGenposBackOfficeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGenposBackOfficeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGenposBackOfficeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGenposBackOfficeView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CView::OnDestroy();
}

void CGenposBackOfficeView::OnLButtonDown(UINT msg, CPoint point)
{
	// close in-place active item
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->Close();
	Invalidate();
}

void CGenposBackOfficeView::OnLButtonDblClk(UINT msg, CPoint point)
{
	CGenposBackOfficeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	POSITION pos = pDoc->GetStartPosition ();
	if (pos) {
		CGenposBackOfficeCntrItem *cDoc = (CGenposBackOfficeCntrItem *)pDoc->GetNextItem(pos);
		if (cDoc != NULL)
		{
			cDoc->DoVerb(GetKeyState(VK_CONTROL) < 0 ? OLEIVERB_OPEN : OLEIVERB_PRIMARY, this);
		}
	}
	Invalidate();
}


// OLE Client support and commands

BOOL CGenposBackOfficeView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CGenposBackOfficeCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CGenposBackOfficeView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CGenposBackOfficeCntrItem object
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CGenposBackOfficeCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document
		CGenposBackOfficeDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CGenposBackOfficeCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);
		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted

		// TODO: reimplement selection as appropriate for your application
		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation
void CGenposBackOfficeView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place
void CGenposBackOfficeView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CGenposBackOfficeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

void CGenposBackOfficeView::OnFilePrint()
{
	//By default, we ask the Active document to print itself
	//using IOleCommandTarget. If you don't want this behavior
	//remove the call to COleDocObjectItem::DoDefaultPrinting.
	//If the call fails for some reason, we will try printing
	//the docobject using the IPrint interface.
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL); 
	if (S_OK == COleDocObjectItem::DoDefaultPrinting(this, &printInfo))
		return;
	
	CView::OnFilePrint();

}



// CGenposBackOfficeView diagnostics

#ifdef _DEBUG
void CGenposBackOfficeView::AssertValid() const
{
	CView::AssertValid();
}

void CGenposBackOfficeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGenposBackOfficeDoc* CGenposBackOfficeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGenposBackOfficeDoc)));
	return (CGenposBackOfficeDoc*)m_pDocument;
}
#endif //_DEBUG


// CGenposBackOfficeView message handlers
