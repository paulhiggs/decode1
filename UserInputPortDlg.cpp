// UserInputPortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "decoder.h"
#include "UserInputPortDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserInputPortDlg dialog


CUserInputPortDlg::CUserInputPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInputPortDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserInputPortDlg)
	m_portNumber = 0;
	//}}AFX_DATA_INIT
}


void CUserInputPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserInputPortDlg)
	DDX_Text(pDX, IDC_PORTNO, m_portNumber);
	DDV_MinMaxUInt(pDX, m_portNumber, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserInputPortDlg, CDialog)
	//{{AFX_MSG_MAP(CUserInputPortDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInputPortDlg message handlers
