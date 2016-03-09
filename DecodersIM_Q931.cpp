//
// DecodersIM_Q931.cpp
//
//////////////////////////////////////////////////////////////////
//
// Revision information
//
//
//
//
// April 8 2002: ewcpahi:
//	Fixed a bug in DecodeBearerCapability which abnormally terminated
//	decoding of layer capabilities	
//  Fixed "short" channel identification messages (i.e. 1 byte of data)
// April 10 2002: ewcpahi:
//  added Q.931 and Q.955 information to Notification Indicator
//
//////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DecodersIM_Q931.h"

#include "HTMLfmt.h"
#include "ISDN_defs.h"

#include "DecodeIEUtils.h"


bool DecodeProtocol(ofstream f, int indent, BYTE data)
{
	bool ok=true;
    DisplayDecodeOctet(f,indent,data);
    DrawBits(f,indent,data,8,1,"Protocol=");
	if ( data >= 0x00 && data <= 0x07)
		f << "**not available**";
	else if ( data == PROTOCOL_Q931 )
		f << "Q.931";
	else if ( data == PROTOCOL_Q2931 )
		f << "Q.2931";
	else if ( (data >= 0x10 && data <= 0x3f) || (data >= 0x50 && data <=0xfe) )
		f << "reserved for other network layer or layer 3 protocols, including "<< Recommendation("X.25");
	else if ( data >= 0x40 && data <= 0x4f )
		f << "National use";
	else {
		f << USAGE_RESERVED;
		ok = false;
	}
	f << " (" << HexOutput(data) << ")" << Break << endl;
	return ok;
}

bool DecodeCallReferenceLength(ofstream f, int indent, BYTE data)
{
	bool decodeOk = true;
	DisplayDecodeOctet(f,indent,data);
	DecodeSpare(f,indent,data,8,5);
	DrawBits(f,indent,data,4,1,"Call reference length=");
	switch (data&0x0f) {
		case 0:
			f<<"0 (Dummy Call Reference)";
			break;
		case 1:
		case 2:
			f<<(int)(data&0x0f);
			break;
		default:
			f<<"**invalid** " << HexOutput(data&0x0f);
			decodeOk = false;
	}
	f << Break << endl;
	return decodeOk;
				
}



void DecodeCallReference(ofstream f, int indent, BYTE len, BYTE data1, BYTE data2)
{
	f << DrawIndent(indent-1) << HexOutput(data1);
	if (len == 2) f<<" "<<HexOutput(data2);
	f<<Break<<endl;

	DecodeBit(f,indent,data1,8,"Flag=Message sent ","to","from"," Call Originator");

	int CallRef = data1 & 0x7f;
	DrawBits(f,indent,data1,7,1);
	if (len==2) {
		f<<Break<<endl;
		DrawBits(f,indent,data2,8,1);
		CallRef *= 256;
		CallRef += data2;
	}
	if ( CallRef == 0 ) 
		WriteValue(f,0,"Call reference","Global Reference");
	else WriteValue(f,0,"Call reference", CallRef );
}


static bool DisplayMessageType(ofstream f, BYTE Protocol, BYTE MessageType )
{
	bool bMessageKnown = true;
	if ( Protocol == PROTOCOL_Q931) {
		switch (MessageType) {
			case MESSAGE_ALERTING:
  				f << "Alerting";
				break;
			case MESSAGE_CALL_PROCEEDING:
				f << "Call Proceeding";
				break;
			case MESSAGE_CONNECT:
				f << "Connect";
				break;
			case MESSAGE_CONNECT_ACKNOWLEDGE:
				f << "Connect Acknowledge";
				break;
			case MESSAGE_PROGRESS:
				f << "Progress";
				break;
			case MESSAGE_SETUP:
				f << "Setup";
				break;
			case MESSAGE_SETUP_ACKNOWLEDGE:
				f << "Setup Acknowledge";
				break;
			case MESSAGE_RESUME:
				f << "Resume";
				break;
			case MESSAGE_RESUME_ACKNOWLEDGE:
				f << "Resume Acknowledge";
				break;
			case MESSAGE_RESUME_REJECT:
				f << "Resume Reject";
				break;
			case MESSAGE_SUSPEND:
				f << "Suspend";
				break;
			case MESSAGE_SUSPEND_ACKNOWLEDGE:
				f << "Suspend Acknowledge";
				break;
			case MESSAGE_SUSPEND_REJECT:
				f << "Suspend Reject";
				break;
			case MESSAGE_USER_INFORMATION:
				f << "User Information";
				break;
			case MESSAGE_DISCONNECT:
				f << "Disconnect";
				break;
			case MESSAGE_RELEASE:
				f << "Release";
				break;
			case MESSAGE_RELEASE_COMPLETE:
				f << "Release Complete";
				break;
			case MESSAGE_RESTART:
				f << "Restart";
				break;
			case MESSAGE_RESTART_ACKNOWLEDGE:
				f << "Restart Acknowledge";
				break;
			case MESSAGE_SEGMENT:
				f << "Segment";
				break;
			case MESSAGE_CONGESTION_CONTROL:
				f << "Congestion Control";
				break;
			case MESSAGE_INFORMATION:
				f << "Information";
				break;
			case MESSAGE_FACILITY:
				f << "Facility (connectionless)";
				break;
//			case MESSAGE_FACILITY_REJECT:
//				f << "Facility reject (connectionless)";
//				break;
			case MESSAGE_NOTIFY:
				f << "Notify";
				break;
			case MESSAGE_STATUS:
				f << "Status";
				break;
			case MESSAGE_STATUS_ENQUIRY:
				f << "Status Enquiry";
				break;
			default:
				f << "**unknown**";
				bMessageKnown=false;
				break;
		}
	}
	if ( Protocol == PROTOCOL_MAINTENANCE ) {
		switch (MessageType) {
			case MESSAGE_SERVICE:
				f << "Service";
				break;
			case MESSAGE_SERVICE_ACKNOWLEDGE:
				f << "Service Acknowledge";
				break;
			default:
				f << "**unknown**";
				bMessageKnown=false;
				break;
		}
	}

	return bMessageKnown;
}

bool DecodeMessageType(ofstream f, int indent, BYTE Protocol, BYTE MessageType )
{
	bool decodeOk = true;
	DisplayDecodeOctet(f,indent,MessageType);
	DrawBits(f,indent,MessageType,8,1,"Message=");
	f<<" ("<<HexOutput(MessageType)<<") ";
	decodeOk=DisplayMessageType(f,Protocol,MessageType);
	f << Break << endl;
	return decodeOk;
}

/*
// Decode the Change Status information element
void DecodeChangeStatus(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);

	DecodeBit(f,indent,data[1],7,"Preference=","Channel","Reserved");

    DecodeSpare(f,indent,data[1],6,4);
    
	DrawBits(f,indent,data[1],3,1,"New status=");
    switch (data[1]&0x07) {
		case 0x00:
			f<<"In service"; break;
		case 0x01:
			f<<"Maintenance"; break;
		case 0x02:
			f<<"Out of service"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
}
*/

static void DecodeBearerCapability3(ofstream f, int indent, BYTE data, bool &bUnrestrictedDigital)
{
    DisplayDecodeOctet(f,indent,data);
    DecodeExtBit(f,indent,data);
    DecodeCodingStandard76(f,indent,data);
	DecodeInformationTransferCapability(f,indent,data,bUnrestrictedDigital);
}
static void DecodeBearerCapability3(ofstream f, int indent, BYTE data)
{
	bool bDummy = false;
	DecodeBearerCapability3(f,indent,data,bDummy);
}

