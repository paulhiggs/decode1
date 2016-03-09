#if !defined(AFX_RHTMLVIEW_H__5AD4907B_3395_11D3_B906_00C0F00CC0B3__INCLUDED_)
#define AFX_RHTMLVIEW_H__5AD4907B_3395_11D3_B906_00C0F00CC0B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RHtmlView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RHtmlView html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

#include "ROleControlSite.h"

class RHtmlView : public CHtmlView
{
protected:
	RHtmlView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(RHtmlView)

// XDocHostUI_DblClk interface
	DWORD GetXDocHostUI_DblClk();
	void SetXDocHostUI_DblClk(DWORD dwSet);

// XDocHostUI_Flag interface
	DWORD GetXDocHostUI_Flag();
	void SetXDocHostUI_Flag(DWORD dwSet);

	BOOL GetXDocHostUIFlag_Dialog();
	BOOL GetXDocHostUIFlag_DisableHelpMenu();
	BOOL GetXDocHostUIFlag_No3dBorder();
	BOOL GetXDocHostUIFlag_ScrollNo();
	BOOL GetXDocHostUIFlag_DisableScriptInactive();
	BOOL GetXDocHostUIFlag_OpenNewWin();
	BOOL GetXDocHostUIFlag_DisableOffscreen();
	BOOL GetXDocHostUIFlag_FlatScrollbar();
	BOOL GetXDocHostUIFlag_DivBlockDefault();
	BOOL GetXDocHostUIFlag_ActivateClienthitOnly();

	void SetXDocHostUIFlag_Dialog(BOOL bSet);
	void SetXDocHostUIFlag_DisableHelpMenu(BOOL bSet);
	void SetXDocHostUIFlag_No3dBorder(BOOL bSet);
	void SetXDocHostUIFlag_ScrollNo(BOOL bSet);
	void SetXDocHostUIFlag_DisableScriptInactive(BOOL bSet);
	void SetXDocHostUIFlag_OpenNewWin(BOOL bSet);
	void SetXDocHostUIFlag_DisableOffscreen(BOOL bSet);
	void SetXDocHostUIFlag_FlatScrollbar(BOOL bSet);
	void SetXDocHostUIFlag_DivBlockDefault(BOOL bSet);
	void SetXDocHostUIFlag_ActivateClienthitOnly(BOOL bSet);

// Updated functions
	void RHtmlView::SetRegisterAsBrowser(BOOL bNewValue);
	void RHtmlView::SetRegisterAsDropTarget(BOOL bNewValue);
	void RHtmlView::SetSilent(BOOL bNewValue);
	void RHtmlView::SetTheaterMode(BOOL bNewValue);

	void ResetSearchParams();
	void ResetHighlightParams();
// html Data
public:
	//{{AFX_DATA(RHtmlView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	ROccManager m_pROccManager;

// Operations
public:
	void OnEditCut();
	void OnEditCopy(); 
	void OnEditPaste(); 
	void OnEditSelectall(); 
	void OnEditFind();

	HRESULT get_Width(long *pl);
	HRESULT put_Width(long Width);

	void FindText(CString searchText, long Flags = 2, BOOL bNNF = FALSE /*for internal use*/);
	void FindText2(CString searchText, long Flags = 2, CString matchStyle = "color: white; background-color: darkblue", CString searchID = "CHtmlView_Search");
	void ClearSearchResults(CString searchID = "CHtmlView_Search");

	void HighlightOnePhrase(CString searchText, long lFlags = 2, CString matchStyle = "background-color: yellow", CString searchID = "CHtmlView_Highlight");
	void HighlightAllLines(CString searchText, long Flags = 2, CString matchStyle = "background-color: yellow", CString searchID = "CHtmlView_Highlight");
	void ClearHighlightResults(CString searchID = "CHtmlView_Highlight");

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RHtmlView)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ExecIE(INT nCmdID);
	virtual ~RHtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(RHtmlView)
	afx_msg void OnContextMenu( CWnd* pWnd, CPoint pos );	
	afx_msg void OnViewFontsLargest();
	afx_msg void OnViewFontsLarge();
	afx_msg void OnViewFontsMedium();
	afx_msg void OnViewFontsSmall();
	afx_msg void OnViewFontsSmallest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XHTMLVIEW_H__5AD4907B_3395_11D3_B906_00C0F00CC0B3__INCLUDED_)
