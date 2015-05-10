// GenposBackOfficeDoc.h : interface of the CGenposBackOfficeDoc class
//

#pragma once

#include "TotalRegFin.h"

class CGenposBackOfficeDoc : public COleDocument
{
protected: // create from serialization only
	CGenposBackOfficeDoc();
	DECLARE_DYNCREATE(CGenposBackOfficeDoc)

// Attributes
public:
	CString  m_csHostName;      // host name prefix for this cluster group without the dash (-) and terminal number
	CString  m_csLastTermNo;    // last terminal number, used with m_csHostName to create DHCP target
	CString  m_csHostMemo;      // memo information about this cluster group.
	CString  m_csHostSession;   // either terminal host name or 
	CString  m_csHostSessionPassword;
	BOOL     m_bLanOpen;
	BOOL     m_bLanLogInto;
	short    m_sLanLastError;

	CTotalRegFin  totalRegFinCurDay;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CGenposBackOfficeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewLanconnection();
	afx_msg void OnUpdateViewLanconnection(CCmdUI *pCmdUI);
	afx_msg void OnTerminalLoginto();
	afx_msg void OnTerminalLogout();
	afx_msg void OnTerminalTotalretrieve();
	afx_msg void OnTerminalEndOfDay();
};


