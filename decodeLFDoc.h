// decodeLFDoc.h : interface of the CDecode1Doc class
//
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//
// Revision information
//
//
//
// March 12 2002: ewcpahi:
//		Added support for different timestamp formats
//      UDPListen, "log file" and none
//
//////////////////////////////////////////////////////////////////

#if !defined(AFX_DECODELFDOC_H__17C73EAC_D853_44E3_9169_379D9E32370B__INCLUDED_)
#define AFX_DECODELFDOC_H__17C73EAC_D853_44E3_9169_379D9E32370B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GlobalDefs.h"

class CDecodeLFDoc : public CDocument
{
protected: // create from serialization only
	CDecodeLFDoc();
	DECLARE_DYNCREATE(CDecodeLFDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecodeLFDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool hasDecodeContent() { return m_bHasDecodeContent; };
	CString getDecodeFile() { return m_sTempFileName; };
	BOOL DecodeLogfile();
	BOOL DecodeLogfile(CString splitAt, int tsMode=TIMESTAMP_UDPLISTEN);
	virtual ~CDecodeLFDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void SetStatusBarText(CString txt);

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDecodeLFDoc)
	afx_msg BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnCloseDocument();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool m_bHasDecodeContent;
	CString m_sLogFileName;
	CString m_sTempFileName;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECODELFDOC_H__17C73EAC_D853_44E3_9169_379D9E32370B__INCLUDED_)
