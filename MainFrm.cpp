// MainFrm.cpp : implementation of the CMainFrame class
//

//////////////////////////////////////////////////////////////////
//
// Revision information
//
//
//
// March 22 2002: ewcpahi:
//			Added Search function
// April 18 2002: ewcpahi:
//			Allow setting LF options from here.
//
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "decoder.h"

#include "MainFrm.h"
#include <..\src\occimpl.h>
#include "RHtmlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_HALL, OnHall)
	ON_BN_CLICKED(IDC_BN_DOHIGHLIGHT, OnDohighlight)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_SEARCHCOMBO, OnSearch)
	ON_COMMAND(ID_OPTIONS, SetViewOptions)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
/*	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/
	if (!m_wndToolBar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_ALIGN_TOP|CBRS_TOOLTIPS) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndSearchBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	CRect rect(50,3,250,200);
	m_wndSearchCombo.Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWN|CBS_AUTOHSCROLL|WS_VSCROLL,rect,&m_wndSearchBar,IDC_SEARCHCOMBO);
	m_wndSearchCombo.SetFont(m_wndSearchBar.GetFont());

	if (!m_wndHighlightBar.Create(this, IDR_MAINFRAME2, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
	

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndSearchBar)  ||
		!m_wndReBar.AddBar(&m_wndHighlightBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);

//	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
//		CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndSearchBar.GetDlgItem(IDC_HCOLOR)->SetWindowText("darkblue");
	m_wndSearchBar.GetDlgItem(IDC_HCOLOR)->EnableWindow(FALSE);
	m_wndSearchBar.GetDlgItem(IDC_HCOL)->EnableWindow(FALSE);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnSearch()
{
	CString txt;
	m_wndSearchCombo.GetWindowText(txt);
	if(txt=="") return;

	int nFlags = ((CButton*)m_wndSearchBar.GetDlgItem(IDC_WORD))->GetCheck() ? 2 : 0;
	BOOL bHAll = ((CButton*)m_wndSearchBar.GetDlgItem(IDC_HALL))->GetCheck();
	CString sHlColor;
	m_wndSearchBar.GetDlgItem(IDC_HCOLOR)->GetWindowText(sHlColor);

	CView *pView = GetActiveFrame()->GetActiveView();
	if(pView!=NULL)
	{
		CString sClassName(pView->GetRuntimeClass()->m_lpszClassName);
		if(sClassName=="RHtmlView"||sClassName=="CDecodeLFView"||sClassName=="CDecodeIMView")
		{
			if(bHAll)
				((RHtmlView*)pView)->FindText2(txt,nFlags,"color: white; background-color: "+sHlColor);
			else
				((RHtmlView*)pView)->FindText(txt,nFlags);
		}
		// TODO: Add more if statements to extend search to other view classes
		return;
	}
	AfxMessageBox("Cannot find the string '" + txt + "'.");
}

void CMainFrame::OnHall() 
{
	if(((CButton*)m_wndSearchBar.GetDlgItem(IDC_HALL))->GetCheck())
	{
		m_wndSearchBar.GetDlgItem(IDC_HCOLOR)->EnableWindow();
		m_wndSearchBar.GetDlgItem(IDC_HCOL)->EnableWindow();
	} else
	{
		m_wndSearchBar.GetDlgItem(IDC_HCOLOR)->EnableWindow(FALSE);
		m_wndSearchBar.GetDlgItem(IDC_HCOL)->EnableWindow(FALSE);
	}
}


void CMainFrame::OnDohighlight() 
{
	// TODO: Add your control notification handler code here

	CString sWhat;
	m_wndHighlightBar.GetDlgItem(IDC_HHIGHLIGHT)->GetWindowText(sWhat);

	CView *pView = GetActiveFrame()->GetActiveView();
	if(pView!=NULL)
	{
		CString sClassName(pView->GetRuntimeClass()->m_lpszClassName);
		if(sClassName=="RHtmlView"||sClassName=="CDecodeLFView"||sClassName=="CDecodeIMView")
		{
			((RHtmlView*)pView)->HighlightAllLines(sWhat,2,"background-color: yellow");
		}
		// TODO: Add more if statements to extend search to other view classes
		return;
	}
	AfxMessageBox("Cannot find the string '" + sWhat + "'.");	
}




#include "LFOptionsDlg.h"

void CMainFrame::SetViewOptions()
{
	CLFOptionsDlg optionsDlg;
	if (optionsDlg.DoModal() == IDOK)
	{
	}
}
