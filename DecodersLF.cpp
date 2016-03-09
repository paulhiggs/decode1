//
// DecodersLF.cpp
//
//////////////////////////////////////////////////////////////////
//
// Revision information
//
//
// March 22 2002: ewcpahi:
//		Added support for multiple WebSwitch versions
// March 19 2002: ewcpahi:
//		Added a check for any dropped call strings and make appropriate highlighting
// March 12 2002: ewcpahi:
//		Added support for different timestamp formats
// March 6 2002: Changed the display formatting
// March 10 2002: Added decode of "log_event"
// April 8 2002: ewcpahi:
//		Added support for decoding the ISDN message in the log file
//
//////////////////////////////////////////////////////////////////

#include <ctype.h>

#include "stdafx.h"
#include "Decoders.h"
#include "GlobalDefs.h"

#include "HTMLfmt.h"
#include "ISDN_defs.h"

#include "StringTokenizer.h"

#include "PString.h"
#include "types.h"

#include "V262Data.h"
#include "V300Data.h"
#include "V301Data.h"
#include "V310Data.h"



#include <afxtempl.h>

#include "GlobalVars.h"
extern GlobalVars gv;

static int bDecodingISDN = false;
static CString csISDNBuffer = "";


void loadDecodeStrings(ofstream f);   // forward declaration

WSInfoElements DecodeStrings[] = {
	{ NameV310, 
		Ver310,
		SignalsV310, 
		StatesV310, 
		EventsV310 },
	{ NameV301, 
		Ver301,
		SignalsV301, 
		StatesV301, 
		EventsV301 },
	{ NameV300, 
		Ver300,
		SignalsV300, 
		StatesV300, 
		EventsV300 },
	{ NameV262, 
		Ver262,
		SignalsV262, 
		StatesV262, 
		EventsV262 },
	{NULL, NULL, NULL, NULL},
};



//*** SHARED FUNCTIONS *********************************************
static int makeInt16(CString s)
{
	int rc=0;
	for (int i=0; i<s.GetLength(); i++) {
		char ch = toupper(s[i]);
		if ((ch >= '0') && (ch <= '9')) {
			rc *= 16;
			rc += ch - '0';
		}
		else if ((ch >= 'A') && (ch <= 'F')) {
			rc *= 16;
			rc += (ch - 'A')+10;
		}
	}
	return rc;
}

static int makeInt10(CString s)
{
	int rc=0;
	for (int i=0; i<s.GetLength(); i++) {
		char ch = toupper(s[i]);
		if ((ch >= '0') || (ch <= '9')) {
			rc *= 10;
			rc += ch - '0';
		}
	}
	return rc;
}



typedef enum {
	nostate,
	filter,
	error,
	isdnmessage,
	isdndecode } sLineState;

#ifndef __LINESTATEDECLARED
#define __LINESTATEDECLARED
IOMANIPdeclare( sLineState )
#endif


ostream &WriteLineState( ostream &stream, sLineState state )
{
	stream << "<span class=\"rowtype\">";
	switch (state) {
		case error:
			stream << "ERR&nbsp;";
			break;
		case filter:
			stream << "FLT&nbsp;";
			break;
		case isdnmessage:
		case isdndecode:
		case nostate:
		default:
			stream << "&nbsp;&nbsp;&nbsp;&nbsp;";
			break;
	}
	stream << "</span>";
	return stream;
}
OMANIP (sLineState) WriteLineState( sLineState state )
{
	return OMANIP (sLineState)(WriteLineState, state);
}


ostream &WriteErrorLine( ostream &stream, cchar_ptr ln )
{
	stream << WriteLineState(error);
	stream << "<span class=\"error\">" << DontWrap(ln) << "</span>";
	return stream;
}
OMANIP (cchar_ptr) WriteErrorLine( cchar_ptr ln )
{
	return OMANIP (cchar_ptr)(WriteErrorLine, ln);
}


// this is in decodeIMDoc.cpp
extern void DecodeISDNMessage(ofstream f, CString message );



