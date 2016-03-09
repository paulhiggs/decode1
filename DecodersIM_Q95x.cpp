#include "stdafx.h"
#include "DecodersIM_Q95x.h"
#include "DecodersIM_Q931.h"

#include "HTMLfmt.h"
#include "ISDN_defs.h"

#include "DecodeIEUtils.h"


void DecodePrecedenceLevel(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecoderNotImplemented(f,indent,data,"PrecedenceLevel");
}


// as defined in 5.4/Q.951
void DecodeConnectedNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodeNumber(f,indent,data);
}


void DecodeConnectedSubaddress(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodeCalledPartySubaddress(f,indent,vars,data);
}


void DecodeRedirectingNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	int hasExt=0;
    DisplayDecodeOctet(f,indent,data[1]);
	DecodeExtBit(f,indent,data[1]);
	DecodeTypeOfNumber(f,indent,data[1]);
	DecodeNumberPlanID(f,indent,data[1]);
	if (ExtBitClear(data[1])) {
		hasExt++;
		DisplayDecodeOctet(f,indent,data[1+hasExt]);
		DecodeExtBit(f,indent,data[1+hasExt]);
		DecodePresentationIndicator(f,indent,data[1+hasExt]);
		DecodeSpare(f,indent,data[1+hasExt],5,3);
		DecodeScreeningIndicator(f,indent,data[1+hasExt]);

		if ( ExtBitClear(data[1+hasExt])) {
			hasExt++;
			DisplayDecodeOctet(f,indent,data[1+hasExt]);
			DecodeExtBit(f,indent,data[1+hasExt]);
			DecodeSpare(f,indent,data[1+hasExt],7,5);
			DecodeReasonForRedirection(f,indent,data[1+hasExt]);
			
		}
	}
	DisplayChars(f,indent,data,2+hasExt,data[0]);
}


void DecodeRedirectionNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	int hasExt=0;
    DisplayDecodeOctet(f,indent,data[1]);
	DecodeExtBit(f,indent,data[1]);
	DecodeTypeOfNumber(f,indent,data[1]);
	DecodeNumberPlanID(f,indent,data[1]);
	if (ExtBitClear(data[1])) {
		hasExt++;
		DisplayDecodeOctet(f,indent,data[1+hasExt]);
		DecodeExtBit(f,indent,data[1+hasExt]);
		DecodePresentationIndicator(f,indent,data[1+hasExt]);
		DecodeSpare(f,indent,data[1+hasExt],5,3);
		DecodeScreeningIndicator(f,indent,data[1+hasExt]);
	}
	DisplayChars(f,indent,data,2+hasExt,data[0]);
}

