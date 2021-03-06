// GenposBackOfficeDoc.h : interface of the CGenposBackOfficeDoc class
//

#pragma once

#include "TotalRegFin.h"
#include "TotalCashier.h"
#include "ParamFlexMem.h"
#include "ParamMdc.h"
#include "ParamMnemonic.h"

#include "ListerCashier.h"
#include "ListerPlu.h"
#include "ListerCoupon.h"
#include "ListerMnemonic.h"
#include "LanThread.h"

class CLanConnectionData
{
public:
	CLanConnectionData();
	~CLanConnectionData();
	CString  m_csHostName;      // host name prefix for this cluster group without the dash (-) and terminal number
	CString  m_csLastTermNo;    // last terminal number, used with m_csHostName to create DHCP target
	CString  m_csHostMemo;      // memo information about this cluster group.
	CString  m_csHostSession;   // either terminal host name or 
	BOOL     m_bSavePassword;
	CString  m_csHostSessionPassword;
	DWORD    m_dwHostSessionIpAddress;
	BOOL     m_bUseIpAddress;
	CString  m_csSqlite3dbFileName;
	sqlite3  *m_hSqlite3db;

	CLanConnectionData & operator = (const CLanConnectionData & other);

	int OpenSqlite3db (wchar_t *csFileName = 0);
	void CloseSqlite3db (void);
};

// the CArchive operators for serializing the LAN Connection Data
CArchive & operator << (CArchive & rhs, const CLanConnectionData & other);
CArchive & operator >> (CArchive & rhs, CLanConnectionData & other);

class CGenposBackOfficeDoc : public CDocument
{
protected: // create from serialization only
	CGenposBackOfficeDoc();
	DECLARE_DYNCREATE(CGenposBackOfficeDoc)

// Attributes
public:
	CLanConnectionData  m_LanData;
	CString  m_csHostFlexMem;   // information concerning last retrieval of flex mem settings.
	BOOL     m_bLanOpen;
	BOOL     m_bLanLogInto;
	BOOL     m_bKeyBoardLock;
	short    m_sLanLastError;

	CString  m_currentRootFolder;  // root folder for the current data set

	CLanThread     *m_LanThread;
	CLanThread::LanBlock m_LanBlock;

	CTotalRegFin   totalRegFinCurDay;
	CTotalCashier  totalCashierCurDay;
	CParamFlexMem  paramFlexMem;
	CParamMdc      paramMdc;
	CListerTransaction  listTrans;
	CListerLeadThru     listLeadThru;

	CListerCashier  listCashier;
	CListerPlu      listPlu;
	CListerCoupon   listCoupon;


	//                               Version:        Mmmvvbbb  M - Major, mm - minor, vv - version, bbb - build
	static const unsigned long m_ulVersionNumber = 0x10000001;   //  1.0.0.001
	static const unsigned long m_ulSignature = 0x1f2d3e4c;

// Operations
public:
	void DispatchToAllViews(UINT msg, WPARAM wParam, LPARAM lParam);
	static void DispatchToAllViewsFunc (void *p, UINT msg, WPARAM wParam, LPARAM lParam);

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
	afx_msg void OnTerminalEJretrieve();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnTerminalLockkeyboard();
	afx_msg void OnTerminalUnlockkeyboard();
	afx_msg void OnTerminalSettingsretrieve();
	afx_msg void OnDatabaseSettingsretrieve();
	afx_msg void OnEditCashieredit();
	afx_msg void OnEditCouponedit();
	afx_msg void OnEditPluedit();
	afx_msg void OnEditTransMnemonicedit();
	afx_msg void OnEditLeadThruMnemonicedit();
	afx_msg void OnEditTenderkeyedit();
};