static void ShowISDNDecode(ofstream f, CString &c)
{
	f << Break << endl <<WriteLineState(isdndecode) << 
		ISDNDecodeOn << DontWrap(c) << ISDNDecodeOff << Break << endl;

	DecodeISDNMessage(f,c);

	c = "";
}



//*** STATE INTERPRETATION *****************************************
class PStateEntry : public CObject
{
public:
	PStateEntry();
	PStateEntry( CString fsm );
	PStateEntry(const PStateEntry& cp);
	~PStateEntry();
	void setFSM( CString fsm ) { m_fsm = fsm; };
	void addState( int state, CString desc );

	void reset();
	int getStateCount(void) { return m_highStateNo; };
	CString getState( int state );
	CString getFSM() { return m_fsm; };

	const PStateEntry& operator=(const PStateEntry& stringSrc);
	int Compare(LPCTSTR lpsz) const;
	operator LPCTSTR() const { return m_fsm; };


protected:
	CString m_fsm;
	CStringArray m_data;
	int m_highStateNo;
};

bool AFXAPI operator==(const PStateEntry& s1, const PStateEntry& s2) { return s1.Compare(s2) == 0; };
bool AFXAPI operator==(const PStateEntry& s1, LPCTSTR s2) { return s1.Compare(s2) == 0; };
bool AFXAPI operator==(LPCTSTR s1, const PStateEntry& s2) { return s2.Compare(s1) == 0; };

PStateEntry::PStateEntry()
{ 
	m_fsm = ""; 
	m_highStateNo = -1;
}

PStateEntry::PStateEntry( CString fsm ) 
{ 
	m_fsm = fsm; 
	m_highStateNo = -1; 
}

PStateEntry::PStateEntry(const PStateEntry& cp)
{
	m_fsm = cp.m_fsm;
	m_highStateNo = cp.m_highStateNo;
	for ( int i=0; i<cp.m_data.GetSize(); i++)
		m_data.SetAtGrow(i,cp.m_data.GetAt(i));
}

PStateEntry::~PStateEntry()
{ 
	m_data.RemoveAll();
}

const PStateEntry& PStateEntry::operator=(const PStateEntry& src)
{
	m_fsm = src.m_fsm;
	m_highStateNo = src.m_highStateNo;
	for ( int i=0; i<src.m_data.GetSize(); i++)
		m_data.SetAtGrow(i,src.m_data.GetAt(i));
	return *this;
}


void PStateEntry::addState(int state, CString desc) 
{ 
	m_data.SetAtGrow(state,desc); 
	if (state > m_highStateNo ) 
		m_highStateNo = state; 
}

CString PStateEntry::getState( int state ) 
{ 
	if (state > m_highStateNo) 
		return ""; 
	else return m_data.GetAt(state); 
}

void PStateEntry::reset()
{
	 m_data.RemoveAll();
	 m_fsm = "";
	 m_highStateNo = -1;
}

int PStateEntry::Compare(LPCTSTR lpsz) const
	{ ASSERT(AfxIsValidString(lpsz)); return _tcscmp(m_fsm, lpsz); }    // MBCS/Unicode aware



CArray<PStateEntry, PStateEntry&> StateList;



static int FindStateFSM( CString fsm )
{
	for (int i=0; i<StateList.GetSize(); i++ )
	{
		PStateEntry *p = (PStateEntry *)&StateList.GetAt(i);
		if (p->getFSM() == fsm)
			return i;
	}
	return -1;
}
static bool StateFSMdefined( CString fsm ) 
{
	return FindStateFSM( fsm ) >= 0;
}

static bool isStateFSM( CString s ) 
{
	// return true is s is a "known" FSM i.e. in the enumeration
    int us = s.Find("_");
    if ( us == -1 )
		return StateFSMdefined(s);
    else return StateFSMdefined(s.Mid(0,us));
}

static bool hasDate( CString s )
{
	int lb = s.Find("(");
	int rb = s.Find(")");
	int fs = s.Find(" ",rb);

	if ( lb == 0 && (rb + 1)==fs ) 
		return true;
	return false;
}




