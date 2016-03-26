// GenposBackOfficeView.h : interface of the CGenposBackOfficeView class
//


#pragma once

class CGenposBackOfficeCntrItem;

class CGenposBackOfficeView : public CView
{
protected: // create from serialization only
	CGenposBackOfficeView();
	DECLARE_DYNCREATE(CGenposBackOfficeView)

// Attributes
public:
	CGenposBackOfficeDoc* GetDocument() const;
	// m_pSelection holds the selection to the current CGenposBackOfficeCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CGenposBackOfficeCntrItem objects.  This selection
	//  mechanism is provided just to help you get started

	// TODO: replace this selection mechanism with one appropriate to your app
	CGenposBackOfficeCntrItem* m_pSelection;

	CFont   m_ViewFont;
	CRect   m_firstTextLine;
	CPoint  m_lineIncrement;

	CButton   cbuttonLogIn;
	CButton   cbuttonLanConnection;
	CButton   cbuttonLogOut;
	CButton   cbuttonFlexMem;
	CButton   cbuttonSettingsRetrieve;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGenposBackOfficeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrint();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GenposBackOfficeView.cpp
inline CGenposBackOfficeDoc* CGenposBackOfficeView::GetDocument() const
   { return reinterpret_cast<CGenposBackOfficeDoc*>(m_pDocument); }
#endif