static void DecodeBearerCapability4(ofstream f, int indent, BYTE data, bool &bIsMultirate)
{
    DisplayDecodeOctet(f,indent,data);
    DecodeExtBit(f,indent,data);
	DecodeInformationTransferMode(f,indent,data);
	DecodeInformationTransferRate(f,indent,data,bIsMultirate);
}


// BearerCapability octet 4a is only defined in ETS 300 102-1
static void DecodeBearerCapability4a(ofstream f, int indent, BYTE data)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);
	DecodeStructure(f,indent,data);
	DecodeConfiguration(f,indent,data);
	DecodeEstablishment(f,indent,data);
}

// BearerCapability octet 4b is only defined in ETS 300 102-1
static void DecodeBearerCapability4b(ofstream f, int indent, BYTE data, bool &isMultirate)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);
	DecodeSymmetry(f,indent,data);
	DrawBits(f,indent,data,7,6,"Symmetry=");
	DecodeInformationTransferRateDO(f,indent,data,isMultirate);
}


static void DecodeBearerCapability5(ofstream f, int indent, BYTE data, bool &need5a, bool &need5b1, bool &need5b2)
{
	need5a = false; need5b1 = false; need5b2 = false;
    DisplayDecodeOctet(f,indent,data);
    DecodeExtBit(f,indent,data);
	DecodeLayerIdentification(f,indent,data);
    DrawBits(f,indent,data,5,1,"User information layer 1 protocol=");
    switch (data&0x1f) {
		case 0x01:
			f<<"ITU-T standardized rate adaption V.110, I.460 and X.30"; 
			need5a = true; need5b1 = true;
			break;
		case 0x02:
			f<<Recommendation("G.711") << " Mu-law"; break;
		case 0x03:
			f<<Recommendation("G.711") << " A-law"; break;
		case 0x04:
			f<<Recommendation("G.711") << " 32kbit/s ADPCM and " << Recommendation("I.460"); break;
/*
		case 0x05:
			f<<"Recommendation G.722 and G.725 7kHz audio"; break;

		case 0x06:
			f<<"Recommendation G.7xx 384bit/s video"; break;
*/
		case 0x05:
			f<<Recommendation("G.221,H.242"); break;
		case 0x06:
			f<<Recommendation("G.223,H.245"); break;
		case 0x07:
			f<<"Non-ITU-T standardized rate adaptation"; 
			need5a = true;
			break;
		case 0x08:
			f<<"ITU-T standardized rate adaptation V.120"; 
			need5a = true; need5b2 = true;
			break;
		case 0x09:
			f<<"ITU-T standardized rate adaptation X.31 HDLC flag stuffing"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}




static void DecodeBearerCapability5a(ofstream f, int indent, BYTE data)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);

	DecodeBit(f,indent,data,7,"","asynchronous","synchronous"," data");

	DecodeBit(f,indent,data,6,"In-band negotiation ","possible","not possible");

	DrawBits(f,indent,data,5,1,"User rate=");
	switch (data&0x1f) {
		case 0x00:
			f<<"According to E-bits specified in " << Recommendation("I.460"); break;
		case 0x01:
			f<<"0.6 kbit/s         " << Recommendation("X.1"); break;
		case 0x02:
			f<<"1.2 kbit/s"; break;
		case 0x03:
			f<<"2.4 kbit/s         " << Recommendation("X.1"); break;
		case 0x04:
			f<<"3.6 kbit/s"; break;
		case 0x05:
			f<<"4.8 kbit/s         " << Recommendation("X.1"); break;
		case 0x06:
			f<<"7.2 kbit/s"; break;
		case 0x07:
			f<<"8 kbit/s           " << Recommendation("I.460"); break;
		case 0x08:
			f<<"9.6 kbit/s         " << Recommendation("X.1"); break;
		case 0x09:
			f<<"14.4 kbit/s"; break;
		case 0x0a:
			f<<"16 kbit/s          " << Recommendation("I.460"); break;
		case 0x0b:
			f<<"19.2 kbit/s"; break;
		case 0x0c:
			f<<"32 kbit/s          " << Recommendation("I.460"); break;
		case 0x0d:
			f<<"38.4 kbit/s        " << Recommendation("V.110"); break;
		case 0x0e:
			f<<"48 kbit/s          " << Recommendation("X.1"); break;
		case 0x0f:
			f<<"56 kbit/s"; break;
/*
		case 0x10:
			f<<"64 kbit/s          Rec. X.1"; break;
*/
		case 0x12:
			f<<"57.6 kbit/s        " << Recommendation("V.14 extended"); break;
		case 0x13:
			f<<"28.8 kbit/s        " << Recommendation("V.110"); break;
		case 0x14:
			f<<"24 kbit/s          " << Recommendation("V.110"); break;
		case 0x15:
			f<<"0.1345 kbit/s      " << Recommendation("X.1"); break;
		case 0x16:
			f<<"0.100 kbit/s       " << Recommendation("X.1"); break;
		case 0x17:
			f<<"0.075/1.2 kbit/s   " << Recommendation("X.1"); break;
		case 0x18:
			f<<"1.2/0.075 kbit/s   " << Recommendation("X.1"); break;
		case 0x19:
			f<<"0.050 kbit/s       " << Recommendation("X.1"); break;
		case 0x1a:
			f<<"0.075 kbit/s       " << Recommendation("X.1"); break;
		case 0x1b:
			f<<"0.110 kbit/s       " << Recommendation("X.1"); break;
		case 0x1c:
			f<<"0.150 kbit/s       " << Recommendation("X.1"); break;
		case 0x1d:
			f<<"0.200 kbit/s       " << Recommendation("X.1"); break;
		case 0x1e:
			f<<"0.300 kbit/s       " << Recommendation("X.1"); break;
		case 0x1f:
			f<<"12 kbit/s"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}

// decode Bearer Capability Octet 5b according to V.110, I.460 and X.30
static void DecodeBearerCapability5b1(ofstream f, int indent, BYTE data)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);
	DrawBits(f,indent,data,7,6,"Intermediate rate");
	switch (data&0x60) {
		case 0x00:
			f<<"Not used"; break;
		case 0x20:
			f<<"8 kbit/s"; break;
		case 0x40:
			f<<"16 kbit/s"; break;
		case 0x60:
			f<<"32 kbit/s"; break;
	}
	f<<Break<<endl;
	
	DecodeBit(f,indent,data,5,"","Required","Not required"," to send data with network independant clock");

	DecodeBit(f,indent,data,4,"","Can","Cannot"," accept data with network independant clock");

	DecodeBit(f,indent,data,3,"","Required","Not required"," to send data with flow control mechanism");

	DecodeBit(f,indent,data,2,"","Can","Cannot"," accept data with flow control mechanism");
	DecodeSpare(f,indent,data,1,1);
}



// decode Bearer Capability Octet 5b according to V.120
static void DecodeBearerCapability5b2(ofstream f, int indent, BYTE data)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);

	DecodeBit(f,indent,data,7,"Rate adaption header ","included","not included");

	DecodeBit(f,indent,data,6,"Multiple frame establishment ",
			"supported","not supported. Only UI frames allowed");

	DecodeBit(f,indent,data,5,"","Protocol sensitive","Bit transparent" " mode of operation");

	DecodeBit(f,indent,data,4,"","Full protocol negotiation","Default, LLI=256 only");

	DecodeBit(f,indent,data,3,"Message originator is \"",
		"Assignor only","Default assignee");

	DecodeBit(f,indent,data,2,"Negotiation is done ",
		"in-band using logical link zero",
		"with USER INFORMATION messages on a temporary signalling connection" );

	DecodeSpare(f,indent,data,1,1);
}



