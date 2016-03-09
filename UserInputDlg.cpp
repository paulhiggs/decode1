// UserInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "decoder.h"
#include "UserInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserInputDlg dialog


CUserInputDlg::CUserInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserInputDlg)
	m_UserInput = _T("");
	//}}AFX_DATA_INIT
	
}


void CUserInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserInputDlg)
	DDX_Text(pDX, IDC_ISDNMESSAGE, m_UserInput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserInputDlg, CDialog)
	//{{AFX_MSG_MAP(CUserInputDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInputDlg message handlers


void CUserInputDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

int CUserInputDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}


BOOL CUserInputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CWnd *p=GetDlgItem(IDC_ISDNMESSAGE);
	GotoDlgCtrl(p);
	return FALSE;
}

