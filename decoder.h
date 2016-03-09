// decoder.h : main header file for the DECODER application
//

#if !defined(AFX_DECODER_H__41A38421_3A2D_4EFF_899C_100BBE1973EE__INCLUDED_)
#define AFX_DECODER_H__41A38421_3A2D_4EFF_899C_100BBE1973EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDecoderApp:
// See decoder.cpp for the implementation of this class
//
class CDecoderApp : public CWinApp
{
public:
	CDecoderApp();
	void DoFileSave();
	~CDecoderApp();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecoderApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDecoderApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNewMsg();
	afx_msg void OnFileNewLog();
	afx_msg void DoRealtimeLogAndDecode();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECODER_H__41A38421_3A2D_4EFF_899C_100BBE1973EE__INCLUDED_)
