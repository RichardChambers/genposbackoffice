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
	ON_COMMAND(ID_FILE_PRINT, &CGenposBackOfficeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_MESSAGE(WM_LANPROGRESS, &CGenposBackOfficeView::OnViewLanconnectionProgress)
END_MESSAGE_MAP()

// CGenposBackOfficeView construction/destruction

CGenposBackOfficeView::CGenposBackOfficeView() : m_firstTextLine (10, 50, 350, 75), m_lineIncrement(0, 25)
{
	LOGFONT lf = {0};
	// request a 12-pixel-height font
	// request a face name "Arial"
	lf.lfHeight = 18;
	wcsncpy (lf.lfFaceName, L"Arial", 7);

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
		// disable the buttons we do not want when logged into a terminal
		cbuttonLogIn.EnableWindow (0);
		cbuttonLanConnection.EnableWindow (0);
		// enable the buttons we need to use when logged into a terminal
		cbuttonLogOut.EnableWindow (1);
		cbuttonFlexMem.EnableWindow (1);
		cbuttonSettingsRetrieve.EnableWindow (1);
	} else {
		// enable the buttons we need to use when logged out of a terminal
		cbuttonLogIn.EnableWindow (1);
		cbuttonLanConnection.EnableWindow (1);
		// disable the buttons we do not need to use when logged out of a terminal
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
	pDC->DrawText (pDoc->m_LanData.m_csSqlite3dbFileName, currentLine, DT_LEFT | DT_VCENTER);
	currentLine += incrementLine;
	pDC->DrawText (pDoc->m_LanData.m_csHostName, currentLine, DT_LEFT | DT_VCENTER);
	currentLine += incrementLine;
	currentLine.bottom += 300;
	currentLine.right  += 50;
	pDC->DrawText (pDoc->m_LanData.m_csHostMemo, currentLine, DT_LEFT | DT_VCENTER | DT_WORDBREAK);

	currentLine.top += 300;
	currentLine += incrementLine;

	pDC->SelectObject(def_font);
}

void CGenposBackOfficeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	int  rectButtonWidth = 90;
	int  rectButtonHeight = 40;

	CRect  rectButton(10, 0, 10 + rectButtonWidth, rectButtonHeight);

	cbuttonLanConnection.Create (_T("Lan Setting"), 0, rectButton, this, ID_VIEW_LANCONNECTION);
	cbuttonLanConnection.ShowWindow (SW_SHOW);

	rectButton.left = 350;

	rectButton.right = rectButton.left + rectButtonWidth;
	cbuttonLogIn.Create (_T("Log In"), 0, rectButton, this, ID_TERMINAL_LOGINTO);
	cbuttonLogIn.ShowWindow (SW_SHOW);

	rectButton.top += rectButtonHeight + 10;
	rectButton.bottom += rectButtonHeight + 10;

	cbuttonFlexMem.Create (_T("Flex Mem"), 0, rectButton, this, ID_TERMINAL_FLEXMRETRIEVE);
	cbuttonFlexMem.ShowWindow (SW_SHOW);
	cbuttonFlexMem.EnableWindow (0);

	rectButton.top -= rectButtonHeight + 10;
	rectButton.bottom -= rectButtonHeight + 10;

	rectButton.left += rectButtonWidth + 5;
	rectButton.right += rectButtonWidth + 5;

	cbuttonLogOut.Create (_T("Log Out"), 0, rectButton, this, ID_TERMINAL_LOGOUT);
	cbuttonLogOut.ShowWindow (SW_SHOW);
	cbuttonLogOut.EnableWindow (0);

	rectButton.top += rectButtonHeight + 10;
	rectButton.bottom += rectButtonHeight + 10;

	cbuttonSettingsRetrieve.Create (_T("Retrieve"), 0, rectButton, this, ID_TERMINAL_SETTINGSRETRIEVE);
	cbuttonSettingsRetrieve.ShowWindow (SW_SHOW);
	cbuttonSettingsRetrieve.EnableWindow (0);

	rectButton.left += rectButtonWidth + 5;
	rectButton.right += rectButtonWidth + 5;
	cstaticProgress.Create (L"LAN", SS_BITMAP | SS_CENTERIMAGE, rectButton, this, 0);

	m_firstTextLine.top = rectButton.bottom + 20;
	m_firstTextLine.bottom = m_firstTextLine.top + 25;

	cstaticProgress.ShowWindow (SW_SHOW);
	cstaticProgress.EnableWindow (0);
}


// CGenposBackOfficeView printing

BOOL CGenposBackOfficeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	SendMessage (WM_LANPROGRESS, 0, 0);

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
   CView::OnDestroy();
}



void CGenposBackOfficeView::OnFilePrint()
{
	
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


LRESULT  CGenposBackOfficeView::OnViewLanconnectionProgress(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your command handler code here
	cstaticProgress.SendMessage (WM_LANPROGRESS, wParam, lParam);
	return 0;
}