static CString getStateDescription( CString fsm, int state, bool &Ok)
{
	// Convert the provided "state" to something meaningful to the "fsm"
	Ok = false;
	char msg[256];
    int us = fsm.Find("_");
	CString g = (us == -1) ? fsm : fsm.Left(us);
	int p = FindStateFSM(g);
    if ( p == -1 ) {
		sprintf(msg,"%sUnknown FSM (%s,0x%x)%s",
					ErrorFontOn, fsm, state, ErrorFontOff );
	}
	else {
		CString s = StateList.GetAt(p).getState(state);
		if (s.GetLength() == 0 ) 
		{
			sprintf(msg,"%sUnknown STATE (0x%x)%s",
					ErrorFontOn, state, ErrorFontOff );
		}
		else {
			sprintf(msg,"%s%s (0x%x)%s",
				HighlightFontOn,s,state,HighlightFontOff );
			Ok = true;
		}
	}
  return msg;
}



static void showStates(ofstream f)
{
	if ( StateList.GetSize() == 0 )
		return;
	f << "*** STATE LIST ***" << Break << endl;
	for (int q=0; q<StateList.GetSize(); q++)
	{	
		f << "FSM=" << StateList.GetAt(q).getFSM() << Break << endl;
		for (int i=0; i<StateList.GetAt(q).getStateCount(); i++ )
			f << "State " << i << "=" << StateList.GetAt(q).getState(i) << Break << endl;
				
	};
	f << "******************" << Break << flush << endl;
}




static void loadStates(ofstream f, int ver)
{
	int m=0, fsmno=-1, stateno = -1;
	PStateEntry s;

	while (strcmp(DecodeStrings[ver].States[m],LIST_END)!=0) {
		PString p = DecodeStrings[ver].States[m];
		if (p.startsWith(FSM_ATTRIBUTE)) {
			fsmno++;
			s.reset();
			s.setFSM(p.Right(p.GetLength()-strlen(FSM_ATTRIBUTE)));
			StateList.SetAtGrow(fsmno,s);
			stateno=-1;
		}
		else {
			if ( fsmno >= 0 ) {
				stateno++;
				StateList.ElementAt(fsmno).addState(stateno,p);
			}
		}
		m++;
	}
//	showStates(f);
}



void decodeNewState(ofstream f, CString line, CString lineSelector, int timestampMode)
{
	if ( bDecodingISDN ) {
		bDecodingISDN = false;
		ShowISDNDecode(f, csISDNBuffer);
	}
	loadDecodeStrings(f);
	
	PString FSM="";

	if (timestampMode == TIMESTAMP_UDPLISTEN || (timestampMode == TIMESTAMP_LOGFILE && line.Find(",")==-1)) 
	{
		StringTokenizer st(line);
		FSM = st.nextToken();
		if ( FSM.startsWith("(") && FSM.endsWith(")") )
		{
			FSM = st.nextToken();
			if ( !isStateFSM( (CString)FSM ) ) {
				WriteErrorLine(line);
				return;
			}
		}
	} 
	else if (timestampMode == TIMESTAMP_LOGFILE)
	{
		// timestamp definately exists
		StringTokenizer st(line.Right(line.GetLength()-line.Find(",")-2));
		FSM = st.nextToken();
		if ( !isStateFSM( (CString)FSM ) ) {
			WriteErrorLine(line);
			return;
		}
	}

	line.Replace(FSM.GetBuffer(128),"<!FSM!>");
	CString replacePattern=SelectorFontOn + lineSelector + SelectorFontOff;
	line.Replace(lineSelector, replacePattern);

    CString STATE = "";
    int i = line.GetLength();
    while ( (line.GetAt(i-1) >= '0' && line.GetAt(i-1) <= '9')||(line.GetAt(i-1) >= 'a' && line.GetAt(i-1) <= 'f')||(line.GetAt(i-1) >= 'A' && line.GetAt(i-1) <= 'F')) {
		STATE = line.GetAt(i-1) + STATE;
		i--;
    }
    line=line.Left(i)+"<!STATE!>";
    // now the string is modified and we have FSM and STATE

    line.Replace("<!FSM!>", FSM );  // TODO: replace the FSM with more interesting description
	bool Ok;
    line.Replace("<!STATE!>", getStateDescription(FSM, makeInt16(STATE), Ok));

	//write out "line" on "f"
	f << WriteLineState(Ok?nostate:error)<< DontWrap(line);
}


