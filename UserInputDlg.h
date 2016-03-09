#if !defined(AFX_USERINPUTDLG_H__A2703BB5_4934_4386_9123_A408C1A5F8A6__INCLUDED_)
#define AFX_USERINPUTDLG_H__A2703BB5_4934_4386_9123_A408C1A5F8A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserInputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserInputDlg dialog

class CUserInputDlg : public CDialog
{
// Construction
public:
	CUserInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserInputDlg)
	enum { IDD = IDD_USERINPUTBOX };
	CString	m_UserInput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInputDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual BOOL OnInitDialog( );

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserInputDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERINPUTDLG_H__A2703BB5_4934_4386_9123_A408C1A5F8A6__INCLUDED_)
