// DecodeLFView.cpp : implementation of the CDecodeLFView class
//

#include "stdafx.h"
#include "decoder.h"
#include "resource.h"

#include "GlobalDEfs.h"

#include <..\src\occimpl.h>
#include "DecodeLFDoc.h"
#include "DecodeLFView.h"

#include "LFOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDecodeLFView

IMPLEMENT_DYNCREATE(CDecodeLFView, RHtmlView)

BEGIN_MESSAGE_MAP(CDecodeLFView, RHtmlView)
	//{{AFX_MSG_MAP(CDecodeLFView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_FIND, RHtmlView::OnEditFind)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_OPTIONS, SetViewOptions)
	ON_COMMAND(ID_FILE_PRINT, RHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecodeLFView construction/destruction


CDecodeLFView::CDecodeLFView()
{
	// TODO: add construction code here
}

CDecodeLFView::~CDecodeLFView()
{
}

BOOL CDecodeLFView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return RHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDecodeLFView drawing

void CDecodeLFView::OnDraw(CDC* pDC)
{
	CDecodeLFDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if (pDoc->hasDecodeContent())
		Navigate2(pDoc->getDecodeFile(),NULL,NULL);

}

void CDecodeLFView::OnInitialUpdate()
{

	RHtmlView::OnInitialUpdate();

	OnUpdate(NULL,0,NULL);
	OnViewFontsSmall();
}

void CDecodeLFView::OnEditCopy()
{

	CWaitCursor wait;

	// get the current selection
	UINT nFrom=0, nTo=0;
/*	GetEditCtrl().GetSel((int&)nFrom, (int&)nTo);
 
	// what gets copied depends on partial vs. full selection
	if ((nFrom == 0 && nTo == (UINT)GetWindowTextLength()))
	{
		// copy entire document to the clipboard
		GetDocument()->GetEmbeddedItem()->CopyToClipboard(TRUE);
	}
	else
	{
		// copy linked item to clipboard
		CPadLinkItem item(GetDocument(), nFrom, nTo);
		item.CopyToClipboard(TRUE);
	}
*/
}

void CDecodeLFView::OnFileClose()
{
	DestroyWindow();
}
/////////////////////////////////////////////////////////////////////////////
// CDecodeLFView printing


/////////////////////////////////////////////////////////////////////////////
// CDecodeLFView diagnostics

#ifdef _DEBUG
void CDecodeLFView::AssertValid() const
{
	RHtmlView::AssertValid();
}

void CDecodeLFView::Dump(CDumpContext& dc) const
{
	RHtmlView::Dump(dc);
}

CDecodeLFDoc* CDecodeLFView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDecodeLFDoc)));
	return (CDecodeLFDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDecodeLFView message handlers


void CDecodeLFView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
	CDecodeLFDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	if (pDoc->hasDecodeContent()) {

		HCURSOR hSaveCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
		LoadFromResource(ID_EMPTY_BROWSE);
		Navigate2(pDoc->getDecodeFile(),NULL,NULL);
		SetCursor(hSaveCursor);
	}
}




#include "GlobalVars.h"
extern GlobalVars gv;
void CDecodeLFView::SetViewOptions()
{
	CDecodeLFDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	GlobalVars p = gv;
	CLFOptionsDlg optionsDlg;
	if ((optionsDlg.DoModal() == IDOK) && (p != gv))
	{
		HCURSOR hSaveCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
		CDocTemplate* pTemplate = pDoc->GetDocTemplate();
		POSITION pos = pTemplate->GetFirstDocPosition();
		while (pos != NULL)
		{
			CDecodeLFDoc* pDoc2 = (CDecodeLFDoc*)pTemplate->GetNextDoc(pos);
			pDoc2->DecodeLogfile();
		}
		SetCursor(hSaveCursor);
	}
}
