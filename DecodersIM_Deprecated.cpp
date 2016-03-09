#include "stdafx.h"
#include "DecodersIM_Deprecated.h"

#include "HTMLfmt.h"
#include "ISDN_defs.h"

#include "DecodeIEUtils.h"



// Decode the Connected Number information element
void DecodeConnectedAddress(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
    DecodeNumber(f, indent, data );
}


void DecodeTerminalCapabilities(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecoderNotImplemented(f,indent,data,"TerminalCapabilities");
}


void DecodeKeypadEcho(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecoderNotImplemented(f,indent,data,"KeypadEcho");
}


void DecodeSwitchhook(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecoderNotImplemented(f,indent,data,"Switchhook");
}