static void DecodeBearerCapability5c(ofstream f, int indent, BYTE data)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);
	DrawBits(f,indent,data,7,6,"Number of stop bits=");
	switch (data&0x60) {
		case 0x00:
			f<<"Not used"; break;
		case 0x20:
			f<<"1 bit"; break;
		case 0x40:
			f<<"1.5 bits"; break;
		case 0x60:
			f<<"2 bits"; break;
	}
	f<<Break<<endl;

	DrawBits(f,indent,data,5,4,"Number of data bits=");
	switch (data&0x18) {
		case 0x00:
			f<<"Not used"; break;
		case 0x08:
			f<<"5 bits"; break;
		case 0x10:
			f<<"7 bits"; break;
		case 0x18:
			f<<"8 bits"; break;
	}
	f<<Break<<endl;

	DrawBits(f,indent,data,3,1,"Parity=");
	switch (data&0x07) {
		case 0x00:
			f<<"Odd"; break;
		case 0x02:
			f<<"Even"; break;
		case 0x03:
			f<<"None"; break;
		case 0x04:
			f<<"Forced to 0"; break;
		case 0x05:
			f<<"Forced to 1"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}



static void DecodeBearerCapability5d(ofstream f, int indent, BYTE data)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);
	DrawBits(f,indent,data,7,7);
	switch (data&0x40) {
		case 0x00:
			f<<"Half duplex"; break;
		case 0x40:
			f<<"Full Duplex"; break;
	}
	f<< Break<<endl;
	DrawBits(f,indent,data,6,1,"Modem type=");
	BYTE mtyp = data&0x3f;
	switch (mtyp&0x30) {
		case 0x00:
			if (mtyp >= 0x00 && mtyp <= 0x05)
				f<<"National use";
			else f<<USAGE_RESERVED;
			break;
		case 0x10:
			switch (mtyp) {
				case 0x11:
					f<<Recommendation("V.21"); break;
				case 0x12:
					f<<Recommendation("V.22"); break;
				case 0x13:
					f<<Recommendation("V.22 bis"); break;
				case 0x14:
					f<<Recommendation("V.23"); break;
				case 0x15:
					f<<Recommendation("V.26"); break;
				case 0x16:
					f<<Recommendation("V.26 bis"); break;
				case 0x17:
					f<<Recommendation("V.26 ter"); break;
				case 0x18:
					f<<Recommendation("V.27"); break;
				case 0x19:
					f<<Recommendation("V.27 bis"); break;
				case 0x1a:
					f<<Recommendation("V.27 ter"); break;
				case 0x1b:
					f<<Recommendation("V.29"); break;
				case 0x1d:
					f<<Recommendation("V.32"); break;
				case 0x1e:
					f<<Recommendation("V.34"); break;
				default:
					f<<USAGE_RESERVED;
			}
			break;
		case 0x20:
			f<<"National use"; break;
		case 0x30:
			f<<"User specified"; break;
	}
	f<<Break<<endl;
}



static int DecodeBearerCapabilityL1Info(ofstream f, int indent, BYTE data[], int startByte, bool bUnrestrictedDigital)
{
	int numDecoded=0;
	bool need5a, need5b1, need5b2;

	DecodeBearerCapability5(f,indent,data[startByte+numDecoded],need5a, need5b1, need5b2);
	if (!ExtBitClear(data[startByte+numDecoded]))
		return numDecoded+1;

	if (need5a) {
		numDecoded++;
		DecodeBearerCapability5a(f,indent,data[startByte+numDecoded]);
		if (!ExtBitClear(data[startByte+numDecoded]))
			return numDecoded+1;
	}
	if (need5b1) {
		numDecoded++;
		DecodeBearerCapability5b1(f,indent,data[startByte+numDecoded]);
		if (!ExtBitClear(data[startByte+numDecoded]))
			return numDecoded+1;
	}
	if (need5b2) {
		numDecoded++;
		DecodeBearerCapability5b2(f,indent,data[startByte+numDecoded]);
		if (!ExtBitClear(data[startByte+numDecoded]))
			return numDecoded+1;
	}
	
	return numDecoded+1;
}

