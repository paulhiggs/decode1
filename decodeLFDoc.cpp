// decodeLFDoc.cpp : implementation of the CDecodeLFDoc class
//
//////////////////////////////////////////////////////////////////
//
// Revision information
//
//
//
//
// March 12 2002: ewcpahi:
//		Added support for different timestamp formats
//      UDPListen, "log file" and none
//
// March 6 2002: Changed the display formatting
//
//////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include "decoder.h"

#include <..\src\occimpl.h>
#include "decodeLFDoc.h"
#include "decodeLFView.h"

#include "MainFrm.h"

#include "BitSet.h"
#include "HTMLfmt.h"
#include "ISDN_defs.h"
#include "Decoders.h"

#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "GlobalVars.h"
extern GlobalVars gv;



/////////////////////////////////////////////////////////////////////////////
// CDecodeLFDoc

IMPLEMENT_DYNCREATE(CDecodeLFDoc, CDocument)

BEGIN_MESSAGE_MAP(CDecodeLFDoc, CDocument)
	//{{AFX_MSG_MAP(CDecodeLFDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecodeLFDoc construction/destruction

CDecodeLFDoc::CDecodeLFDoc()
{
	// TODO: add one-time construction code here
	m_sTempFileName = _tempnam("c:\\","LDec");
	m_bHasDecodeContent = false;
}

CDecodeLFDoc::~CDecodeLFDoc()
{
}

BOOL CDecodeLFDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CDecodeLFDoc::OnCloseDocument()
{
	DeleteFile(m_sTempFileName);
}


/////////////////////////////////////////////////////////////////////////////
// CDecodeLFDoc serialization

void CDecodeLFDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDecodeLFDoc diagnostics

#ifdef _DEBUG
void CDecodeLFDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDecodeLFDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDecodeLFDoc commands



static void decodeLine(ofstream f, CString cs, int tsMode)
{
	cs.TrimLeft(); cs.TrimRight();

	if (cs.Find("O_FSM::NEW STATE:") != -1 )
		decodeNewState(f,cs,"O_FSM::NEW STATE:", tsMode);
	else if ( cs.Find("--> send") != -1 )
		decodeSignal(f,cs,"--> send", tsMode);
	else if ( cs.Find("--< receive") != -1 )
		decodeSignal(f,cs,"--< receive", tsMode);
	else if (cs.Find("O_FSM::log_event") != -1 )
		decodeLogEvent(f,cs,"O_FSM::log_event", tsMode);
	else if (cs.Find("*****ISDN Message") != -1 ) {
		decodeISDNMessage(f,cs,tsMode );
	}
	else
		decodeOther(f,cs, tsMode);
	f << Break << endl;

}

/*
void CDecodeLFDoc::SetStatusBarText(CString txt)
{
   POSITION pos = GetFirstViewPosition();
   while (pos != NULL)
   {
		CDecodeLFView* pView = (CDecodeLFView *)GetNextView(pos);
		CMainFrame *mf = (CMainFrame *)(pView->GetParentFrame());
		if ( mf != NULL )
		{
			mf->SetStatusBarText( txt );
		}
		pView->UpdateWindow();
   }   
}
*/

BOOL CDecodeLFDoc::DecodeLogfile()
{
	return DecodeLogfile(gv.g_splitLine ? gv.g_lineDelim : "", gv.g_timestampMode );
}



BOOL CDecodeLFDoc::DecodeLogfile(CString splitAt, int tsMode/*=TIMESTAMP_UDPLISTEN*/)
{
	//SetStatusBarText("Decoding");
	ofstream f(m_sTempFileName, ios::out|ios::trunc);
	if ( f == NULL )
		return false;

	ifstream i(m_sLogFileName, ios::in);
	if ( i == NULL )
	{
		f.close();
		return false;
	}

	f << sHTML << "<head>" << StyleList << "</head>";
	f << sBody << /*sFontSize(-1) <<*/ endl;

	char ibuf[4096];
	while ( !i.eof() ) {
		i.getline(&ibuf[0],sizeof(ibuf),'\n');
		CString cs = ibuf;
		if ( splitAt != "" )
		{
			int c = cs.GetLength();
			int b = 0;
			int a = cs.Find(splitAt,b+1);
			if ( a == -1 )
				decodeLine(f,cs, tsMode);
			else {
				do {
					decodeLine(f,cs.Mid(b,a-b), tsMode);
					b=a;
					a=cs.Find(splitAt,b+1);
				} while ( a != -1);
				decodeLine(f,cs.Right(cs.GetLength()-b),tsMode);
			}
		}
		else
			decodeLine(f,cs, tsMode);
	}
	m_bHasDecodeContent = true;

	f << eFont << eBody << eHTML << endl;

	f.close();
	i.close();
	UpdateAllViews(NULL);
	return true;
}


BOOL CDecodeLFDoc::OnOpenDocument(LPCTSTR lpszPathName)
{

	BOOL t = CDocument::OnOpenDocument(lpszPathName);
	if ( t ) {
		HCURSOR hSaveCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
		m_sLogFileName = lpszPathName;
		t = DecodeLogfile();
		SetCursor(hSaveCursor);
	}
	
	return t;
}

