// decode1Frm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "decoder.h"

#include "decode1Frm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdecode1Frm

IMPLEMENT_DYNCREATE(Cdecode1Frm, CMDIChildWnd)

BEGIN_MESSAGE_MAP(Cdecode1Frm, CMDIChildWnd)
	//{{AFX_MSG_MAP(Cdecode1Frm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdecode1Frm construction/destruction

Cdecode1Frm::Cdecode1Frm()
{
	// TODO: add member initialization code here
	
}

Cdecode1Frm::~Cdecode1Frm()
{
}

BOOL Cdecode1Frm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void Cdecode1Frm::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void Cdecode1Frm::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Cdecode1Frm message handlers
