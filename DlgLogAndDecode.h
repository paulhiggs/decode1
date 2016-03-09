#if !defined(AFX_DLGLOGANDDECODE_H__555AE80F_DB7D_453A_A6AC_A2552B14D772__INCLUDED_)
#define AFX_DLGLOGANDDECODE_H__555AE80F_DB7D_453A_A6AC_A2552B14D772__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogAndDecode.h : header file
//
#include <winsock2.h>

#include "DalsuRichEdit.h"

typedef enum eventtype {
	eNetworkEvent = 0,
	eAbortEvent,
	eKeypressEvent,
	cntEvents };

typedef struct {
	WSAEVENT		events[cntEvents];
	SOCKET			sRecv;	
	CDalsuRichEdit	*m_pDalRich;
} sLogThreadParams;

/////////////////////////////////////////////////////////////////////////////
// CDlgLogAndDecode dialog

class CDlgLogAndDecode : public CDialog
{
// Construction
public:
	CDlgLogAndDecode(CWnd* pParent);   // standard constructor
	~CDlgLogAndDecode();			   // and destructor
	BOOL Create();

// Dialog Data
	//{{AFX_DATA(CDlgLogAndDecode)
	enum { IDD = IDD_RT_LOG_AND_DECODE };
	int		m_PortNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogAndDecode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog(); 
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd			*m_pParent;
	int				m_nID;
//	CDalsuRichEdit	*m_pDalRich;


	// Generated message map functions
	//{{AFX_MSG(CDlgLogAndDecode)
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();
	afx_msg void OnCancel();
	afx_msg void OnOk();
	afx_msg void OnBtnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	sLogThreadParams  loggingCfg;
private:
	DWORD		dwLoggingThreadId;
	HANDLE		hLoggingThread;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGANDDECODE_H__555AE80F_DB7D_453A_A6AC_A2552B14D772__INCLUDED_)
