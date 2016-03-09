#if !defined(AFX_LFOPTIONSDLG_H__4373D5BF_B591_4780_8A84_5A2E229139E5__INCLUDED_)
#define AFX_LFOPTIONSDLG_H__4373D5BF_B591_4780_8A84_5A2E229139E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LFOptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLFOptionsDlg dialog

class CLFOptionsDlg : public CDialog
{
// Construction
public:
	CLFOptionsDlg(CWnd* pParent = NULL);   // standard constructor
	void ConfigureControls(void);

// Dialog Data
	//{{AFX_DATA(CLFOptionsDlg)
	enum { IDD = IDD_LFOPTIONS };
	CString	m_Versions;
	//}}AFX_DATA
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLFOptionsDlg)
	public:
	virtual int DoModal();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLFOptionsDlg)
	afx_msg void OnForceCr();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LFOPTIONSDLG_H__4373D5BF_B591_4780_8A84_5A2E229139E5__INCLUDED_)
