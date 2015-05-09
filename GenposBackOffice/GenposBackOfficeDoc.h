// GenposBackOfficeDoc.h : interface of the CGenposBackOfficeDoc class
//


#pragma once


class CGenposBackOfficeDoc : public COleDocument
{
protected: // create from serialization only
	CGenposBackOfficeDoc();
	DECLARE_DYNCREATE(CGenposBackOfficeDoc)

// Attributes
public:
	CString  m_csHostName;

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
};


