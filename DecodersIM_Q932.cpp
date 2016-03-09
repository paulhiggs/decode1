#include "stdafx.h"
#include "DecodersIM_Q932.h"

#include "HTMLfmt.h"
#include "ISDN_defs.h"

#include "DecodeIEUtils.h"


void DecodeExtendedFacility(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecoderNotImplemented(f,indent,data,"ExtendedFacility");
}



// Decode the Facility information element
void DecodeFacility(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
    int hasExt = 0;
    if (ExtBitClear(data[1])) hasExt = 1;
    DecodeSpare(f,indent,data[1],7,6);
    DrawBits(f,indent,data[1],5,1,"Protocol profile=");
    switch (data[1]&0x1f) {
		case 0x11:
			f<<"Remote Operations protocol"; break;
		case 0x12:
			f<<"CMIP Protocol ("<<Recommendation("Q.941")<<")"; break;
		case 0x13:
			f<<"ACSE Protocol ("<<Recommendation("X.217,X.227")<<")"; break;
		case 0x1f:
			f<<"Network extensions"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;

    if ( hasExt==1 ) {
		//decode octet 4 as 3a
		DisplayDecodeOctet(f,indent,data[2]);
		DecodeExtBit(f,indent,data[2]);
		DrawBits(f,indent,data[1],7,1,"Service identifier=");
		switch (data[1]&0x7f) {
			case 0x70:
				f<<"Network Message Service (NMS)"; break;
			case 0x7e:
				f<<"Network Automatic Call Distribution (NACD)"; break;
			case 0x7f:
				f<<"Network Ring Again (NRAG)"; break;
			default:
				f<<USAGE_RESERVED;
		}
		f<<Break<<endl;
    }
	for (int j=2+hasExt, cnt=0; j<=data[0]; j++)
	{
      f<<HexOutput(data[j])<<" ";
	  if ( (++cnt) % 16 == 0 )
		  f << Break << endl;
	}
    f<<Break<<endl;

    // !!ph!! need to set up decoders for the ROSE or TCAP user data (4.5.15.1 and 4.5.15.2)
}



// Decode the Information Request information element
void DecodeInformationRequest(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
	
	DecodeBit(f,indent,data[1],7,"Indicator=","Prompt for additional information","Information request comleted");

    DrawBits(f,indent,data[1],6,1,"Type of information=");
    switch (data[1]&0x3f) {
		case 0x00:
			f<<"Undefined"; break;
		case 0x01:
			f<<"Authorization code"; break;
		case 0x02:
			f<<"Address digits"; break;
		case 0x03:
			f<<"Terminal identification"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;

/*
    DisplayDecodeOctet(f,indent,data[2]);
    DecodeExtBit(f,indent,data[2]);
    
	DrawBits(f,indent,data[2],7,1,"Information specifics=");
    switch (data[2]&0x7f) {
		case 0x00:
			f<<"Dialed number"; break;
		case 0x01:
			f<<"Calling party number"; break;
		case 0x02:
			f<<"Connected number"; break;
		case 0x10:
			f<<"Redirecting number and indicators"; break;
		case 0x11:
			f<<"Redirection number and indicators"; break;
		case 0x12:
			f<<"Redirecting number without reason indicator"; break;
		case 0x13:
			f<<"Redirection number without reason indicator"; break;
		case 0x30:
			f<<"Information denied"; break;
		case 0x31:
			f<<"Information not available"; break;
		default:
			f<<USAGE_RESERVED;
    }
    f<<Break<<endl;
*/
}



void DecodeFeatureActivation(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	WORD FIDN=0;
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
	DrawBits(f,indent,data[1],7,1,"Feature identifier number",true);
	
	FIDN+=(data[1]&0x7f);
	if (ExtBitClear(data[1])) 
	{
		DisplayDecodeOctet(f,indent,data[2]);
	    DecodeExtBit(f,indent,data[2]);
		DrawBits(f,indent,data[2],7,1,"Feature identifier number (cont)",true);
		FIDN=(FIDN<<7)+(data[2]&0x7f);
	}
	f<<DrawIndent(indent)<<"Feature identifier number="<<FIDN<<Break<<endl;
}



void DecodeFeatureIndication(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	WORD FIDN=0;
	int extCnt=0;
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
	DrawBits(f,indent,data[1],7,1,"Feature identifier number",true);
	
	FIDN+=(data[1]&0x7f);
	if (ExtBitClear(data[1])) 
	{
		extCnt++;
		DisplayDecodeOctet(f,indent,data[1+extCnt]);
	    DecodeExtBit(f,indent,data[1+extCnt]);
		DrawBits(f,indent,data[1+extCnt],7,1,"Feature identifier number (cont)",true);
		FIDN=(FIDN<<7)+(data[1+extCnt]&0x7f);
	}
	f<<DrawIndent(indent)<<"Feature identifier number="<<FIDN<<Break<<endl;

	DisplayDecodeOctet(f,indent,data[2+extCnt]);
	DecodeSpare(f,indent,data[2+extCnt],8,5);
	DrawBits(f,indent,data[2+extCnt],4,1,"Status=");
	switch (data[2+extCnt]&0x0f) {
		case 0x00:
			f<<"Deactivated"; break;
		case 0x01:
			f<<"Activated"; break;
		case 0x02:
			f<<"Prompt"; break;
		case 0x03:
			f<<"Pending"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}



void DecodeServiceProfileIdentification(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecoderNotImplemented(f,indent,data,"ServiceProfileIdentification");
}



void DecodeEndpointIdentifier(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DisplayDecodeOctet(f,indent,data[1]);
	DecodeExtBit(f,indent,data[1]);
	DrawBits(f,indent,data[1],7,1,"User Service IDentifier=");
	f<<((int)(data[1]&0x7f))<<Break<<endl;

	if (data[0]>1) {
		DisplayDecodeOctet(f,indent,data[2]);
		// octet 4 is provided
		if ((data[1]&0x7f)==0x7f) 
			f<<DrawIndent(indent)<<"Not Used (USID=7f)"<<Break<<endl;
		else {
			DecodeExtBit(f,indent,data[2]);
			DrawBits(f,indent,data[2],7,6,"Interpreter=");
			switch (data[2]&0x40) {
				case 0x00:
					f<<"Addressed on TID match"; break;
				case 0x40:
					f<<"Addressed on TID mismatch and TID not 63"; break;
			}
			f<<Break<<endl;
			DrawBits(f,indent,data[2],5,1,"Terminal IDentifier=");
			f<<((int)(data[2]&0x1f))<<Break<<endl;
		}

	}
}
