// DecodeIMFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "decoder.h"

#include "DecodeIMFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMFrm

IMPLEMENT_DYNCREATE(CDecodeIMFrm, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CDecodeIMFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CDecodeIMFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMFrm construction/destruction

CDecodeIMFrm::CDecodeIMFrm()
{
	// TODO: add member initialization code here
	
}

CDecodeIMFrm::~CDecodeIMFrm()
{
}

BOOL CDecodeIMFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDecodeIMFrm diagnostics

#ifdef _DEBUG
void CDecodeIMFrm::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CDecodeIMFrm::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMFrm message handlers