//*** SIGNAL INTERPRETATION *****************************************
class PSignalEntry : public CObject
{
public:
	PSignalEntry();
	PSignalEntry(int tagno, CString tagname );
	PSignalEntry(const PSignalEntry& cp);
	~PSignalEntry();
	void setTag( int tagno, CString tagname ) { m_tagno=tagno; m_tagname=tagname; };
	int getTagNo() { return m_tagno; };
	CString getTagname()  { return m_tagname; };

	void addSignal(int signalno, CString signalname);
	CString getSignal( int signalno );
	int getHighSignalNo() { return m_highSigNo; };

	const PSignalEntry& operator=(const PSignalEntry& stringSrc);
	int Compare(LPCTSTR lpsz) const;
	operator LPCTSTR() const { return m_tagname; };

	void reset();

protected:
	int m_tagno;
	CString m_tagname;
	CStringArray m_data;
	int m_highSigNo;
};

int PSignalEntry::Compare(LPCTSTR lpsz) const
	{ ASSERT(AfxIsValidString(lpsz)); return _tcscmp(m_tagname, lpsz); }    // MBCS/Unicode aware

bool AFXAPI operator==(const PSignalEntry& s1, const PSignalEntry& s2)
	{ return s1.Compare(s2) == 0; }
bool AFXAPI operator==(const PSignalEntry& s1, LPCTSTR s2)
	{ return s1.Compare(s2) == 0; }
bool AFXAPI operator==(LPCTSTR s1, const PSignalEntry& s2)
	{ return s2.Compare(s1) == 0; }



PSignalEntry::PSignalEntry()
{ 
	m_tagno = -1;
	m_tagname = ""; 
	m_highSigNo = -1;
}

PSignalEntry::PSignalEntry( int tagno, CString tagname ) 
{ 
	m_tagno = tagno;
	m_tagname = tagname; 
	m_highSigNo = -1;
}

PSignalEntry::PSignalEntry(const PSignalEntry& cp)
{
	m_tagno = cp.m_tagno;
	m_tagname = cp.m_tagname;
	m_highSigNo = cp.m_highSigNo;
	for ( int i=0; i<cp.m_data.GetUpperBound(); i++)
		m_data.SetAtGrow(i,cp.m_data.GetAt(i));
}

PSignalEntry::~PSignalEntry()
{ 
	m_data.RemoveAll();
}

const PSignalEntry& PSignalEntry::operator=(const PSignalEntry& src)
{
	m_tagno =  src.m_tagno;
	m_tagname = src.m_tagname;
	for ( int i=0; i<src.m_data.GetUpperBound(); i++)
		m_data.SetAtGrow(i,src.m_data.GetAt(i));
	return *this;
}


void PSignalEntry::addSignal(int signalno, CString signalname)
{
	m_data.SetAtGrow(signalno,signalname);
	if ( signalno > m_highSigNo )
		m_highSigNo = signalno;
}


CString PSignalEntry::getSignal( int signalno )
{
	return m_data.GetAt(signalno);
}

void PSignalEntry::reset()
{
	m_data.RemoveAll();
	m_tagno = 0;
	m_tagname = "";
}



CArray<PSignalEntry,PSignalEntry&> SignalList;


static void showSignals(ofstream f)
{
	if ( SignalList.GetSize() == 0 )
		return;
	f << "*** SIGNAL LIST ***" << Break << endl;
	for (int q=0; q<SignalList.GetSize(); q++)
	{	
		f << "Tag=" << SignalList.GetAt(q).getTagname() << "(" << SignalList.GetAt(q).getTagNo() << ")" << Break << endl;
		for (int i=0; i<SignalList.GetAt(q).getHighSignalNo(); i++ )
			f << "Signal " << i << "=" << SignalList.GetAt(q).getSignal(i) << Break << endl;
				
	};
	f << "******************" << Break << flush << endl;
}

