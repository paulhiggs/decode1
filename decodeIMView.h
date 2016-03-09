// DecodeIMView.h : interface of the CDecodeIMView class
//
/////////////////////////////////////////////////////////////////////////////

#include "RHtmlView.h"

#if !defined(AFX_DecodeIMView_H__6D3779C2_576A_4A41_81A6_7164A63ED412__INCLUDED_)
#define AFX_DecodeIMView_H__6D3779C2_576A_4A41_81A6_7164A63ED412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDecodeIMView : public RHtmlView
{
protected: // create from serialization only
	CDecodeIMView();
	DECLARE_DYNCREATE(CDecodeIMView)

// Attributes
public:
	CDecodeIMDoc* GetDocument();
private:
	void GetUserInput(void);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecodeIMView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDecodeIMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDecodeIMView)
	afx_msg void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DecodeIMView.cpp
inline CDecodeIMDoc* CDecodeIMView::GetDocument()
   { return (CDecodeIMDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_DecodeIMView_H__6D3779C2_576A_4A41_81A6_7164A63ED412__INCLUDED_)
