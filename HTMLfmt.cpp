#include "stdafx.h"

#include "HTMLfmt.h"

ostream &Break( ostream &stream )
{
	stream << _T("<br>");
	return stream;
}
const char *FontOff = "</span>";
const char *ErrorFontOn = "<span class=\"error\">";
const char *ErrorFontOff = FontOff;
const char *InfoMessageOn = "<span class=\"info\">";
const char *InfoMessageOff = FontOff;
const char *HighlightFontOn = "<span class=\"highlight\">";
const char *HighlightFontOff = FontOff;
const char *FilterFontOn = "<span class=\"filter\">";
const char *FilterFontOff = FontOff;
const char *SelectorFontOn = "<span class=\"select\">";
const char *SelectorFontOff = FontOff;
const char *ISDNMessageOn = "<span class=\"isdnmessage\">";
const char *ISDNMessageOff = FontOff;
const char *ISDNDecodeOn = "<span class=\"isdndecode\">";
const char *ISDNDecodeOff = FontOff;


const char *StyleList = "<style typ=\"text/css\">\n"
		" .rowtype {font-family: courier; font-size:small; font-style:normal;}\n"
		" BODY {white-space: nowrap; font-family: arial; font-size:small;}\n"
		" .normal {font-family: arial; font-size:small;}\n"
		" .info {font-family: arial; font-size:small; font-style: italic;}\n"
		" .highlight {font-family: arial; font-size:small; color:blue;}\n"
		" .error {font-family: arial; font-size:small; color:red;}\n"
		" .select {font-family: arial; font-size:small; color:green;}\n"
		" .filter {font-family: arial; font-size:small; color:fuchsia; font-style: italic;}\n"
		" .isdnmessage {font-family: arial; font-size:small; color:lime; font-style: normal;}\n"
		" .isdndecode {font-family: arial; font-size:small; color:lime; font-style: italic;}\n"
		"</style>\n";


ostream &sItalic( ostream &stream )
{
	stream << _T("<i>");
	return stream;
}

ostream &eItalic( ostream &stream )
{
	stream << _T("</i>");
	return stream;
}

ostream &sHTML( ostream &stream )
{
	stream << _T("<html>");
	return stream;
}

ostream &eHTML( ostream &stream )
{
	stream << _T("</html>");
	return stream;
}

ostream &sBody( ostream &stream )
{
	stream << _T("<body>");
	return stream;
}

ostream &sBody( ostream &stream, int width )
{
	stream << "<body width=\"" << width << "\">";
	return stream;
}

OMANIP (int) sBody( int width )
{
	return OMANIP (int)(sBody, width);
}

ostream &eBody( ostream &stream )
{
	stream << _T("</body>");
	return stream;
}

ostream &sFont( ostream &stream, int face )
{
	if ( face == FONT_COURIER )
		stream << "<font face=courier>";
	return stream;
}

OMANIP (int) sFont( int face )
{
	return OMANIP (int)(sFont, face);
}

ostream &sFontSize( ostream &stream, int size )
{
	stream << "<font size=\"" << size << "\">";
	return stream;
}

OMANIP (int) sFontSize( int size )
{
	return OMANIP (int)(sFontSize, size);
}

ostream &eFont( ostream &stream )
{
	stream << _T("</font>");
	return stream;
}




ostream &HexOutput( ostream &stream, BYTE b )
{


	long saveFlags = stream.setf(ios::hex);
	stream << "0x" << setfill('0') << setw(2) << (int)b << setfill(' ');
	stream.unsetf(ios::hex);

	return stream;
}
OMANIP (BYTE) HexOutput( BYTE b )
{
	return OMANIP (BYTE)(HexOutput, b);
}




ostream &Recommendation( ostream &stream, cchar_ptr recs )
{
	bool hasMultiple = (strchr(recs,',')!=NULL);

	stream << "Recommendation";
	if ( hasMultiple ) {
		char seps[] = ",", *token;
		bool firstTok = true;
		stream << "s ";
		token = strtok((char *)recs,seps);
		while (token != NULL) {
			if ( !firstTok )
				stream << ", ";
			stream << token;
			token = strtok(NULL,seps);
			firstTok = false;
		}
	}
	else 
		stream << " " << recs;
	return stream;
}

OMANIP (cchar_ptr) Recommendation( cchar_ptr recs )
{
	return OMANIP (cchar_ptr)(Recommendation, recs);
}



ostream &DontWrap( ostream &stream, cchar_ptr line )
{
	// convert all ' ' to "&nbsp;"

/*
	CString t = line;
	t.Replace(_T(" "),_T("&nbsp"));
	stream << t;
*/
/*
	bool inCtrl = false;
	cchar_ptr p=line;
	while (*p != '\0') {
		if ( (*p == '<') && !inCtrl ) {
			inCtrl = true;
			stream << *p;
		} 
		else if ( (*p == '>') && inCtrl ) {
			inCtrl = false;
			stream << *p;
		} 
		else if ( (*p == ' ') && !inCtrl )
			stream << "&nbsp;";
		else
			stream << *p;
		p++;
	}
*/
	stream << line;
	return stream;
}

OMANIP (cchar_ptr) DontWrap( cchar_ptr line )
{
	return OMANIP (cchar_ptr)(DontWrap, line);
}