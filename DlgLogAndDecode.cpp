// DlgLogAndDecode.cpp : implementation file
//


#include "stdafx.h"
#include "decoder.h"
#include "DlgLogAndDecode.h"
#include "DalsuRichEdit.h"

#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment( lib, "ws2_32.lib" )

void StripCRLF( char *buf )
{
	char *buf2 = strdup( buf );
	char seps[] = "\n\r";
	char *token = strtok( buf2, seps );

	strcpy( buf, "" );
	while ( token != NULL )
	{
		strcat( buf, token );
		token = strtok( NULL, seps );
	}
	free( buf2 );
}

/////////////////////////////////////////////////////////////////////////////
// CDlgLogAndDecode dialog


static char *WindowTitle = "Realtime Log and Decode";
static COLORREF crRed = RGB(255,0,0), crBlue = RGB(0,0,255);

CDlgLogAndDecode::CDlgLogAndDecode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogAndDecode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogAndDecode)
	m_PortNo = 1;
	//}}AFX_DATA_INIT
//	ASSERT(pParent != NULL);

	loggingCfg.m_pDalRich = NULL;
	m_pParent = pParent;
	m_nID = CDlgLogAndDecode::IDD;

	for ( int i = 0; i < cntEvents; i++ )
		loggingCfg.events[ i ] = CreateEvent( NULL, FALSE, FALSE, NULL );
}

CDlgLogAndDecode::~CDlgLogAndDecode()
{
	for ( int i = 0; i < cntEvents; i++ )
		CloseHandle( loggingCfg.events[ i ] );
}

void CDlgLogAndDecode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogAndDecode)
	DDX_Text(pDX, IDC_PORTNO, m_PortNo);
	DDV_MinMaxInt(pDX, m_PortNo, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogAndDecode, CDialog)
	//{{AFX_MSG_MAP(CDlgLogAndDecode)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogAndDecode message handlers
DWORD WINAPI StartLogging(LPVOID lpParameter) 
{
	bool	loopDone = false;
	DWORD	dwWaitResult;
	char	rBuf[ 2048 ], tBuf[ 20 ];
	int		len;
	
	sLogThreadParams *p = (sLogThreadParams *)lpParameter;
	CDalsuRichEdit *eCtrl = p->m_pDalRich;

	while ( !loopDone ) {
		dwWaitResult = WSAWaitForMultipleEvents(cntEvents, p->events, FALSE, WSA_INFINITE, TRUE);
		switch ( dwWaitResult )
		{
			case (WSA_WAIT_EVENT_0 + eNetworkEvent):
				len = recvfrom( p->sRecv, rBuf, sizeof(rBuf), 0, NULL, NULL );
				rBuf[len] = '\0';
				StripCRLF( rBuf );
				time_t ltime;
				time( &ltime );
				struct tm now;
				memcpy( &now, localtime( &ltime ), sizeof(now) );
				sprintf( tBuf, "(%02d:%02d:%02d) ", now.tm_hour, now.tm_min, now.tm_sec );
	
				eCtrl->AddText(tBuf,crBlue);
				eCtrl->AddText(rBuf,crBlue);
				eCtrl->AddText("\n",crBlue);
//				cout << tBuf << rBuf << endl << flush;

#ifdef DO_MESSAGEPARSE
				if ( decode )
					DecodeMessage( rBuf );
#endif
				break;
			case (WSA_WAIT_EVENT_0 + eAbortEvent):
				eCtrl->AddText("Stopping...\n",crBlue);
				loopDone = true;
				break;
			case (WSA_WAIT_EVENT_0 + eKeypressEvent):
/*				switch ( toupper(chKeyHit) ) 
				{
					case 'L':
						// toggle program logging
						additionalLogging = !additionalLogging;
						cout << TIMEPAD << "Additional logging turned " << ( additionalLogging ? "ON" : "OFF" ) << endl;
						break;
					case 'M':
						// record a marker in the file
						break;
					case 'C':
						// close the log file
						break;
					case 'O':
						//open the log file
						break;
					case 'Q':
						// key press to quit the application
						loopdone = true;
						break;
				}*/
				break;
			default:
				sprintf(rBuf,"Error in event wait...(err=%d)",WSAGetLastError());
				eCtrl->AddText(rBuf,crRed);
				loopDone = true;
				break;
		}
	}
	return 0;
}

