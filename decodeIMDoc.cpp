// DecodeIMDoc.cpp : implementation of the CDecodeIMDoc class
//
//////////////////////////////////////////////////////////////////
//
// Revision information
//
//
//
//
// March 13 2002: ewcpahi:
//		Added additional IEs based on Q.931 05/98 recommendation
// April 8 2002: ewcpahi
//      Changed format of IE names so that single- and multi-
//		octet elements have the same decoded appearance
//
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "decoder.h"

#include "DecodeIMDoc.h"

#include "BitSet.h"
#include "HTMLfmt.h"
#include "ISDN_defs.h"
#include "Decoders.h"
#include "DecodeIEUtils.h"

#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMDoc

IMPLEMENT_DYNCREATE(CDecodeIMDoc, CDocument)

BEGIN_MESSAGE_MAP(CDecodeIMDoc, CDocument)
	//{{AFX_MSG_MAP(CDecodeIMDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMDoc construction/destruction

CDecodeIMDoc::CDecodeIMDoc()
{
	// TODO: add one-time construction code here
	m_sTempFileName = _tempnam("c:\\","IDec");
	m_bHasDecodeContent = false;
	m_sLastMessage = "";
}

CDecodeIMDoc::~CDecodeIMDoc()
{
}

#include "UserInputDlg.h"

BOOL CDecodeIMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	CUserInputDlg userInputDlg;
	userInputDlg.m_UserInput = getLastMessage();
	if (userInputDlg.DoModal() == IDOK)
		DecodeMessage(userInputDlg.m_UserInput);

	return TRUE;
}

void CDecodeIMDoc::OnCloseDocument()
{
	DeleteFile(m_sTempFileName);
}

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMDoc serialization

void CDecodeIMDoc::Serialize(CArchive& ar)
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
// CDecodeIMDoc diagnostics

#ifdef _DEBUG
void CDecodeIMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDecodeIMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDecodeIMDoc commands

#define INDENT_SIZE	3

static BYTE HexValue(TCHAR c)
{
	if (!isxdigit(c))
		return 0;

	if ( c >= '0' && c <= '9')
		return c - '0';
	if ( c >= 'A' && c <= 'F' )
		return (c - 'A') + 10;

	return 0;

}

class CPException
{
public:
    CPException(){};
    ~CPException(){};
    const char *ShowReason() const { return "Exception in CPException class."; }

};


static BYTE GetByte(CString message, int index) 
{
	if (index*2+1 > message.GetLength() )
		throw CPException();

	TCHAR c1 = toupper(message.GetAt(index*2));
	TCHAR c2 = toupper(message.GetAt(index*2+1));
	
	return (HexValue(c1)*16) + HexValue(c2);
}

static void SetFont(ofstream f, eMessageMode MessageMode )
{
	switch (MessageMode) {
		case mandatory:
			f << "<font color=blue>";
			break;
		case optional:
			f << "<font color=green>";
			break;
		case other:
			f << "<font color=red>";
			break;
	}
}


