// GenposBackOfficeDoc.h : interface of the CGenposBackOfficeDoc class
//

#pragma once

#include "TotalRegFin.h"
#include "TotalCashier.h"
#include "ParamFlexMem.h"
#include "ParamMdc.h"

#include "ListerCashier.h"
#include "ListerPlu.h"
#include "ListerCoupon.h"

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
	CString  m_csHostFlexMem;   // information concerning last retrieval of flex mem settings.
	CString  m_csHostSession;   // either terminal host name or 
	CString  m_csHostSessionPassword;
	DWORD    m_dwHostSessionIpAddress;
	BOOL     m_bLanOpen;
	BOOL     m_bLanLogInto;
	BOOL     m_bKeyBoardLock;
	short    m_sLanLastError;

	CString  m_currentRootFolder;  // root folder for the current data set

	CTotalRegFin   totalRegFinCurDay;
	CTotalCashier  totalCashierCurDay;
	CParamFlexMem  paramFlexMem;
	CParamMdc      paramMdc;

	CListerCashier  listCashier;
	CListerPlu      listPlu;
	CListerCoupon   listCoupon;

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
	afx_msg void OnTerminalFlexmretrieve();
	afx_msg void OnTerminalCashierretrieve();
	afx_msg void OnTerminalCouponretrieve();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnTerminalPluretrieve();
	afx_msg void OnTerminalLockkeyboard();
	afx_msg void OnTerminalUnlockkeyboard();
	afx_msg void OnTerminalSettingsretrieve();
	afx_msg void OnEditCashieredit();
	afx_msg void OnEditCouponedit();
	afx_msg void OnEditPluedit();
};


