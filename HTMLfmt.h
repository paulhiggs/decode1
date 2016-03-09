
#ifndef __HTMLTAGS_H__
#define __HTMLTAGS_H__

#pragma warning(disable:4270)

#include <iostream.h>
#include <iomanip.h>

#include <windows.h>

#ifndef __BYTEDECLARED
#define __BYTEDECLARED
IOMANIPdeclare( BYTE )
#endif

#ifndef __CHARPTRDECLARED
#define __CHARPTRDECLARED
typedef const char * cchar_ptr;
IOMANIPdeclare( cchar_ptr )
IOMANIPdeclare( LPCWSTR )
#endif


ostream &sItalic( ostream &stream );
ostream &eItalic( ostream &stream );
ostream &sHTML( ostream &stream );
ostream &eHTML( ostream &stream );


OMANIP (int) sBody( int body );
ostream &sBody( ostream &stream );
ostream &eBody( ostream &stream );


ostream &Break( ostream &stream );

#define FONT_COURIER	0x01

OMANIP (int) sFont( int face );
ostream &eFont( ostream &stream );

OMANIP (int) sFontSize( int size );
ostream &eFontSize( ostream &stream );

//not strictly an HTML thing but
ostream &HexOutput( ostream &stream, BYTE b );
OMANIP (BYTE) HexOutput( BYTE b );

extern const char *ErrorFontOn,		*ErrorFontOff;
extern const char *InfoMessageOn,	*InfoMessageOff;
extern const char *HighlightFontOn,	*HighlightFontOff;
extern const char *FilterFontOn,	*FilterFontOff;
extern const char *SelectorFontOn,	*SelectorFontOff;
extern const char *ISDNMessageOn,	*ISDNMessageOff;
extern const char *ISDNDecodeOn,	*ISDNDecodeOff;

extern const char *StyleList;

ostream &Recommendation( ostream &stream, cchar_ptr recs );
OMANIP (cchar_ptr) Recommendation( cchar_ptr recs );

ostream &DontWrap( ostream &stream, cchar_ptr line );
OMANIP (cchar_ptr) DontWrap( cchar_ptr line );

#endif