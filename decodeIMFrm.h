// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DecodeIMFrm_H__44D94832_0116_4651_AF8A_EDD17835581F__INCLUDED_)
#define AFX_DecodeIMFrm_H__44D94832_0116_4651_AF8A_EDD17835581F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDecodeIMFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CDecodeIMFrm)
public:
	CDecodeIMFrm();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecodeIMFrm)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDecodeIMFrm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CDecodeIMFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DecodeIMFrm_H__44D94832_0116_4651_AF8A_EDD17835581F__INCLUDED_)