static void loadSignals(ofstream f, int ver)
{
	int m=0, tagno=-1, signo = -1;
	PSignalEntry s;

	while (strcmp(DecodeStrings[ver].Signals[m],LIST_END)!=0) {
		PString p = DecodeStrings[ver].Signals[m];
		if (p.startsWith(TAG_ATTRIBUTE)) {
			tagno++;
			s.reset();
			s.setTag(tagno,p.Right(p.GetLength()-strlen(TAG_ATTRIBUTE)));
			SignalList.SetAtGrow(tagno,s);
			signo=-1;
		}
		else {
			if ( tagno >= 0 ) {
				signo++;
				SignalList.ElementAt(tagno).addSignal(signo,p);
			}
		}
		m++;
	}
//	showSignals(f);
}


static bool fetchSignal( CString &t, int tag, int signal )
{
	char msg[256];
	bool ok = false;
	if (tag > (SignalList.GetSize()-1))
	{
		sprintf(msg,"%sNO_TAG[%i] sig=%i%s", ErrorFontOn, tag, signal, ErrorFontOff);
	} 
	else if (SignalList.ElementAt(tag).getHighSignalNo() < signal) {
		sprintf(msg,"%stag=%s %i NO_SIG[%i]%s", 
					ErrorFontOn, 
					SignalList.ElementAt(tag).getTagname(),
					tag, signal, ErrorFontOff);
	}
	else {
		sprintf(msg,"%s%s:%s (%i %i)%s",
			HighlightFontOn,
			SignalList.ElementAt(tag).getTagname(),
			SignalList.ElementAt(tag).getSignal(signal),
			tag, signal,
			HighlightFontOff );
		ok = true;
	}
	t = msg;
	return ok;
}

void decodeSignal(ofstream f, CString line, CString lineSelector, int timestampMode)
{
	if ( bDecodingISDN ) {
		bDecodingISDN = false;
		ShowISDNDecode(f, csISDNBuffer);
	}
	loadDecodeStrings(f);

	CString replacePattern=SelectorFontOn + lineSelector + SelectorFontOff;
	line.Replace(lineSelector, replacePattern);

	CString SignalMark = "Sig: ";
	int u = line.Find(SignalMark);
	if ( u == -1 ) {
		f << WriteErrorLine(line);
		return;
	}
	StringTokenizer st(line.Right(line.GetLength()-u-SignalMark.GetLength()));
	int tag = makeInt10(st.nextToken());
	int sig = makeInt10(st.nextToken());
	//write out "line" on "f"

	CString t;
	bool noErr = fetchSignal( t, tag, sig );
	f << WriteLineState(noErr?nostate:error)<<DontWrap(line.Left(u))<< DontWrap(SignalMark);
	f << DontWrap(t);
}







//*** LOG_EVNT INTERPRETATION ***************************************
class PEventEntry : public CObject
{
public:
	PEventEntry();
	PEventEntry( CString fsm );
	PEventEntry(const PEventEntry& cp);
	~PEventEntry();
	void setFSM( CString fsm ) { m_fsm = fsm; };
	void addEvent( int event, CString desc );

	void reset();
	int getEventCount(void) { return m_highEventNo; };
	CString getEvent( int event );
	CString getFSM() { return m_fsm; };

	const PEventEntry& operator=(const PEventEntry& stringSrc);
	int Compare(LPCTSTR lpsz) const;
	operator LPCTSTR() const { return m_fsm; };


protected:
	CString m_fsm;
	CStringArray m_data;
	int m_highEventNo;
};

bool AFXAPI operator==(const PEventEntry& s1, const PEventEntry& s2) { return s1.Compare(s2) == 0; };
bool AFXAPI operator==(const PEventEntry& s1, LPCTSTR s2) { return s1.Compare(s2) == 0; };
bool AFXAPI operator==(LPCTSTR s1, const PEventEntry& s2) { return s2.Compare(s1) == 0; };

