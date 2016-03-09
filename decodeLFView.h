// DecodeLFView.h : interface of the CDecodeLFView class
//
/////////////////////////////////////////////////////////////////////////////

#include "RHtmlView.h"

#if !defined(AFX_DecodeLFView_H__6D3779C2_576A_4A41_81A6_7164A63ED412__INCLUDED_)
#define AFX_DecodeLFView_H__6D3779C2_576A_4A41_81A6_7164A63ED412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDecodeLFView : public RHtmlView
{
protected: // create from serialization only
	CDecodeLFView();
	DECLARE_DYNCREATE(CDecodeLFView)

// Attributes
public:
	CDecodeLFDoc* GetDocument();
private:
	void OpenLogfile(void);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecodeLFView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnEditCopy();
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDecodeLFView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDecodeLFView)
	afx_msg void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);
	afx_msg void SetViewOptions(void);
	afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in DecodeLFView.cpp
inline CDecodeLFDoc* CDecodeLFView::GetDocument()
   { return (CDecodeLFDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DecodeLFView_H__6D3779C2_576A_4A41_81A6_7164A63ED412__INCLUDED_)
