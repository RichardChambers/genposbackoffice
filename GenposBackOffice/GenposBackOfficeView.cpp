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

CGenposBackOfficeView::CGenposBackOfficeView() : m_firstTextLine(10, 10, 300, 25), m_lineIncrement(0, 25)
{
	m_pSelection = NULL;
	// TODO: add construction code here

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

	// TODO: add draw code for native data here
	CRect currentLine(m_firstTextLine);
	pDC->DrawText (pDoc->m_csHostName, currentLine, DT_LEFT | DT_VCENTER);
	currentLine += m_lineIncrement;
	currentLine.bottom += 300;
	currentLine.right  += 50;
	pDC->DrawText (pDoc->m_csHostMemo, currentLine, DT_LEFT | DT_VCENTER | DT_WORDBREAK);
	currentLine += m_lineIncrement;

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
}

void CGenposBackOfficeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

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