PEventEntry::PEventEntry()
{ 
	m_fsm = ""; 
	m_highEventNo = -1;
}

PEventEntry::PEventEntry( CString fsm ) 
{ 
	m_fsm = fsm; 
	m_highEventNo = -1; 
}

PEventEntry::PEventEntry(const PEventEntry& cp)
{
	m_fsm = cp.m_fsm;
	m_highEventNo = cp.m_highEventNo;
	for ( int i=0; i<cp.m_data.GetSize(); i++)
		m_data.SetAtGrow(i,cp.m_data.GetAt(i));
}

PEventEntry::~PEventEntry()
{ 
	m_data.RemoveAll();
}

const PEventEntry& PEventEntry::operator=(const PEventEntry& src)
{
	m_fsm = src.m_fsm;
	m_highEventNo = src.m_highEventNo;
	for ( int i=0; i<src.m_data.GetSize(); i++)
		m_data.SetAtGrow(i,src.m_data.GetAt(i));
	return *this;
}


void PEventEntry::addEvent(int event, CString desc) 
{ 
	m_data.SetAtGrow(event,desc); 
	if (event > m_highEventNo ) 
		m_highEventNo = event; 
}

CString PEventEntry::getEvent( int event ) 
{ 
	if (event > m_highEventNo) 
		return ""; 
	else return m_data.GetAt(event); 
}

void PEventEntry::reset()
{
	 m_data.RemoveAll();
	 m_fsm = "";
	 m_highEventNo = -1;
}

int PEventEntry::Compare(LPCTSTR lpsz) const
	{ ASSERT(AfxIsValidString(lpsz)); return _tcscmp(m_fsm, lpsz); }    // MBCS/Unicode aware


CArray<PEventEntry,PEventEntry&> EventList;


static void showEvents(ofstream f)
{
	if ( EventList.GetSize() == 0 )
		return;
	f << "*** EVENT LIST ***" << Break << endl;
	for (int q=0; q<EventList.GetSize(); q++)
	{	
		f << "FSM=" << EventList.GetAt(q).getFSM() << Break << endl;
		for (int i=0; i<EventList.GetAt(q).getEventCount(); i++ )
			f << "Event " << i << "=" << EventList.GetAt(q).getEvent(i) << Break << endl;
				
	};
	f << "******************" << Break << flush << endl;
}


static void loadEvents(ofstream f, int ver)
{
	int m=0, fsmno=-1, eventno = -1;
	PEventEntry s;

	while (strcmp(DecodeStrings[ver].Events[m],LIST_END)!=0) {
		PString p = DecodeStrings[ver].Events[m];
		if (p.startsWith(FSM_ATTRIBUTE)) {
			fsmno++;
			s.reset();
			s.setFSM(p.Right(p.GetLength()-strlen(FSM_ATTRIBUTE)));
			EventList.SetAtGrow(fsmno,s);
			eventno=-1;
		}
		else {
			if ( fsmno >= 0 ) {
				eventno++;
				EventList.ElementAt(fsmno).addEvent(eventno,p);
			}
		}
		m++;
	}
//	showEvents(f);
}

static int readValue( CString &c, CString line, int startAt = 0 )
{
	// reads hexchars starting at position "startAt" from "line"
	// until end of line or ',' delimitor
	// resultant chars goe into "c"
	// return value is number of chars read
	c = "";
	int pos = startAt, len=line.GetLength();
	while ( pos < len && line[pos] != ',' ) 
	{
		if (_istxdigit(line[pos]))
			c += line[pos];
		pos++;
	}

	return c.GetLength();

}


static int FindEventFSM( CString fsm )
{
	
	for (int i=0; i<EventList.GetSize(); i++ )
	{
		if ( EventList.GetAt(i).getFSM() == fsm )
			return i;
	}
	return -1;
}
static bool EventFSMdefined( CString fsm ) 
{
	return FindEventFSM( fsm ) >= 0;
}

