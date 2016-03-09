#if !defined(AFX_SEARCHCOMBO_H__E7772356_E10C_4205_92EC_4AEAF2595233__INCLUDED_)
#define AFX_SEARCHCOMBO_H__E7772356_E10C_4205_92EC_4AEAF2595233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchCombo window

class CSearchCombo : public CComboBox
{
// Construction
public:
	CSearchCombo();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchCombo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSearchCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSearchCombo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHCOMBO_H__E7772356_E10C_4205_92EC_4AEAF2595233__INCLUDED_)
