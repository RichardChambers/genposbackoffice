// GenposBackOfficeDoc.cpp : implementation of the CGenposBackOfficeDoc class
//

#include "stdafx.h"
#include "GenposBackOffice.h"

#include "GenposBackOfficeDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
END_MESSAGE_MAP()


// CGenposBackOfficeDoc construction/destruction

CGenposBackOfficeDoc::CGenposBackOfficeDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	m_csHostName = _T("HostName-1");

}

CGenposBackOfficeDoc::~CGenposBackOfficeDoc()
{
}

BOOL CGenposBackOfficeDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CGenposBackOfficeDoc serialization

void CGenposBackOfficeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_csHostName;
	}
	else
	{
		m_csHostName = _T("xxxx");
		ar >> m_csHostName;
	}

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


// CGenposBackOfficeDoc commands
