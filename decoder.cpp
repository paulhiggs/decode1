// decoder.cpp : Defines the class behaviors for the application.
//


#include "stdafx.h"
#include "decoder.h"

#include <..\src\occimpl.h>
#include "MainFrm.h"
#include "decodeIMFrm.h"
#include "decodeIMDoc.h"
#include "decodeIMView.h"
#include "decodeLFFrm.h"
#include "decodeLFDoc.h"
#include "decodeLFView.h"

#include "DlgLogAndDecode.h"

#include "types.h"
#include "VersionNo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// information stored in the registry
#include "GlobalVars.h"
GlobalVars gv;

/////////////////////////////////////////////////////////////////////////////
// CDecode1App

BEGIN_MESSAGE_MAP(CDecoderApp, CWinApp)
	//{{AFX_MSG_MAP(CDecoderApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEWMSG, OnFileNewMsg)
	ON_COMMAND(ID_FILE_OPENLOG, OnFileNewLog)
	ON_COMMAND(ID_FILE_SAVE, DoFileSave)
	ON_COMMAND(ID_FILE_REALTIME, DoRealtimeLogAndDecode)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


void CDecoderApp::DoFileSave()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDecoderApp construction

CDecoderApp::CDecoderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// CDecoderApp destruction

CDecoderApp::~CDecoderApp()
{
	// TODO: add destruction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDecoderApp object

CDecoderApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CDecoderApp initialization

BOOL CDecoderApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Ericsson"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	gv.g_timestampMode = GetProfileInt("Timestamp Settings","Mode",TIMESTAMP_UDPLISTEN);
	gv.g_splitLine = GetProfileInt("Lineparse Options", "Do Split", 0 );
	gv.g_lineDelim = GetProfileString("Lineparse Options", "Delimiter", "" );
	gv.g_decodeVersion = GetProfileInt("Lineparse Options", "DecodeVersion", 0 );
	gv.g_dropCallFilter = GetProfileInt("Filter Options", "POPDropped Calls", 0 );
	gv.g_doISDNdecode = GetProfileInt("Decoding Options", "ISDNinLog", 1 );

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pLFTemplate;
	pLFTemplate = new CMultiDocTemplate(
		IDR_LOGFILE,
		RUNTIME_CLASS(CDecodeLFDoc),
		RUNTIME_CLASS(CDecodeLFFrm), // custom MDI child frame
		RUNTIME_CLASS(CDecodeLFView));
	AddDocTemplate(pLFTemplate);

	CMultiDocTemplate* pIMTemplate;
	pIMTemplate = new CMultiDocTemplate(
		IDR_MESSAGE,
		RUNTIME_CLASS(CDecodeIMDoc),
		RUNTIME_CLASS(CDecodeIMFrm), // custom MDI child frame
		RUNTIME_CLASS(CDecodeIMView));
	AddDocTemplate(pIMTemplate);
/*
	CMultiDocTemplate* pRTTemplate;
	pRTTemplate = new CMultiDocTemplate(
		IDR_REALTIME,
		RUNTIME_CLASS(CDecodeRTDoc),
		RUNTIME_CLASS(CDecodeRTFrm), // custom MDI child frame
		RUNTIME_CLASS(CDecodeRTView));
	AddDocTemplate(pRTTemplate);
*/
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
/*
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
*/
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


int CDecoderApp::ExitInstance()
{
	WriteProfileInt("Timestamp Settings","Mode",gv.g_timestampMode);
	WriteProfileInt("Lineparse Options", "Do Split", gv.g_splitLine );
	WriteProfileString("Lineparse Options", "Delimiter", gv.g_lineDelim );
	WriteProfileInt("Lineparse Options", "DecodeVersion", gv.g_decodeVersion );
	WriteProfileInt("Filter Options", "POPDropped Calls", gv.g_dropCallFilter );
	WriteProfileInt("Decoding Options", "ISDNinLog", gv.g_doISDNdecode );


	// close any open windows
	CloseAllDocuments(FALSE);

	return CWinApp::ExitInstance();
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	int DoModal(HINSTANCE parent);
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT

}

int CAboutDlg::DoModal(HINSTANCE parent)
{
	return CDialog::DoModal();
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
	
	TCHAR buff[128];
	LoadString(NULL,IDR_MAINFRAME,buff,128);
	_tcscat(buff,_T(" version "));
	_tcscat(buff,_T(STRPRODUCTVER));
	SetDlgItemText(IDC_APP_AND_VER,buff);
}




BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDecoderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal(m_hInstance);
}

/////////////////////////////////////////////////////////////////////////////
// CDecoderApp message handlers

// The following two command handlers provides an
// alternative way to open documents by hiding the fact
// that the application has multiple templates. The
// default method uses a dialog with a listing of
// possible types to choose from.

void CDecoderApp::OnFileNewMsg()
{

// Searches template list for a document type
// containing the "Message" string

	POSITION curTemplatePos = GetFirstDocTemplatePosition();

	while(curTemplatePos != NULL)
	{
		CDocTemplate* curTemplate =
			GetNextDocTemplate(curTemplatePos);
		CString str;
		curTemplate->GetDocString(str, CDocTemplate::docName);
		if(str == _T("Message"))
		{
			CDocument *newDoc = curTemplate->OpenDocumentFile(NULL);
//			if ( newDoc != NULL && newDoc->GetDocTemplate() == NULL )
//				curTemplate->AddDocument(newDoc);
			return;
		}
	}
}

void CDecoderApp::OnFileNewLog()
{
// Searches template list for a document type
// containing the "Log" string

	POSITION curTemplatePos = GetFirstDocTemplatePosition();

	while(curTemplatePos != NULL)
	{
		CDocTemplate* curTemplate =
			GetNextDocTemplate(curTemplatePos);
		CString str;
		curTemplate->GetDocString(str, CDocTemplate::docName);
		if(str == _T("Log"))
		{
			// prompt the user (with all document templates)
			CString newName;
			if (!DoPromptFileName(newName, AFX_IDS_OPENFILE,
					OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
				return; // open cancelled

			// if returns NULL, the user has already been alerted
			CDocument *newDoc = curTemplate->OpenDocumentFile(newName);
//			if ( newDoc != NULL && newDoc->GetDocTemplate() == NULL )
//				curTemplate->AddDocument(newDoc);
			return;
		}
	}
}



void CDecoderApp::DoRealtimeLogAndDecode()
{
// Searches template list for a document type
// containing the "Log" string

	CDlgLogAndDecode *dlgRT = new CDlgLogAndDecode(NULL);

	if ( dlgRT->Create() == TRUE )
	{
	}

/*
	POSITION curTemplatePos = GetFirstDocTemplatePosition();

	while(curTemplatePos != NULL)
	{
		CDocTemplate* curTemplate =
			GetNextDocTemplate(curTemplatePos);
		CString str;
		curTemplate->GetDocString(str, CDocTemplate::docName);
		if(str == _T("Realtime"))
		{
			// prompt the user (with all document templates)
			curTemplate->AddDocument(curTemplate->OpenDocumentFile(NULL));
			return;
		}
	}
*/
}