static int DecodeBearerCapabilityL2Info(ofstream f, int indent, BYTE data[], int startByte)
{
	int decodecnt=1;
	bool userSpecified=false;
	DisplayDecodeOctet(f,indent,data[startByte]);
	DecodeExtBit(f,indent,data[startByte]);
	DecodeLayerIdentification(f,indent,data[startByte]);
	DrawBits(f,indent,data[startByte],5,1);
	switch (data[startByte]&0x1f) {
		case 0x01:
			f<<"Basic mode ISO 1745"; break;
		case 0x02:
			f<<Recommendation("Q.921/I.441"); break;
		case 0x06:
			f<<Recommendation("X.25 link layer"); break;
		case 0x07:
			f<<Recommendation("X.25 Multilink"); break;
		case 0x08:
			f<<"Extended LAPB; for half duplex operation ("<<Recommendation("T.71")<<")"; break;
		case 0x09:
			f<<"HDLC ARM (ISO/IEC 4335)"; break;
		case 0x0a:
			f<<"HDLC NRM (ISO/IEC 4335)"; break;
		case 0x0b:
			f<<"HDLC ABM (ISO/IEC 4335)"; break;
		case 0x0c:
			f<<"LAN logical link control (ISO/IEC 8802-2)"; break;
		case 0x0d:
			f<<Recommendation("X.75. Single Link Procedure (SLP)"); break;
		case 0x0e:
			f<<Recommendation("Q.922"); break;
		case 0x0f:
			f<<"Core aspects of "<<Recommendation("Q.922"); break;
		case 0x10:
			f<<"User specified"; 
			userSpecified = true;
			break;
		case 0x11:
			f<<"ISO/IEC 7776 DTE-DCE operation"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
	if ( ExtBitClear(data[startByte]) ) {
		decodecnt++;
		DisplayDecodeOctet(f,indent,data[startByte+1]);
		if ( userSpecified ) {
			DrawBits(f,indent,data[startByte+1],8,1,"User Defined", true);
		}
		else {
			DecodeExtBit(f,indent,data[startByte+1]);
			DrawBits(f,indent,data[startByte+1],7,6);
			switch ( data[startByte+1]&60 ) {
				case 0x20:
					f<<"Normal mode of operation"; break;
				case 0x40:
					f<<"Extended mode of operation"; break;
				default:
					f<<USAGE_RESERVED;
			}
			f<<Break<<endl;
			DecodeSpare(f,indent,data[startByte+1],5,3);
			DrawBits(f,indent,data[startByte+1],2,1);
			if ( (data[startByte+1]&0x03) == 0x00 )
				f<<"For use when coding defined in Recommendation Q.933 is not used";
			else f<<USAGE_RESERVED;
			f<<Break<<endl;
		}
		if ( ExtBitClear(data[startByte+1]) ) {
			decodecnt++;
			DisplayDecodeOctet(f,indent,data[startByte+2]);
			DecodeExtBit(f,indent,data[startByte+2]);
			DrawBits(f,indent,data[startByte+2],7,1,"k parameter=");
			f<<((int)(data[startByte+2]&0x7f))<<Break<<endl;
			
		}
	}

	
	return decodecnt;
}



static int DecodeBearerCapabilityL3Info(ofstream f, int indent, BYTE data[], int startByte)
{
	int numDecoded=0;
	bool bIsTR9577=false;

	// should be octet 7
	DisplayDecodeOctet(f,indent,data[startByte+numDecoded]);
	DecodeExtBit(f,indent,data[startByte+numDecoded]);
	DecodeLayerIdentification(f,indent,data[startByte+numDecoded]);
	DrawBits(f,indent,data[startByte+numDecoded],5,1);
	switch (data[startByte+numDecoded]&0x1f) {
		case 0x02:
			f<<Recommendation("Q.931"); break;
		case 0x06:
			f<<Recommendation("X.25 packet layer"); break;
		case 0x07:
			f<<"ISO/IEC 8208 (X.25 packet level protocol for data terminal equipment)"; break;
		case 0x08:
			f<<"ITU-T Rec. X.223 and ISO/IEC 8878 (use of ISO/IEC 8208 and Recommendation X.25 to provide the OSI-CONS)"; break;
		case 0x09:
			f<<"ISO/IEC 8473"; break;
		case 0x0a:
			f<<Recommendation("T.70 minimm network layer"); break;
		case 0x0b:
			f<<"ISO/IEC TR 9577 (Protocol identification in the network layer)"; 
			bIsTR9577=true;
			break;
		case 0x10:
			f<<"User specified"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
	if ( !ExtBitClear(data[startByte+numDecoded]) )
		return numDecoded+1;

	numDecoded++;
	// should be octet 7a
	DisplayDecodeOctet(f,indent,data[startByte+numDecoded]);
	DecodeExtBit(f,indent,data[startByte+numDecoded]);
	DecodeSpare(f,indent,data[startByte+numDecoded],7,5);
	switch(data[startByte+numDecoded]&0x0f) {
		case 0x0c:
			f<<"Internet Protocol (RFC 791)(ISO/IEC TR 9577)"; break;
		case 0x0f:
			f<<"Point-to-point Protocol (RFC 1548)"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
	if ( !ExtBitClear(data[startByte+numDecoded]) )
		return numDecoded+1;

	numDecoded++;
	// should be octet 7b
	DisplayDecodeOctet(f,indent,data[startByte+numDecoded]);
	DecodeExtBit(f,indent,data[startByte+numDecoded]);
	DecodeSpare(f,indent,data[startByte+numDecoded],7,5);
	switch(data[startByte+numDecoded]&0x0f) {
		case 0x0c:
			f<<"Internet Protocol (RFC 791)(ISO/IEC TR 9577)"; break;
		case 0x0f:
			f<<"Point-to-point Protocol (RFC 1548)"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
	if ( !ExtBitClear(data[startByte+numDecoded]) )
		return numDecoded+1;

	numDecoded++;
	return numDecoded;
}



// Decode the Bearer Capability information element
void DecodeBearerCapability(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    int hasExt=0;
	bool bUnrestrictedDigital=false;
	DecodeBearerCapability3(f,indent,data[1],bUnrestrictedDigital);

	if ( data[0] == 1) {
		return;
	}

    bool bIsMultirate = false;
	DecodeBearerCapability4(f,indent,data[2],bIsMultirate);
	if ( data[0] == 2) {
		return;
	}

    if ( ExtBitClear(data[2]) ) {
		hasExt++;
		//data[3] contains octet 4a   (ETS 300 102-1)
		DecodeBearerCapability4a(f,indent,data[2+hasExt]);

		if (ExtBitClear(data[2+hasExt]) ) {
			hasExt++;
			//data[4] contains octect 4b    (ETS 300 102-1)
			bool dummy;
			DecodeBearerCapability4b(f,indent,data[2+hasExt],dummy);
		}
    }
    if (bIsMultirate) {
		hasExt++;
		//octet 4.1 is in data[2+hasExt]    (Q.931)
		DisplayDecodeOctet(f,indent,data[2+hasExt]);
		DecodeExtBit(f,indent,data[2+hasExt]);
		DrawBits(f,indent,data[2+hasExt],7,1,"Rate multiplier=");
/*
  ** NIS A211-1 for US-ISDN binds the multiplier to 2-24	
		int mult=(data[2+hasExt]&0x7f);
		if ( mult>=2 && mult<=24) {
			f<<(64*mult)<<" kbit/s (n="<<mult<<")";
		}
		else
			f<<USAGE_RESERVED;
*/
		int mult=(data[2+hasExt]&0x7f);
		f<<(64*mult)<<" kbit/s (n="<<mult<<")";
		f<<Break<<endl;
	}

	int octNum=2+hasExt+1, numDecoded;
	while (octNum<=data[0]) {
		BYTE layer=(data[octNum]&0x60)>>5;
		if (layer==1) {
			// its Octet 5 - Layer 1 Information
			numDecoded=DecodeBearerCapabilityL1Info(f,indent,data,octNum,bUnrestrictedDigital);
		}
		if (layer==2) {
			// its Octet 6 - Layer 2 Information
			numDecoded=DecodeBearerCapabilityL2Info(f,indent,data,octNum);
		}
		if (layer==3) {
			// its Octet 7 - Layer 3 Information
			numDecoded=DecodeBearerCapabilityL3Info(f,indent,data,octNum);
		}
		octNum+=numDecoded;
	}

	if ( data[0] > 12 )
		TooMuchData(f,indent,12);
}


// !!ph!! not complete
void DecodeLowLayerCompatability(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	int hasExt=0;
	bool bUnrestrictedDigital;
	DecodeBearerCapability3(f,indent,data[1], bUnrestrictedDigital);
	if (ExtBitClear(data[1])) {
		hasExt++;
		//decode data[1+hasExt] as octet 3a
	    DisplayDecodeOctet(f,indent,data[1+hasExt]);
		DecodeExtBit(f,indent,data[1+hasExt]);
		DecodeBit(f,indent,data[1+hasExt],7,"out of band negotiation",""," not"," possible");
		DecodeSpare(f,indent,data[1+hasExt],6,1);
	}
	//decode data[2+hasExt] as Octet 4
	bool isMultirate;
	DecodeBearerCapability4(f,indent,data[2+hasExt],isMultirate);
	if ( ExtBitClear(data[2+hasExt]) ) {
		hasExt++;
		//decode data[2+hasExt] as Octet 4a
	    DecodeBearerCapability4a(f,indent,data[2+hasExt]);

		if ( ExtBitClear(data[2+hasExt])) {
			hasExt++;
			//decode data[2+hasExt] as Octet 4b
			bool dummy;
		    DecodeBearerCapability4b(f,indent,data[2+hasExt],dummy);
			
		}
	}
	//decode data[3+hasExt] as octet 5
	int cnt=DecodeBearerCapabilityL1Info(f,indent,data,3+hasExt, bUnrestrictedDigital);	

	cnt+=DecodeBearerCapabilityL2Info(f,indent,data,3+hasExt+cnt);
	cnt+=DecodeBearerCapabilityL3Info(f,indent,data,3+hasExt+cnt);

}




static void DecodePartySubaddress(ofstream f, int indent, BYTE data[])
{
    int hasExt=0;
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
    DrawBits(f,indent,data[1],7,5,"Type of subaddress=");
    switch (data[1]&0x70) {
		case 0x00:
			f<<"NASP (ITU-T Rec. X.213 and ISO/IEC 8348 Add.2)"; break;
		case 0x20:
			f<<"user specified"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
    DrawBits(f,indent,data[1],4,4);
    switch (data[1]&0x80) {
		case 0x00:
			f<<"even"; break;
		case 0x80:
			f<<"odd"; break;
    }
    f<<" number of address signals"<<Break<<endl;
    DecodeSpare(f,indent,data[1],3,1);
    f<<DrawIndent(indent-1);
    for (int j=2; j<=data[0]; j++)
      f<<HexOutput(data[0])<<" ";
    f<<Break<<endl;
}




// Decode the Calling Party Number information element
void DecodeCallingPartyNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
    DecodeNumber(f, indent, data );
}


// Decode the Calling Party Subaddress information element
void DecodeCallingPartySubaddress(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodePartySubaddress(f,indent,data);
}


// Decode the Called Party Number information element
void DecodeCalledPartyNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
    DecodeNumber(f, indent, data );

}


// Decode the Called Party Subaddress information element
void DecodeCalledPartySubaddress(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodePartySubaddress(f,indent,data);
}





// Decode the Call Identity information element
void DecodeCallIdentity(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
    int j;
    f<<DrawIndent(indent-1);
    for (j=0; j<data[0]; j++)
      f<<HexOutput(data[j+1])<<" ";
	f<<Break<<endl;
    f<<DrawIndent(indent);
    for (j=0; j<=data[0]; j++)
		f<<((char)(data[j+1]));

    f<<Break<<endl;
}








// Decode the Call State information element
void DecodeCallState(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DisplayDecodeOctet(f,indent,data[1]);
    DecodeCodingStandard87(f,indent,data[1]);
    DrawBits(f,indent,data[1],6,1);
    if ( vars->GlobalCallReference ) {
		switch (data[1]&0x3f) {
			case 0x00:
				f<<"REST 0-Null"; break;
			case 0x3d:
				f<<"REST 1-Restart request"; break;
			case 0x3e:
				f<<"REST 2-Restart"; break;
			default:
				f<<USAGE_RESERVED;
		}
		f<<Break<<endl;
    }
    else {
		switch (data[1]&0x3f) {
			case 0x00:
				f<<"Null"; break;
			case 0x01:
				f<<"Call initiated"; break;
			case 0x02:
				f<<"Overlap sending"; break;		// Q.931 05/98 
			case 0x03:
				f<<"Outgoing call proceeding"; break;
			case 0x04:
				f<<"Call delivered"; break;
			case 0x06:
				f<<"Call present"; break;
			case 0x07:
				f<<"Call received"; break;
			case 0x08:
				f<<"Connect request"; break;
			case 0x09:
				f<<"Incoming call proceeding"; break;
			case 0x0a:
				f<<"Active"; break;
			case 0x0b:
				f<<"Disconnect request"; break;
			case 0x0c:
				f<<"Disconnect indication"; break;
			case 0x0f:
				f<<"Suspend request"; break;		// Q.931 05/98 
			case 0x11:
				f<<"Resume request"; break;			// Q.931 05/98 
			case 0x13:
				f<<"Release request"; break;
			case 0x16:
				f<<"Call abort"; break;
			case 0x19:
				f<<"Overlap receiving"; break;
			default:
				f<<USAGE_RESERVED;
		}
		f<<Break<<endl;
    }
}







// Decode the Channel Identification information element
void DecodeChannelIdentification(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);

    bool bDecode31=DecodeBit(f,indent,data[1],7,"Interface identifier present=",
				"Interface explicitly defined",
				"Interface implicity defined");

	bool bBasicInterface = !DecodeBit(f,indent,data[1],6,"Interface type=",
				"Other interface, e.g. Primary rate",
				"Basic interface");

    DecodeSpare(f,indent,data[1],5,5);

	DecodeBit(f,indent,data[1],4,"Pref/Excl=",
			"Exclusive; only the indicated channel is acceptable",
			"Indicated channel is preferred" );

	DecodeBit(f,indent,data[1],3,"Channel identified is ","","not ","the D-channel");

    DrawBits(f,indent,data[1],2,1,"Information channel selection=");
	if ( bBasicInterface ) {
		switch (data[1]&0x03) {
			case 0x00:
				f<<"No channel"; break;
			case 0x01:
				f<<"B1 channel"; break;
			case 0x02:
				f<<"B2 channel"; break;
			case 0x03:
				f<<"Any channel"; break;
		}
	}
	else {
		switch (data[1]&0x03) {
			case 0x00:
				f<<"No channel"; break;
			case 0x01:
				f<<"As indicated in the following octets"; break;
			case 0x02:
				f<<USAGE_RESERVED; break;
			case 0x03:
				f<<"Any channel"; break;
		}
	}
	f<<Break<<endl;
    int hasExt=0;
    if ( bDecode31 ) {
      // decode octect 3.1 (in data[2])
      DisplayDecodeOctet(f,indent,data[2]);
      DecodeExtBit(f,indent,data[2]);
      DrawBits(f,indent,data[2],7,1,"Interface identifier=");
      f<<(data[2]&0x7f)<<Break<<endl;
      hasExt++;
    }
	if (data[0]<(2+hasExt))
		return;
    //decode octect 3.2 in data[2+hasExt]
    DisplayDecodeOctet(f,indent,data[2+hasExt]);
    DecodeExtBit(f,indent,data[2+hasExt]);
    DecodeCodingStandard76(f,indent,data[2+hasExt]);
    bool isChannelNumber=!DecodeBit(f,indent,data[2+hasExt],5,
			"Channel is indicated by the ",
				"slot map",
				"number",
			" in the following octet(s)");
	eChannelType BChannelUnits = DecodeChannelType(f,indent,data[2+hasExt]);

    // if the channel number or slot map is not incuded then thats all there is to decode
    if ( data[0]<=2+hasExt)
      return;

    if (isChannelNumber) {
      //octet 3.3 is the channel number
      DisplayDecodeOctet(f,indent,data[2+hasExt+1]);
	  DecodeExtBit(f,indent,data[2+hasExt+1]);
      DrawBits(f,indent,data[2+hasExt+1],7,1,"Channel number=");
      f<<(int)(data[2+hasExt+1]&0x7f)<<Break<<endl;
    }
    else {
		switch ( BChannelUnits ) { 
			case BChannel: {
				//octct 3.3 is a slot map
				int numBytes=(data[0]-(2+hasExt));  // number of bytes in the slot map
				f<<DrawIndent(indent-1);
				int bo=2+hasExt+1;
				for (int j=bo; j<=data[0]; j++)
					f<<HexOutput(data[j])<<" ";
				f<<Break<<endl;
				if ( numBytes == 4)
				  DrawBits(f,indent,data[bo++],8,1,"32..25");
				DrawBits(f,indent,data[bo++],8,1,"24..17");
				DrawBits(f,indent,data[bo++],8,1,"16..9");
				DrawBits(f,indent,data[bo++],8,1,"8..1");
				break;
				}
			case H0Channel:
				DrawBits(f,indent,data[2+hasExt+1],8,1,"channel=");
				if ( data[2+hasExt+1] & 0x10 )
					f << "e(5) ";
				if ( data[2+hasExt+1] & 0x08 )
					f << "d(4) ";
				if ( data[2+hasExt+1] & 0x04 )
					f << "c(3) ";
				if ( data[2+hasExt+1] & 0x02 )
					f << "b(2) ";
				if ( data[2+hasExt+1] & 0x01 )
					f << "a(1) ";
				f<<Break<<endl;
				break;
			case H11Channel:
				DrawBits(f,indent,data[2+hasExt+1],8,1,"channel=");
				if ( data[2+hasExt+1] & 0x01 )
					f << "H11(1) ";
				f<<Break<<endl;
				break;
			case H12Channel:
				DrawBits(f,indent,data[2+hasExt+1],8,1,"channel=");
				if ( data[2+hasExt+1] & 0x01 )
					f << "H12(1) ";
				f<<Break<<endl;
				break;
		}
    }
}


void DecodeCongestionLevel(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DrawBits(f,indent,data[0],4,1);
	switch (data[0]&0x0f) {
		case 0x00:
			f<<"Receiver ready"; break;
		case 0x0f:
			f<<"Receiver not ready"; break;
		default:
			f<<USAGE_RESERVED;
	}
}

void DecodeRepeatIndication(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DrawBits(f,indent,data[0],4,1,"Repeat Indication=");
	switch (data[0]&0x0f) {
		case 0x02:
			f<<"Prioritized list for selecting one possibility"; break;
		default:
			f<<USAGE_RESERVED;
	}
}

void DecodeShift(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	int tCodeSet = (data[0]&0x07);
	DecodeBit(f,indent,data[0],4,"","non-locking","locking"," shift");
	DrawBits(f,indent,data[0],3,1,"Codeset=");
	switch (tCodeSet) {
		case 0x00:
			f << "Q.931";
			break;
		case 0x04:
			f << "ISO/IEC";
			break;
		case 0x05:
			f << "national";
			break;
		case 0x06:
			f << "local network";
			break;
		case 0x07:
			f << "user-specific";
			break;
		default:
			f << "**reserved**";
			tCodeSet=vars->ActiveCodeSet;
			break;
	}
	f << Break << endl;
	if ( (data[0]&0x08)==0 ) {
		// this is a locking shift
		vars->ActiveCodeSet = tCodeSet;
	}
	else {
		vars->LastCodeSet = vars->ActiveCodeSet;
		vars->LockCount=2;
		vars->ActiveCodeSet=tCodeSet;
	}
}







void DecodeProgressIndicator(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
    DecodeCodingStandard76(f,indent,data[1]);
    DecodeSpare(f,indent,data[1],5,5);
    DecodeLocation(f,indent,data[1]);

    DisplayDecodeOctet(f,indent,data[2]);
    DecodeExtBit(f,indent,data[2]);
    DrawBits(f,indent,data[2],7,1,"Diagnositc=");
    switch(data[2]&0x7f) {
		case 0x01:
			f<<"Call not end-to-end ISDN."; break;
		case 0x02:
			f<<"Destination address is non-ISDN"; break;
		case 0x03:
			f<<"Origination address is non-ISDN"; break;
		case 0x04:
			f<<"Call returned to the ISDN"; break;
		case 0x05:
			f<<"Interworking has occurred and has resulted in a telecommunication service change"; break;
		case 0x08:
			f<<"In-band information or an appropriate pattern is now available"; break;
		// for Q.931 Annex M (VPN)
		case 0x10:
			f<<"Interworking with the public network"; break;
		case 0x11:
			f<<"Interworking with a network unable to supply a release signal"; break;
		case 0x12:
			f<<"Interworking with a network unable to supply a release signal before answer"; break;
		case 0x13:
			f<<"Interworking with a network unable to supply a release signal after answer"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
}





// Decode the Network Specific Facilities information element
void DecodeNetworkSpecificFacilities(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
    f<<DrawIndent(indent)<<"Length of network identification="<<(int)(data[1])<<Break<<endl;

    if (data[1]>0) {
		if ( ExtBitSet(data[2]) ) {
			DisplayDecodeOctet(f,indent,data[2]);
			DecodeExtBit(f,indent,data[2]);
			DecodeNetworkIdentificationType(f,indent,data[2]);
			DecodeNetworkIdentificationPlan(f,indent,data[2]);
		}
		f<<DrawIndent(indent-1);
		for (int j=1; j<data[1]; j++)
			f<<HexOutput(data[2+j]&0x7f)<<" ";
		f<<Break<<endl;
		f<<DrawIndent(indent);
		for (j=1; j<data[1]; j++)
			f<<((char)(data[2+j]&0x7f))<<" ";
		f<<Break<<endl;
    }
	//octet 4 is data[2+data[1]]
    DisplayDecodeOctet(f,indent,data[2+data[1]]);
	WriteValue(f,indent,"Network-specific facility specification",data[2+data[1]]);
	
}





void DecodeNotificationIndicator(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
    DrawBits(f,indent,data[1],7,1,"Notification description=");
    switch (data[1]&0x7f) {
		case 0x00:		// Q.931
			f<<"User suspended"; break;
		case 0x01:		// Q.931
			f<<"User reumed"; break;
		case 0x02:		// Q.931
			f<<"Bearer service change"; break;
		case 0x04: 		// Q.955/3.4.3.3
			f<<"Call completion delay"; break;
		case 0x4f:		// Q.955/3.4.3.3
			f<<"Conference floating served user preempted"; break;
		case 0x4c:		// Q.955/3.4.3.3
			f<<"Conference disconnecte, preemption"; break;
		case 0x71:
			f<<"Call information/event"; break;
		default:
			f<<USAGE_RESERVED;
    }
    f<<Break<<endl;
}





// Decode the Display information element
void DecodeDisplay(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	int charsStartAt = 1;

    DisplayDecodeOctet(f,indent,data[1]);
	if ( ExtBitSet(data[1]) ) {
		// 
		// this additional information before the Display IA5 characters
		// is only defined for US ISDN in NIS A211-1 4.5.14
		charsStartAt++;
		DecodeExtBit(f,indent,data[1]);
		DrawBits(f,indent,data[1],7,5,"Associated Info=");
		switch (data[1]&0x70) {
			case 0x10:
				f<<"Requested"; break;
			case 0x30:
				f<<"Included"; break;
			default:
				f<<USAGE_RESERVED;
		}
		DrawBits(f,indent,data[1],4,1,"Display Type=");
		switch (data[1]&0x0f) {
			case 0x01:
				f<<"Calling party name"; break;
			case 0x02:
				f<<"Connected party name"; break;
			case 0x05:
				f<<"Original called party name"; break;
			default:
				f<<USAGE_RESERVED;
		}
		f<<Break<<endl;
	}
    f<<DrawIndent(indent-1);
    for (int j=charsStartAt; j<=data[0]; j++)
      f<<HexOutput(data[j])<<" ";
	f<<Break<<endl;
	f<<DrawIndent(indent);
    for (j=charsStartAt; j<=data[0]; j++)
      f<<((char)(data[j]));

    f<<Break<<endl;
}









void DecodeOriginalCalledNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
    DecodeTypeOfNumber(f,indent,data[1]);
    DecodeNumberPlanID(f,indent,data[1]);

    //!!ph!! this is not complete

}








void DecodeTransitNetworkSelection(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
    DecodeNetworkIdentificationType(f,indent,data[1]);
    DecodeNetworkIdentificationPlan(f,indent,data[1]);

    f<<DrawIndent(indent-1)<<"Network identification=";
    for (int j=2; j<=data[0]; j++)
      f<<HexOutput(data[j])<<" ";
	f<<Break<<endl;

    f<<DrawIndent(indent);
    for (j=2; j<=data[0]; j++)
      f<<((char)(data[j]));
	f<<Break<<endl;
}





void DecodeRestartIndicator(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
    DecodeSpare(f,indent,data[1],7,4);
    DrawBits(f,indent,data[1],3,1,"Class=");
    switch(data[1]&0x07) {
		case 0x00:
			f<<"Indicated channel"; break;
		case 0x06:
			f<<"Single interface"; break;
		case 0x07:
			f<<"All interfaces"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
}



void DecodeSignal(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
	DrawBits(f,indent,data[1],8,1,"Signal=");
	switch (data[1]) {
		case 0x00:
			f<<"Dial tone on"; break;
		case 0x01:
			f<<"Ring back tone on"; break;
		case 0x02:
			f<<"Intercept tone on"; break;
		case 0x03:
			f<<"Network congestion tone on"; break;
		case 0x04:
			f<<"Busy tone on"; break;
		case 0x05:
			f<<"Confirm tone on"; break;
		case 0x06:
			f<<"Answer tone on"; break;
		case 0x07:
			f<<"Call waiting tone"; break;
		case 0x08:
			f<<"Off-hook warning tone"; break;
		case 0x09:
			f<<"Pre-emption tone"; break;
		case 0x2f:
			f<<"Tones off"; break;
		case 0x40:
			f<<"Alerting on - pattern 0"; break;
		case 0x41:
			f<<"Alerting on - pattern 1"; break;
		case 0x42:
			f<<"Alerting on - pattern 2"; break;
		case 0x43:
			f<<"Alerting on - pattern 3"; break;
		case 0x44:
			f<<"Alerting on - pattern 4"; break;
		case 0x45:
			f<<"Alerting on - pattern 5"; break;
		case 0x46:
			f<<"Alerting on - pattern 6"; break;
		case 0x47:
			f<<"Alerting on - pattern 7"; break;
		case 0x4f:
			f<<"Alerting off"; break;
	}
		
	f<<Break<<endl;
}









void DecodeHighLayerCompatability(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	int hasExt=0;
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
	DecodeCodingStandard76(f,indent,data[1]);
	DrawBits(f,indent,data[1],5,3,"Interpretation=");
	switch(data[1]&0x1c) {
		case 0x10:
			f<<"First (primary only) high layer characteristics identification to be used in the call"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
	DrawBits(f,indent,data[1],2,1,"Presentation method=");
	switch(data[1]&0x03) {
		case 0x01:
			f<<"High layer protocol profile (without specification of attributes)"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;

    DisplayDecodeOctet(f,indent,data[2]);
    DecodeExtBit(f,indent,data[2]);
	DrawBits(f,indent,data[2],7,1,"High layer characteristics=");
	DecodeHighLayerCharacteristics(f,indent,data[2],false);
	if (ExtBitClear(data[2])) {
		//decode data[3] as octet4a
	    DisplayDecodeOctet(f,indent,data[3]);
		DecodeExtBit(f,indent,data[3]);
		DrawBits(f,indent,data[3],7,1,"Extended high layer characteristics=");
		DecodeHighLayerCharacteristics(f,indent,data[3],true);
	}

}





void DecodeKeypadFacility(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	f<<DrawIndent(indent-1);
	for (int j=1; j<=data[0]; j++)
      f<<HexOutput(data[j])<<" ";
    f<<Break<<endl;
	f<<DrawIndent(indent);
	for (j=1; j<=data[0]; j++)
      f<<(char)(data[j])<<" ";
    f<<Break<<endl;
}



void DecodeDateTime(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	WriteValue(f,indent,"Year",data[1]);
	WriteValue(f,indent,"Month",data[2]);
	WriteValue(f,indent,"Day",data[3]);
	if ( data[0]>3 )
		WriteValue(f,indent,"Hour",data[4]);
	if ( data[0]>4 )
		WriteValue(f,indent,"Minute",data[5]);
	if ( data[0]>5 )
		WriteValue(f,indent,"Second",data[6]);
}



void DecodeUserUser(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
	DrawBits(f,indent,data[1],8,1,"Protocol Discriminator ");
	if ( (data[1]>=0x10 && data[1]<=0x3f) || (data[1]>=0x50 && data[1]<=0xfe))
		f<<"reserved for other network layer or layer 3 protocols including "<<Recommendation("X.25");
	else if ( data[1]>=0x40 && data[1]<=0x4f)
		f<<"national use";
	else switch( data[1] ) {
		case 0x00:
			f<<"User-specific protocol"; break;
		case 0x01:
			f<<"OSI high layer protocol"; break;
		case 0x02:
			f<<Recommendation("X.244"); break;
		case 0x03:
			f<<"Reserved for system management convergence function"; break;
		case 0x04:
			f<<"IA5 characters"; break;
		case 0x05:
			f<<"X.208 and X.209 coded user infromation"; break;
		case 0x07:
			f<<Recommendation("V.120")<<" rate adaption"; break;
		case 0x08:
			f<<"Q.931/I.451 user-network call control messages"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
	for (int j=2, cnt=0; j<=data[0]; j++)
	{
      f<<HexOutput(data[j])<<" ";
	  if ( (++cnt) % 16 == 0 )
		  f << Break << endl;
	}
    f<<Break<<endl;
}


static void DecodeDestnationOrigination(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	int hasExt=0; bool isPrivateNumber=false;
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
	DrawBits(f,indent,data[1],7,4,"Type of routing=");
	switch (data[1]&0x78) {
		case 0x00:
			f<<"Spare"; break;
		case 0x08:
			f<<"Private number"; 
			isPrivateNumber = true;
			break;
		case 0x10:
			f<<"Public number (Recommendation E.164)"; break;
		case 0x18:
			f<<"CCS7 point code"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
	DrawBits(f,indent,data[1],3,1,"Encoding=");
	switch (data[1]&0x07) {
		case 0x00:
			f<<"Spare"; break;
		case 0x01:
			f<<"BCD odd"; break;
		case 0x02:
			f<<"BCD even"; break;
		case 0x03:
			f<<"Binary"; break;
		case 0x04:
			f<<"IA5"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
	int bo=-1;
	if (isPrivateNumber) {
		// we have a Private Network Identifier in data[2] and possibly [3] and [4]
		int PNI=0;
		do {
			bo++;
			PNI=(PNI*64)+(data[2+bo]&0x7f);
			DisplayDecodeOctet(f,indent,data[2+bo]);
			DecodeExtBit(f,indent,data[2+bo]);
			DrawBits(f,indent,data[2+bo],7,1,"Private network identifier");
			f<<Break<<endl;
		} while (ExtBitClear(data[2+bo]));
		WriteValue(f,indent,"Private network identifier",PNI);
	}
	//data[3+bo] is octet 4
	DisplayDecodeOctet(f,indent,data[2+bo]);
	WriteValue(f,indent,"Length of routing information",data[3+bo]);
	
	if (data[3+bo] > 0) {
		f<<DrawIndent(indent-1);
		for (int j=4+bo; j<=4+bo+data[3+bo]; j++)
			f<<HexOutput(data[j])<<" ";
		f<<Break<<endl;
		f<<DrawIndent(indent);
		for (j=4+bo; j<=4+bo+data[3+bo]; j++)
			f<<DrawDigit(data[j]);
		f<<Break<<endl;
	}
}

void DecodeDestination(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodeDestnationOrigination(f,indent,vars,data);
}



void DecodeOptions(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
	DrawBits(f,indent,data[1],7,1,"Options value=");
	switch (data[1]&0x7f) {
		case 0x01:
			f<<"Return message on error"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}



void DecodeOrigination(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodeDestnationOrigination(f,indent,vars,data);
}



void DecodeReasonForReturn(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
	DrawBits(f,indent,data[1],7,1,"Diagnostic=");
	switch (data[1]&0x7f) {
		case 0x00:
			f<<USAGE_RESERVED; break;
		case 0x01:
			f<<"No translation for address of such nature"; break;
		case 0x02:
			f<<"No translation for this specific address"; break;
		case 0x03:
			f<<"Application congestion"; break;
		case 0x04:
			f<<"Application failure"; break;
		case 0x05:
			f<<"Unequipped application"; break;
		case 0x06:
			f<<"Network failure"; break;
		case 0x07:
			f<<"Network congestion"; break;
		default:
			f<<"Spare";
	}
	f<<Break<<endl;
}



void DecodeSegmentedMessage(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
	DecodeBit(f,indent,data[1],8,"","First segment of segmented message","Subsequent segment to first segment");
    DrawBits(f,indent,data[1],7,1,"Remaining Segments=");
	f<<((int)(data[1]&0x7f))<<Break<<endl;

    DisplayDecodeOctet(f,indent,data[2]);
	DecodeSpare(f,indent,data[2],8,8);
    DrawBits(f,indent,data[2],7,1,"Segmented message type=");
	DisplayMessageType(f,PROTOCOL_Q931,data[2]&0x7f);
	f<<Break<<endl;
}

static void DecodeInformationRate(ofstream f, int indent, BYTE data, const char *label)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);
	DecodeSpare(f,indent,data,7,6);
	DrawBits(f,indent,data,5,1);
	f<<" "<<label<<" information rate=";
	switch (data&0x1f) {
		case 0x00:
		case 0x01:
		case 0x02:
		case 0x0e:
		case 0x0f:
			f<<"Reserved"; break;
		case 0x03:
			f<<"75 bit/s"; break;
		case 0x04:
			f<<"150 bit/s"; break;
		case 0x05:
			f<<"300 bit/s"; break;
		case 0x06:
			f<<"600 bit/s"; break;
		case 0x07:
			f<<"1200 bit/s"; break;
		case 0x08:
			f<<"2400 bit/s"; break;
		case 0x09:
			f<<"4800 bit/s"; break;
		case 0x0a:
			f<<"9600 bit/s"; break;
		case 0x0b:
			f<<"19200 bit/s"; break;
		case 0x0c:
			f<<"48000 bit/s"; break;
		case 0x0d:
			f<<"64000 bit/s"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}
void DecodeInformationRate(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodeInformationRate(f,indent,data[1],"Incoming");
	DecodeInformationRate(f,indent,data[2],"Outgoing");
	DecodeInformationRate(f,indent,data[3],"Minimum incoming");
	DecodeInformationRate(f,indent,data[4],"Maximum outgoing");
}


static void DecodeDelayValue(ofstream f, int indent, BYTE b1, BYTE b2, BYTE b3, const char *label)
{
	f<<DrawIndent(indent-1)<<HexOutput(b1)<<" "<<HexOutput(b2)<<" "<<HexOutput(b3)<<Break<<endl;
	f<<DrawIndent(indent)<<label<<"=";
	WORD d=((b1&0x03)<<14)+((b2&0x7f)<<7)+(b3&0x7f);

	f<<d<<"ms"<<Break<<endl;
}

void DecodeEndToEndTransitDelay(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodeDelayValue(f,indent,data[1],data[2],data[3],"Cumulative transit delay value");

	if ( data[0] > 3 )
		DecodeDelayValue(f,indent,data[4],data[5],data[6],"Requested transit delay value");
	if ( data[0] > 6 )
		DecodeDelayValue(f,indent,data[7],data[8],data[9],"Maximum transit delay value");
}

void DecodeTransitDelaySelectionAndIndication(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodeDelayValue(f,indent,data[1],data[2],data[3],"Transit delay selection and indication");
}

void DecodePacketLayerBinaryParameters(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DisplayDecodeOctet(f,indent,data[1]);
	DecodeExtBit(f,indent,data[1]);
	DecodeSpare(f,indent,data[1],7,6);
	DrawBits(f,indent,data[1],5,4);
	switch (data[1]&0x18) {
		case 0x00:
		case 0x08:
			f<<"Fast select not requested"; break;
		case 0x10:
			f<<"Fast select requested with no restrictions of response"; break;
		case 0x18:
			f<<"Fast select requested with restrictions of response"; break;
	}
	f<<Break<<endl;
	DecodeBit(f,indent,data[1],3,"",
					"Request indicated/request accepted",
					"No request/request denied" );
	DecodeBit(f,indent,data[1],2,"",
					"End-to-end confirmation",
					"Link-by-link confirmation" );
	DecodeBit(f,indent,data[1],1,"Modulus ","128","8"," sequencing");
}

static void DecodeSize(ofstream f, int indent, BYTE data, const char *label)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);
	DrawBits(f,indent,data,7,1,label);
	f<<((int)(data&0x7f))<<Break<<endl;
}

void DecodePacketLayerWindowSize(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodeSize(f,indent,data[1],"Forward value=");

	if ( data[0] > 1 ) 
		DecodeSize(f,indent,data[2],"Backward value=");
}

void DecodePacketSize(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecodeSize(f,indent,data[1],"Forward value=");

	if ( data[0] > 1 ) 
		DecodeSize(f,indent,data[2],"Backward value=");
}

void DecodeClosedUserGroup(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
	DecodeExtBit(f,indent,data[1]);
	DecodeSpare(f,indent,data[1],7,4);
	DrawBits(f,indent,data[1],3,1);
	switch (data[1]&0x07) {
		case 0x01:
			f<<"Closed user group selection"; break;
		case 0x02:
			f<<"Closed user group with outgoing access selection and indication"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;

    f<<DrawIndent(indent-1)<<"CUG Index=";
    for (int j=2; j<=data[0]; j++)
      f<<HexOutput(data[j])<<" ";
	f<<Break<<endl;

    f<<DrawIndent(indent);
    for (j=2; j<=data[0]; j++)
      f<<((char)(data[j]));
	f<<Break<<endl;
}

void DecodeReverseChargingInformation(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
    DisplayDecodeOctet(f,indent,data[1]);
	DecodeExtBit(f,indent,data[1]);
	DecodeSpare(f,indent,data[1],7,4);
	DrawBits(f,indent,data[1],3,1);
	if ( (data[1]&0x07)==0x01 )
		f<<"Reverse charging requested"<<Break<<endl;
	else f<<USAGE_RESERVED<<Break<<endl;
}



void DecodeEscapeForExtension(ofstream f, int indent, psGlobalDefs vars, BYTE data[])
{
	DecoderNotImplemented(f,indent,data,"EscapeForExtension");
}


void DecodeTransitCounter(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
	DecodeReserved(f,indent,data[1],7,6);
	DrawBits(f,indent,data[1],5,1,"Transit Count=");
	f<<((int)(data[1]&0x1f))<<Break<<endl;
}

void DecodeVPNIndicator(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
	DecodeSpare(f,indent,data[1],7,4);
	DrawBits(f,indent,data[1],3,1,"CN indicator=");
	switch (data[1]&0x07) {
		case 0x00:
			f<<"No indication"; break;
		case 0x01:
			f<<"Network specific"; break;
		case 0x02:
			f<<"Global"; break;
		default:
			f<<USAGE_RESERVED;	
	}
	f<<Break<<endl;
	if (data[0] > 1) {
		f<<DrawIndent(indent-1);
		for (int j=2;j<data[0];j++)
			f<<HexOutput(data[j])<<" ";
		f<<Break<<endl;
		f<<DrawIndent(indent)<<"CN Indicator"<<Break<<endl;		
	}
}



void NoDecoder(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
}
