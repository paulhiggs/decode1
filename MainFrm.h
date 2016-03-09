// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__8D15FDFA_E2AE_4462_B0F6_2C6C4A63C924__INCLUDED_)
#define AFX_MAINFRM_H__8D15FDFA_E2AE_4462_B0F6_2C6C4A63C924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchCombo.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//	void SetStatusBarText(CString txt) {m_wndStatusBar.SetPaneText(0,txt);};

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
	CDialogBar      m_wndSearchBar;
	CDialogBar      m_wndHighlightBar;

// Generated message map functions
protected:
	CSearchCombo m_wndSearchCombo;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHall();
	afx_msg void OnDohighlight();
	afx_msg void SetViewOptions(void);
	//}}AFX_MSG
	afx_msg void OnSearch();	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8D15FDFA_E2AE_4462_B0F6_2C6C4A63C924__INCLUDED_)