void DecodeISDNMessage(ofstream f, CString message )
{
	sGlobalDefs gvars;
	gvars.GlobalCallReference = false;
	bool decodeOk = true;
	int bi=0;

	message.TrimLeft(); message.TrimRight();
	BYTE Protocol=0;
	try {
		Protocol=GetByte(message,bi++);
		SetFont(f,ElementType(0,IE_PROTOCOL_DISCRIMINATOR));
		decodeOk=DecodeProtocol(f,INDENT_SIZE,Protocol);
		f<<eFont;
		f<<Break<<endl;
	} catch (CPException se) {
		decodeOk=false;
	}

	
	BYTE crefl;
	if ( decodeOk ) {
		try {
			crefl = GetByte(message,bi++);
		} catch (CPException se) {
			decodeOk=false;
		}
	}
	if ( decodeOk ) {
		SetFont(f,ElementType(0,IE_CALL_REFERENCE));
		decodeOk=DecodeCallReferenceLength(f,3,crefl);
		if (decodeOk) {
			int callRefLen = (crefl & 0x0f);  // should be one or two only
			if ( callRefLen != 0 )
			{
				BYTE CallRef[2] = { 0,0 };
				for (int j=0; j<crefl; j++)
				try {
					CallRef[j]=GetByte(message,bi++);
				}
				catch (CPException se) {
					f<<"**Not enough Call Reference data**"<<Break<<endl;
					decodeOk = false;
				}
				if ( decodeOk ) 
					DecodeCallReference(f,INDENT_SIZE,crefl,CallRef[0],CallRef[1]);
			}
		}
		f<<eFont;
		f<<Break<<endl;
	}

    BYTE MessageType;
    if ( decodeOk ) {
		try {
			MessageType = GetByte(message,bi++);
		} catch (CPException se) {
			decodeOk=false;
		}
	}

	CBitSet elements;
	if ( decodeOk ) {
		SetFont(f,ElementType(MessageType,IE_MESSAGE_TYPE));
		DecodeMessageType(f,INDENT_SIZE,Protocol,MessageType);
		f<<eFont<<endl;
    }

	gvars.ActiveCodeSet = 0;
    int LastActiveCodeSet=0;
	bool decodeDone=false;
    while ( decodeOk && !decodeDone) {
		int ie;
		try {
			ie = GetByte(message,bi++);
		} catch (CPException se) {
			decodeDone=true;
			continue;
		}
		f << Break << endl;
		if ( (ie & 0x80) == 0x80 ) {
			// single octet Information Element
			SetFont(f,ElementType(MessageType,ie));
			if (ie==IE_SENDING_COMPLETE) {
				f << "ie=" << HexOutput(ie) << Break << "IE="<<IEname(MAKE_FULLIE(gvars.ActiveCodeSet,ie)) << Break << endl;
			}
			else if (ie==IE_MORE_DATA) {
				f << "ie=" << HexOutput(ie) << Break << "IE="<<IEname(MAKE_FULLIE(gvars.ActiveCodeSet,ie)) << Break << endl;
			} 
			else {
				BYTE d[1]; 
				switch (ie&0xf0) {
					case IE_RESERVED:
						f << "ie=" << HexOutput(ie) << Break << "IE=" << IEname(MAKE_FULLIE(gvars.ActiveCodeSet,ie)) << Break << endl;
						break;
					case IE_SHIFT:
						f << "ie=" << HexOutput(ie) << Break << "IE=" << IEname(MAKE_FULLIE(gvars.ActiveCodeSet,ie)) << Break << endl;
						d[0]=ie;
						DecodeShift(f,3,&gvars,d);
						break;
					case IE_CONGESTION_LEVEL:
						f << "ie=" << HexOutput(ie) << Break << "IE=" << IEname(MAKE_FULLIE(gvars.ActiveCodeSet,ie)) << Break << endl;
						d[0]=ie;
						DecodeCongestionLevel(f,3,&gvars,d);
						break;
					case IE_REPEAT_INDICATOR:
						f << "ie=" << HexOutput(ie) << Break << "IE=" << IEname(MAKE_FULLIE(gvars.ActiveCodeSet,ie)) << Break << endl;
						d[0]=ie;
						DecodeRepeatIndication(f,3,&gvars,d);
						break;
					default:
						f << "**invalid Single Octet IE** (" << HexOutput(ie) << ")" << Break << endl;
						decodeOk = false;
				}
			}
			f<<eFont<<endl;
		}
		else {
			// multiple octet Information Element
			SetFont(f,ElementType(MessageType,ie));
			int ielen;
			try {
				ielen = GetByte(message,bi++);
			} catch (CPException se ) {
				// IE is missing its length
				f << "No IE Length for ie=" << HexOutput(ie) << Break << endl;
				decodeOk = false;
				continue;
			}
			if ( ielen == 0 ) {
				f << "IE length cannot be zero for ie=" << HexOutput(ie) << Break << endl;
				decodeOk = false;
				continue;
			}
			f << "ie=" << HexOutput(ie) << " len=" << HexOutput(ielen) << " data=";
			int dstat = bi;
			BYTE iea[64];
			memset(iea,0,sizeof(iea));
			try {
				iea[0]=0xff;
				for (int i=0; i<ielen; i++)
				{
					int ieb = GetByte(message,dstat++);
					f << " " << HexOutput(ieb);
					iea[i+1]=ieb;
					iea[0]=i+1;
				}
			} catch (CPException se) {
				f << " **more expected**";
				decodeOk=false;
			}
			f << Break << endl;

			if ( decodeOk ) {
				elements.setBit(ie);
				f << "IE=" << IEname(MAKE_FULLIE(gvars.ActiveCodeSet,ie)) << Break << endl;
				psIEDecoderEntry p = &IEDecoders[0];
				if ( p != NULL ) {
					while (p->DecodeFunction!=NULL) {
						if ((p->CodeSet==gvars.ActiveCodeSet) && ((p->IEid&p->IEidMask)==(ie&p->IEidMask))) {
							(p->DecodeFunction)(f,INDENT_SIZE,&gvars,iea);
							break;
						}
						p++;
					}
					if ( p->DecodeFunction == NULL )
						f<<DrawIndent(INDENT_SIZE)<<"!!!NO DECODERS INSTALLED FOR codeset="<<HexOutput(gvars.ActiveCodeSet)<<" ie="<<HexOutput(ie)<<"!!!"<<Break<<endl;
				}
				else 
					f<<DrawIndent(INDENT_SIZE)<<"!!!NO DECODERS INSTALLED!!!"<<Break<<endl;
			}
			f << eFont;
			bi = dstat;
		}
		// decrement the vars->LockCount. If its zero, restore the ActiveCodeSet
		if ( gvars.LockCount > 0 ) {
			gvars.LockCount--;
			if ( gvars.LockCount == 0 )
				gvars.ActiveCodeSet = gvars.LastCodeSet;
		}
    }
/*
	if ( decodeOk ) {
		// Can add some sanity check here to ensure that all the mandatory fields were entered
		if ( Protocol == PROTOCOL_Q931) {
			switch (MessageType) {
			case MESSAGE_ALERTING:
				break;
			case MESSAGE_CALL_PROCEEDING:
				break;
			case MESSAGE_CONNECT:
				break;
			case MESSAGE_CONNECT_ACKNOWLEDGE:
				break;
			case MESSAGE_PROGRESS:
				break;
			case MESSAGE_SETUP:
				break;
			case MESSAGE_SETUP_ACKNOWLEDGE:
				break;
			case MESSAGE_RESUME:
				break;
			case MESSAGE_RESUME_ACKNOWLEDGE:
				break;
			case MESSAGE_RESUME_REJECT:
				break;
			case MESSAGE_SUSPEND:
				break;
			case MESSAGE_SUSPEND_ACKNOWLEDGE:
				break;
			case MESSAGE_SUSPEND_REJECT:
				break;
			case MESSAGE_USER_INFORMATION:
				break;
			case MESSAGE_DISCONNECT:
				break;
			case MESSAGE_RELEASE:
				break;
			case MESSAGE_RELEASE_COMPLETE:
				break;
			case MESSAGE_RESTART:
				break;
			case MESSAGE_RESTART_ACKNOWLEDGE:
				break;
			case MESSAGE_SEGMENT:
				break;
			case MESSAGE_CONGESTION_CONTROL:
				break;
			case MESSAGE_INFORMATION:
				break;
			case MESSAGE_FACILITY:
				break;
			case MESSAGE_FACILITY_REJECT:
				break;
			case MESSAGE_NOTIFY:
				break;
			case MESSAGE_STATUS:
				break;
			case MESSAGE_STATUS_ENQUIRY:
				break;
			default:
				decodeOk=false;
				break;
			}
		}
		if ( Protocol == PROTOCOL_MAINTENANCE ) {
			switch (MessageType) {
			case MESSAGE_SERVICE:
				break;
			case MESSAGE_SERVICE_ACKNOWLEDGE:
				break;
			default:
				decodeOk=false;
				break;
			}
		}
	}
*/
}

BOOL CDecodeIMDoc::DecodeMessage(CString message)
{
	ofstream f(m_sTempFileName, ios::out|ios::trunc);
	if ( f == NULL ||message.GetLength()==0)
		return false;

	m_sLastMessage = message;
	m_bHasDecodeContent = true;

	f << sHTML << "<head>" << StyleList << "</head>";
	f << sBody << sFont(FONT_COURIER) << message << eFont << Break << endl;

	DecodeISDNMessage(f,message);

	f << eBody << eHTML << endl;

	f.close();

	UpdateAllViews(NULL);
	return true;
}


