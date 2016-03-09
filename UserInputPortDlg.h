#if !defined(AFX_USERINPUTPORTDLG_H__24161529_D802_499F_814E_1A4E98D040DC__INCLUDED_)
#define AFX_USERINPUTPORTDLG_H__24161529_D802_499F_814E_1A4E98D040DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserInputPortDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserInputPortDlg dialog

class CUserInputPortDlg : public CDialog
{
// Construction
public:
	CUserInputPortDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserInputPortDlg)
	enum { IDD = IDD_USERINPUTPORTBOX };
	UINT	m_portNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInputPortDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserInputPortDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERINPUTPORTDLG_H__24161529_D802_499F_814E_1A4E98D040DC__INCLUDED_)
