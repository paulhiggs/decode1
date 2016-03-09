#if !defined(AFX_DALSURICHEDIT_H__6081508D_AA8B_11D2_9D7B_00207415044C__INCLUDED_)
#define AFX_DALSURICHEDIT_H__6081508D_AA8B_11D2_9D7B_00207415044C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DalsuRichEdit.h : header file (In Korean Version)...
//
/*************************************************************************
	
	CDalsuRichEdit�� ���Ͽ�
	������:�Ϲ������� chatter�� ������ ���, ������ �޽����� �Ʒ��κ���
			 �߰��Ǿ�� �ϸ�, ��ΰ� ���� ������ ���� ���, �ڵ������� �� 
			 ĭ�� �Ʒ��� ��ũ�ѵǾ�� �Ѵ�.
			 ���� ��ȭ���� �̸��� ��ȭ����, chatter���� �߰��Ǵ� �޽����� 
			 ���еȴ�.
	�Լ��� ���� ����:
			 1. AddName(CString &strName, COLORREF &crColor);
				�̸��� �̸��� ������ �����ϸ�ȴ�.
				��, �̸��� ���鶧, ������ ������ �����ϵ��� �ϸ� ���� ����.
				(���� ����)

			 2. AddText(CString &strTextIn, COLORREF &crColor);
				�߰��� text�� text�� ������ �����Ѵ�.
				��, �ݵ�� text�� ������ '\r\n'�� �����Ǿ� �־�� �Ѵ�. �׷���
				�������� �����ٷ� �̾�����.

			 3. AddMsg(CString &strMsg, COLORREF &crColor, BOOL bUnderLine, BOOL bBold);
				�߰��� �޽����� �޽����� ����, ������ ����, �������� ���� ������ �� �ִ�.
				���������� ������ '\r\n'�� �����Ǿ� �־�� �Ѵ�.

  To Use the CDalsuRichEdit...
  1. Copy "DalsuRichEdit.h", "DalsuRichEdit.cpp" in your work directory
  2. Add your project these two files
  3. Add a member data ex:m_pDalRich or m_pDalRich
  4. Create the CDalRichEdit's Window with appropriate style

  The Description of member function
  1. AddName(CString &strName, COLORREF &crColor);
		Specify the User Name and its color

  2. AddText(CString &strTextIn, COLORREF &crColor);
		Specify text string and its color
		Don't forget! There are "\r\n" characters on the tail of this string.

  3. AddMsg(CString &strMsg, COLORREF &crColor, BOOL bUnderLine, BOOL bBold);
		It's general system message. ex:A User joined this room...
		In the same manner, there are "\r\n" characters on the tail of this string.

and I thank for Zafir Anjum, Tom Moor, Steve Dunn, Juraj Rojko 's codes...
  
***************************************************************************/
/////////////////////////////////////////////////////////////////////////////
// CDalsuRichEdit window

class CDalsuRichEdit : public CRichEditCtrl
{
// Construction
public:
	CDalsuRichEdit();

// Attributes
public:

// Operations
public:
	void AddText(LPCTSTR szTextIn, COLORREF &crNewColor);
	void AddText(CString &strTextIn, COLORREF &crNewColor);
	void AddName(CString &strName, COLORREF &crNewColor);
	void AddMsg(CString &strMSG, COLORREF &crNewColor, BOOL bUnderLine = FALSE, BOOL bBold = FALSE);
	void Clear();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDalsuRichEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDalsuRichEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDalsuRichEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DALSURICHEDIT_H__6081508D_AA8B_11D2_9D7B_00207415044C__INCLUDED_)