void CDlgLogAndDecode::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTN_START)->EnableWindow(false);
	GetDlgItem(IDC_PORTNO)->EnableWindow(false);
	GetDlgItem(IDC_PORTNO_LABEL)->EnableWindow(false);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(true);


	UpdateData();
	char buf[128];
	sprintf(buf,"%s (port=%d)", WindowTitle, m_PortNo );
	SetWindowText(buf);

	WSADATA wsaData;
	int err = WSAStartup( MAKEWORD( 2, 0 ), &wsaData );
	if ( err != 0 )
	{
		sprintf(buf, "Failed to start networking, Error=%d\n", WSAGetLastError() );
		loggingCfg.m_pDalRich->AddText(buf,crRed);
		OnBtnStop();
		return;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 ) 
	{
		loggingCfg.m_pDalRich->AddText("Insufficient networking support",crRed);
		OnBtnStop();
		return;
	}
	if ( (loggingCfg.sRecv = socket( AF_INET, SOCK_DGRAM, 0 )) == INVALID_SOCKET )
	{
		sprintf(buf, "Failed to obtain a socket (err=%d)\n", WSAGetLastError() );
		loggingCfg.m_pDalRich->AddText(buf,crRed);
		OnBtnStop();
		return;
	}
    struct sockaddr_in local;
//	int port = atoi(argv[1]);

//	sscanf( argv[1], strchr(argv[1],'x') || strchr(argv[1],'X') ? "%x" : "%d", &port );

    local.sin_port = htons(m_PortNo);
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;

    if ( loggingCfg.sRecv != INVALID_SOCKET && bind(loggingCfg.sRecv, (struct sockaddr *)&local, sizeof(local) ) == SOCKET_ERROR )
	{
		sprintf(buf, "Specified port already in use (err=%d)\n", WSAGetLastError() );
		loggingCfg.m_pDalRich->AddText(buf,crRed);
		OnBtnStop();
		return;
	}
	else {
		sprintf(buf, "Listening on port %d\n", m_PortNo );
		loggingCfg.m_pDalRich->AddText(buf,crBlue);
	}
	WSAEventSelect( loggingCfg.sRecv, loggingCfg.events[ eNetworkEvent ], FD_READ ); 

	hLoggingThread = ::CreateThread( NULL, 0, StartLogging, (LPVOID)&loggingCfg, 0, &dwLoggingThreadId );
}

void CDlgLogAndDecode::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	SetEvent( loggingCfg.events[eAbortEvent] );
	GetDlgItem(IDC_BTN_START)->EnableWindow(true);
	GetDlgItem(IDC_PORTNO)->EnableWindow(true);
	GetDlgItem(IDC_PORTNO_LABEL)->EnableWindow(true);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(false);

	SetWindowText(WindowTitle);
	CloseHandle( hLoggingThread );
	closesocket(loggingCfg.sRecv);
}


void CDlgLogAndDecode::OnCancel()
{
	// TODO: Add your control notification handler code here
	DestroyWindow();
}

void CDlgLogAndDecode::OnOk()
{
	// TODO: Add your control notification handler code here
	OnBtnStop();
	DestroyWindow();
}


void CDlgLogAndDecode::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;

	//CDialog::PostNcDestroy();
}

BOOL CDlgLogAndDecode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(false);

	CRect rc;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_RICHEDIT);
	pWnd->GetWindowRect(&rc);
	ScreenToClient(&rc);

	loggingCfg.m_pDalRich = new CDalsuRichEdit;
	loggingCfg.m_pDalRich->Create(WS_VISIBLE | WS_CHILD |WS_BORDER | WS_HSCROLL | 
					WS_CLIPCHILDREN | WS_VSCROLL | ES_MULTILINE | ES_AUTOHSCROLL | ES_READONLY |
					ES_AUTOVSCROLL |ES_LEFT | ES_WANTRETURN, rc, this, IDC_STATIC_RICHEDIT);

	CFont *cf;
	cf = loggingCfg.m_pDalRich->GetFont();
	loggingCfg.m_pDalRich->SetFont(cf,TRUE);
	
	SetWindowText(WindowTitle);

	GetDlgItem(IDC_PORTNO)->SetFocus();

	return FALSE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlgLogAndDecode::Create()
{
	return CDialog::Create(m_nID, m_pParent);
}

void CDlgLogAndDecode::OnBtnClear() 
{
	// TODO: Add your control notification handler code here
	loggingCfg.m_pDalRich->Clear();
}
