// LFOptionsDlg.cpp : implementation file
//

//////////////////////////////////////////////////////////////////
//
// Revision information
//
//
// March 22 2002: ewcpahi:
//		Added support for multiple WebSwitch versions
// April 8 2002: ewcpahi:
//		Added support for decoding the ISDN message in the log file
//
//////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "decoder.h"
#include "LFOptionsDlg.h"
#include "GlobalDefs.h"
#include "types.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLFOptionsDlg dialog

#include "GlobalVars.h"
extern GlobalVars gv;

extern WSInfoElements DecodeStrings[];

CLFOptionsDlg::CLFOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLFOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLFOptionsDlg)
	m_Versions = _T("");
	//}}AFX_DATA_INIT
}

void CLFOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLFOptionsDlg)
	DDX_Radio(pDX, IDC_NONE, gv.g_timestampMode);
	DDX_Check(pDX, IDC_FORCE_CR, gv.g_splitLine);
	DDX_Text(pDX, IDC_NEWLINE_DELIM, gv.g_lineDelim);
	DDX_Check(pDX, IDC_DROPCALLFILTER, gv.g_dropCallFilter);
	DDX_Check(pDX, IDC_DECODEISDNINOG, gv.g_doISDNdecode);
	DDX_CBString(pDX, IDC_VERSION_SELECT, m_Versions);
	//}}AFX_DATA_MAP

	if ( pDX->m_bSaveAndValidate ) {
		CComboBox *p = (CComboBox *)GetDlgItem(IDC_VERSION_SELECT);
		gv.g_decodeVersion = p->GetItemData(p->GetCurSel());
	}
}


BEGIN_MESSAGE_MAP(CLFOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CLFOptionsDlg)
	ON_BN_CLICKED(IDC_FORCE_CR, OnForceCr)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLFOptionsDlg message handlers


void CLFOptionsDlg::OnForceCr() 
{
//	UpdateData();
	// TODO: Add your control notification handler code here
	ConfigureControls();
}

void CLFOptionsDlg::ConfigureControls() 
{
	GetDlgItem(IDC_CONDITION)->EnableWindow(gv.g_splitLine);
	GetDlgItem(IDC_NEWLINE_DELIM)->EnableWindow(gv.g_splitLine);
}


int CLFOptionsDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DoModal();
}

BOOL CLFOptionsDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(IDD, pParentWnd);
}

BOOL CLFOptionsDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreCreateWindow(cs);
}

void CLFOptionsDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

BOOL CLFOptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ConfigureControls();

	WSInfoElements *p = &DecodeStrings[0];
	CComboBox *verSelect = ((CComboBox *)GetDlgItem(IDC_VERSION_SELECT));
	if ( p != NULL && verSelect != NULL ) {
		while ( p->ver != NULL ) {
			int i = verSelect->AddString(p->ver);
			if ( i == CB_ERR )
				break;
			verSelect->SetItemData(i,p->nVer);
			if ( gv.g_decodeVersion == p->nVer )
				verSelect->SetCurSel(i);
			p++;
		}
		if ( gv.g_decodeVersion == 0 )
			verSelect->SetCurSel(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
