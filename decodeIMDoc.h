// DecodeIMDoc.h : interface of the CDecodeIMDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DecodeIMDoc_H__17C73EAC_D853_44E3_9169_379D9E32370B__INCLUDED_)
#define AFX_DecodeIMDoc_H__17C73EAC_D853_44E3_9169_379D9E32370B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDecodeIMDoc : public CDocument
{
protected: // create from serialization only
	CDecodeIMDoc();
	DECLARE_DYNCREATE(CDecodeIMDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecodeIMDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString getLastMessage() { return m_sLastMessage; };
	bool hasDecodeContent() { return m_bHasDecodeContent; };
	CString getDecodeFile() { return m_sTempFileName; };
	BOOL DecodeMessage(CString message);
	virtual ~CDecodeIMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDecodeIMDoc)
	afx_msg void OnCloseDocument();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool m_bHasDecodeContent;
	CString m_sTempFileName;
	CString m_sLastMessage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DecodeIMDoc_H__17C73EAC_D853_44E3_9169_379D9E32370B__INCLUDED_)
