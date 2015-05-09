// CntrItem.h : interface of the CGenposBackOfficeCntrItem class
//

#pragma once

class CGenposBackOfficeDoc;
class CGenposBackOfficeView;

class CGenposBackOfficeCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CGenposBackOfficeCntrItem)

// Constructors
public:
	CGenposBackOfficeCntrItem(CGenposBackOfficeDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer

// Attributes
public:
	CGenposBackOfficeDoc* GetDocument()
		{ return reinterpret_cast<CGenposBackOfficeDoc*>(COleClientItem::GetDocument()); }
	CGenposBackOfficeView* GetActiveView()
		{ return reinterpret_cast<CGenposBackOfficeView*>(COleClientItem::GetActiveView()); }

	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);

// Implementation
public:
	~CGenposBackOfficeCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

