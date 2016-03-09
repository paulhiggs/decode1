// DecodeIMView.cpp : implementation of the CDecodeIMView class
//

#include "stdafx.h"
#include "decoder.h"

#include <..\src\occimpl.h>
#include "DecodeIMDoc.h"
#include "DecodeIMView.h"

#include "UserInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMView

IMPLEMENT_DYNCREATE(CDecodeIMView, RHtmlView)

BEGIN_MESSAGE_MAP(CDecodeIMView, RHtmlView)
	//{{AFX_MSG_MAP(CDecodeIMView)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, RHtmlView::OnFilePrint)
	ON_COMMAND(ID_LOADMESSAGE, GetUserInput)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMView construction/destruction

CDecodeIMView::CDecodeIMView()
{
	// TODO: add construction code here

}

CDecodeIMView::~CDecodeIMView()
{
}



/////////////////////////////////////////////////////////////////////////////
// CDecodeIMView drawing

void CDecodeIMView::OnDraw(CDC* pDC)
{
	CDecodeIMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if (pDoc->hasDecodeContent())
		Navigate2(pDoc->getDecodeFile(),NULL,NULL);

}

void CDecodeIMView::OnInitialUpdate()
{
	RHtmlView::OnInitialUpdate();

	CDecodeIMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	if (pDoc->hasDecodeContent())
		Navigate2(pDoc->getDecodeFile(),NULL,NULL);
}


void CDecodeIMView::OnFileClose()
{
	CHtmlView::OnClose();
}

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMView printing


/////////////////////////////////////////////////////////////////////////////
// CDecodeIMView diagnostics

#ifdef _DEBUG
void CDecodeIMView::AssertValid() const
{
	RHtmlView::AssertValid();
}

void CDecodeIMView::Dump(CDumpContext& dc) const
{
	RHtmlView::Dump(dc);
}

CDecodeIMDoc* CDecodeIMView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDecodeIMDoc)));
	return (CDecodeIMDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CDecodeIMView message handlers

void CDecodeIMView::GetUserInput(void)
{
	CDecodeIMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CUserInputDlg userInputDlg;
	userInputDlg.m_UserInput = pDoc->getLastMessage();
	if (userInputDlg.DoModal() == IDOK)
	{
		pDoc->DecodeMessage(userInputDlg.m_UserInput);
		Navigate2(pDoc->getDecodeFile(),NULL,NULL);
	}
}


void CDecodeIMView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
	CDecodeIMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	if (pDoc->hasDecodeContent())
		Navigate2(pDoc->getDecodeFile(),NULL,NULL);
}

void CDecodeIMView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	HMENU hMenu;
	hMenu=CreatePopupMenu();

	BOOL t = TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_TOPALIGN,point.x,point.y,0,pWnd->m_hWnd,NULL);
}