static bool isEventFSM( CString s ) 
{
	// return true is s is a "known" FSM i.e. in the enumeration
    int us = s.Find("_");
    if ( us == -1 )
		return StateFSMdefined(s);
    else return StateFSMdefined(s.Mid(0,us));
}


static CString getEventDescription( CString fsm, CString EventMark, int event, bool &Ok)
{
	// Convert the provided "event" to something meaningful to the "fsm"
	Ok = false;
	char msg[256];
    int us = fsm.Find("_");
	CString g = (us == -1) ? fsm : fsm.Left(us);
	int p = FindEventFSM(g);
    if ( p == -1 ) {
		sprintf(msg,"%sUnknown FSM (%s,%u)%s",
					ErrorFontOn, fsm, event, ErrorFontOff );
	}
	else {
		CString e = EventList.GetAt(p).getEvent(event);
		if (e.GetLength() == 0 ) 
		{
			sprintf(msg,"%sUnknown EVENT (%u)%s",
					ErrorFontOn, event, ErrorFontOff );
		}
		else {
			sprintf(msg,"%s%s (%u)%s",
				HighlightFontOn,e,event,HighlightFontOff );
			Ok = true;
		}
	}
  return msg;
}

static bool getEvent( CString &t,
						 CString FSM,
						 CString StateMark, int STATE,
						 CString EventMark, int EVENT )
{
	// already handled the FSM validity
	bool Ok;
	t = StateMark + getStateDescription(FSM, STATE, Ok);
	if ( !Ok ) {
		// state is not valid
		char t2[256];
		sprintf( t2, " %s%u", EventMark, EVENT );
		t += t2;
	}
	else {
		// state is valid
		t += " ";
		t += EventMark;
		t += getEventDescription(FSM, EventMark, EVENT, Ok);
	}

	return Ok;
}
	

void decodeLogEvent(ofstream f, CString line, CString lineSelector, int timestampMode)
{
	if ( bDecodingISDN ) {
		bDecodingISDN = false;
		ShowISDNDecode(f, csISDNBuffer);
	}
	// need states and events for line decode

	loadDecodeStrings(f);
	PString FSM = "";

	if (timestampMode == TIMESTAMP_UDPLISTEN || (timestampMode == TIMESTAMP_LOGFILE && line.Find(",")==-1)) 
	{
		StringTokenizer st(line);
		FSM = st.nextToken();
		if ( FSM.startsWith("(") && FSM.endsWith(")") )
		{
			FSM = st.nextToken();
			if ( !isEventFSM( (CString)FSM ) ) {
				f << WriteErrorLine(line);
				return;
			}
		}
	} 
	else if (timestampMode == TIMESTAMP_LOGFILE)
	{
		// timestamp definately exists
		StringTokenizer st(line.Right(line.GetLength()-line.Find(",")-2));
		FSM = st.nextToken();
		if ( !isEventFSM( (CString)FSM ) ) {
			f << WriteErrorLine(line);
			return;
		}
	}

	CString replacePattern=SelectorFontOn + lineSelector + SelectorFontOff;	
	line.Replace(lineSelector, replacePattern);

	
	CString StateStr, StateMark = "State: ";
	int u = line.Find(StateMark);
	if ( u == -1 ) {
		f << line;
		return;
	}
	CString EventStr, EventMark = "Event: ";
	int v = line.Find(EventMark);
	if ( v == -1 ) {
		f << line;
		return;
	}

	readValue(StateStr, line, u+StateMark.GetLength() );
	readValue(EventStr, line, v+EventMark.GetLength() );


 //   line.Replace("<!FSM!>", FSM );  // TODO: replace the FSM with more interesting description
	

	CString t;
	bool noErr = getEvent( t, FSM, StateMark, makeInt16(StateStr), EventMark, makeInt10(EventStr) );
	f << WriteLineState(noErr?nostate:error)<<DontWrap(line.Left(u));
	f << DontWrap(t);
}




//*** INFORMATION INTERPRETATION ***************************************

