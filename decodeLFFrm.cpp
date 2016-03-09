// decodeLFFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "decoder.h"

#include "decodeLFFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDecodeLFFrm

IMPLEMENT_DYNCREATE(CDecodeLFFrm, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CDecodeLFFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CDecodeLFFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecodeLFFrm construction/destruction

CDecodeLFFrm::CDecodeLFFrm()
{
	// TODO: add member initialization code here
	
}

CDecodeLFFrm::~CDecodeLFFrm()
{
}

BOOL CDecodeLFFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDecodeLFFrm diagnostics

#ifdef _DEBUG
void CDecodeLFFrm::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CDecodeLFFrm::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDecodeLFFrm message handlers