static bool CheckDroppedCall( CString line )
{
	bool hasDroppedMessage = 
		( ( line.Find("WEBSWITCH CLOSED an ONGOING call") != -1 ) ||
		  ( line.Find("Closed incoming call, lack of resources") != -1 ) ||
		  ( line.Find("CLOSED AN ONGOING call") != -1 ) ||
		  ( line.Find("Disconnect Request for call from XIPDRV") != -1 ) );

	return hasDroppedMessage;
}


void decodeOther(ofstream f, CString line, int timestampMode)
{
	PString TS = "";
	if (timestampMode == TIMESTAMP_UDPLISTEN || (timestampMode == TIMESTAMP_LOGFILE && line.Find(",")==-1)) 
	{
		StringTokenizer st(line);
		TS = st.nextToken();
		if ( TS.startsWith("(") && TS.endsWith(")") )
		{
		}
		else
			TS.Empty();
	} 
	else if (timestampMode == TIMESTAMP_LOGFILE)
	{
		// timestamp definately exists
		StringTokenizer st(line,',');
		TS = st.nextToken() + ",";
	}


	PString s = line.Right(line.GetLength()-TS.GetLength());
	if ( bDecodingISDN )
	{
		int x = s.ReverseFind(' ');
		if ( x == -1 )
		{
			bDecodingISDN = false;
			ShowISDNDecode(f, csISDNBuffer);
		}
		else {
			csISDNBuffer += s.Right(s.GetLength() - x - 1);
			f << WriteLineState(isdnmessage) << DontWrap(TS);
			f << ISDNMessageOn << DontWrap(s) << ISDNMessageOff;

			int il = s.GetLength();
			if ((il-x-1) != (2*40) ) {
				// incomplete line, must be done
				bDecodingISDN = false;
				ShowISDNDecode(f, csISDNBuffer);
			}
		}
	}
	else {
		bool    b = (gv.g_dropCallFilter != 0) & CheckDroppedCall(s);
		
	//	s.PrepHTML();
		f << WriteLineState((b)?filter:nostate) << DontWrap(TS);
		if (b) 
			f << FilterFontOn << DontWrap(s) << FilterFontOff;
		else f << InfoMessageOn << DontWrap(s) << InfoMessageOff;
	}
}


//*** ISDN INTERPRETATION ***************************************
void decodeISDNMessage(ofstream f, CString line, int timestampMode)
{
	if ( !gv.g_doISDNdecode )
	{
		decodeOther(f,line,timestampMode);
		return;
	}
	PString TS = "";
	if (timestampMode == TIMESTAMP_UDPLISTEN || (timestampMode == TIMESTAMP_LOGFILE && line.Find(",")==-1)) 
	{
		StringTokenizer st(line);
		TS = st.nextToken();
		if ( TS.startsWith("(") && TS.endsWith(")") )
		{
		}
		else
			TS.Empty();
	} 
	else if (timestampMode == TIMESTAMP_LOGFILE)
	{
		// timestamp definately exists
		StringTokenizer st(line,',');
		TS = st.nextToken() + ",";
	}


	PString s = line.Right(line.GetLength()-TS.GetLength());
	
//	s.PrepHTML();
	f << WriteLineState(isdnmessage) << DontWrap(TS);
	f << ISDNMessageOn << DontWrap(s) << ISDNMessageOff;
	bDecodingISDN=true;
}




//***************************************************************


static int loadedVersion = -1;

static void loadDecodeStrings(ofstream f)
{
	if ( loadedVersion == gv.g_decodeVersion )
		return;

	StateList.RemoveAll();
	EventList.RemoveAll();
	SignalList.RemoveAll();

	int i = 0;
	WSInfoElements *p = &DecodeStrings[i];
	if ( p != NULL ) {
		while ( p->ver != NULL ) {
			if (p->nVer == gv.g_decodeVersion) {
				loadStates(f, i);
				loadEvents(f, i);
				loadSignals(f, i);
				loadedVersion = gv.g_decodeVersion;
				break;
			}				
			i++;
			p++;
		}
	}
}
