//
// DecodersUtils.cpp
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
//		Changed some IE terminology based on Q.931 05/98 recommendation
//
//////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "DecodeIEUtils.h"

#include "HTMLfmt.h"
#include "ISDN_defs.h"

#include "Decoders.h"

const char *USAGE_RESERVED="**use is reserved**";


sIEDecoderEntry IEDecoders[] = {
	{ "Reserved",							0, IE_RESERVED,							0xf0, NoDecoder },
	{ "Shift",								0, IE_SHIFT,							0xf0, NoDecoder },
	{ "More Data",							0, IE_MORE_DATA,						0xff, NoDecoder },
	{ "Sending Complete",					0, IE_SENDING_COMPLETE,					0xff, NoDecoder },
	{ "Congestion Level",					0, IE_CONGESTION_LEVEL,					0xf0, DecodeCongestionLevel },
	{ "Repeat Indicator",					0, IE_REPEAT_INDICATOR,					0xf0, DecodeRepeatIndication },
	{ "Segmented Message",					0, IE_SEGMENTED_MESSAGE,				0xff, DecodeSegmentedMessage },
	{ "Bearer Capability",					0, IE_BEARER_CAPABILITY,				0xff, DecodeBearerCapability },
	{ "Cause",								0, IE_CAUSE,							0xff, DecodeCauseQ931 },
	{ "Connected Address",					0, IE_CONNECTED_ADDRESS,				0xff, DecodeConnectedAddress },
	{ "Extended Facility",					0, IE_EXTENDED_FACILITY,				0xff, DecodeExtendedFacility },
	{ "Call Indentity",						0, IE_CALL_IDENTITY,					0xff, DecodeCallIdentity },
	{ "Call State",							0, IE_CALL_STATE,						0xff, DecodeCallState },
	{ "Channel Identification",				0, IE_CHANNEL_IDENTIFICATION,			0xff, DecodeChannelIdentification },
	{ "Data Link Connection Identifier",	0, IE_DATA_LINK_CONNECTION_IDENTIFIER,	0xff, DecodeDataLinkConnectionIdentifier },
	{ "Facility",							0, IE_FACILITY,							0xff, DecodeFacility },
	{ "Progress Indicator",					0, IE_PROGRESS_INDICATOR,				0xff, DecodeProgressIndicator },
	{ "Network-specific Facilities",		0, IE_NETWORK_SPECIFIC_FACILITIES,		0xff, DecodeNetworkSpecificFacilities },
	{ "Terminal Capabilities",				0, IE_TERMINAL_CAPABILITIES,			0xff, DecodeTerminalCapabilities },
	{ "Notification Indicator",				0, IE_NOTIFICATION_INDICATOR,			0xff, DecodeNotificationIndicator },
	{ "Display",							0, IE_DISPLAY,							0xff, DecodeDisplay },
	{ "Date/Time",							0, IE_DATE_TIME,						0xff, DecodeDateTime },
	{ "Keypad Facility",					0, IE_KEYPAD_FACILITY,					0xff, DecodeKeypadFacility },
	{ "Keypad Echo",						0, IE_KEYPAD_ECHO,						0xff, DecodeKeypadEcho },
	{ "Decode Information Request",			0, IE_INFORMATION_REQUEST,				0xff, DecodeInformationRequest },
	{ "Signal",								0, IE_SIGNAL,							0xff, DecodeSignal },
	{ "Switchhook",							0, IE_SWITCHHOOK,						0xff, DecodeSwitchhook },
	{ "Feature Activation",					0, IE_FEATURE_ACTIVATION,				0xff, DecodeFeatureActivation },
	{ "Feature Indication",					0, IE_FEATURE_INDICATION,				0xff, DecodeFeatureIndication },
	{ "Service Profile Identification",		0, IE_SERVICE_PROFILE_IDENTIFICATION,	0xff, DecodeServiceProfileIdentification },
	{ "Endpoint Identifier",				0, IE_ENDPOINT_IDENTIFIER,				0xff, DecodeEndpointIdentifier },
	{ "Information Rate",					0, IE_INFORMATION_RATE,					0xff, DecodeInformationRate },
	{ "Precedence Level",					0, IE_PRECEDENCE_LEVEL,					0xff, DecodePrecedenceLevel },
	{ "End-to-end transit level",			0, IE_END_TO_END_TRANSIT_DELAY,			0xff, DecodeEndToEndTransitDelay },
	{ "Transit Delay Selection and Indication", 0, IE_TRANSIT_DELAY_SELECTION_AND_INDICATION, 0xff, DecodeTransitDelaySelectionAndIndication },
	{ "Packet Layer Binary Parameters",		0, IE_PACKET_LAYER_BINARY_PARAMETERS,	0xff, DecodePacketLayerBinaryParameters },
	{ "Packet Layer Window Size",			0, IE_PACKET_LAYER_WINDOW_SIZE,			0xff, DecodePacketLayerWindowSize },
	{ "Packet Size",						0, IE_PACKET_SIZE,						0xff, DecodePacketSize },
	{ "Closed User Group",					0, IE_CLOSED_USER_GROUP,				0xff, DecodeClosedUserGroup },
	{ "Link Layer Core Parameters",			0, IE_LINK_LAYER_CORE_PARAMETERS,		0xff, DecodeLinkLayerCoreParameters },
	{ "Link Layet Protocol Parameters",		0, IE_LINK_LAYER_PROTOCOL_PARAMETERS,	0xff, DecodeLinkLayerProtocolParameters },
	{ "Reverse Charging Information",		0, IE_REVERSE_CHARGING_INDICATION,		0xff, DecodeReverseChargingInformation },
	{ "Connected Number",					0, IE_CONNECTED_NUMBER,					0xff, DecodeConnectedNumber },
	{ "Connected Subaddress",				0, IE_CONNECTED_SUBADDRESS,				0xff, DecodeConnectedSubaddress },
	{ "X.213 Priority",						0, IE_X213_PRIORITY,					0xff, DecodeX213Priority },
	{ "Report Type",						0, IE_REPORT_TYPE,						0xff, DecodeReportType },
	{ "Link Integrity Verification",		0, IE_LINK_INTEGRITY_VERIFICATION,		0xff, DecodeLinkIntegrityVerification },
	{ "PVC Status",							0, IE_PVC_STATUS,						0xff, DecodePVCStatus },
	{ "Calling Party Number",				0, IE_CALLING_PARTY_NUMBER,				0xff, DecodeCallingPartyNumber },
	{ "Calling Party Subaddress",			0, IE_CALLING_PARTY_SUBADDRESS,			0xff, DecodeCallingPartySubaddress },
	{ "Called Party Number",				0, IE_CALLED_PARTY_NUMBER,				0xff, DecodeCalledPartyNumber },
	{ "Called Party Subaddress",			0, IE_CALLED_PARTY_SUBADDRESS,			0xff, DecodeCalledPartySubaddress },
	{ "Redirecting Number",					0, IE_REDIRECTING_NUMBER,				0xff, DecodeRedirectingNumber },
	{ "Redirection Number",					0, IE_REDIRECTION_NUMBER,				0xff, DecodeRedirectionNumber },
	{ "Transit Network Selection",			0, IE_TRANSIT_NETWORK_SELECTION,		0xff, DecodeTransitNetworkSelection },
	{ "Restart Indicator",					0, IE_RESTART_INDICATOR,				0xff, DecodeRestartIndicator },
	{ "Low Layer Compatability",			0, IE_LOW_LAYER_COMPATABILITY,			0xff, DecodeLowLayerCompatability },
	{ "High Layer Compatability",			0, IE_HIGH_LAYER_COMPATABILITY,			0xff, DecodeHighLayerCompatability },
	{ "User-user",							0, IE_USER_USER,						0xff, DecodeUserUser },
	{ "VPN Indicator",						0, IE_VPN_INDICATOR,					0xff, DecodeVPNIndicator },
//	{ "Original Called Number",				0, IE_ORIGINAL_CALLED_NUMBER,			0xff, DecodeOriginalCalledNumber },
//	{ "Change Status",						0, IE_CHANGE_STATUS,					0xff, DecodeChangeStatus },
	{ "Transit Counter",					4, IE_TRANSIT_COUNTER,					0xff, DecodeTransitCounter },
	{ "Escape for Extension",				4, IE_ESCAPE_FOR_EXTENSION,				0xff, DecodeEscapeForExtension },
	{ "Escape for Extension",				5, IE_ESCAPE_FOR_EXTENSION,				0xff, DecodeEscapeForExtension },
	{ "Escape for Extension",				6, IE_ESCAPE_FOR_EXTENSION,				0xff, DecodeEscapeForExtension },
	{ "Escape for Extension",				7, IE_ESCAPE_FOR_EXTENSION,				0xff, DecodeEscapeForExtension },
	{ "Destination",						6, IE_DESTINATION,						0xff, DecodeDestination },
	{ "Options",							6, IE_OPTIONS,							0xff, DecodeOptions },
	{ "Origination",						6, IE_ORIGINATION,						0xff, DecodeOrigination },
	{ "Reason for Return",					6, IE_REASON_FOR_RETURN,				0xff, DecodeReasonForReturn },

	{ NULL,	0, 0, 0, NULL }
};



ostream &IEname( ostream &stream, WORD fullie )
{
	psIEDecoderEntry p = &IEDecoders[0];
	if (p==NULL) return stream;
	BYTE codeset = GET_CODESET(fullie);
	BYTE ie = GET_IE(fullie);

	while (p->DecodeFunction!=NULL) {
		if ((p->CodeSet==codeset) && ((p->IEid&p->IEidMask)==(ie&p->IEidMask))) {
			stream << p->IEname;
			break;
		}
		p++;
	}
	if (p->DecodeFunction == NULL )
		stream << "**unknown IE (codeset="<<HexOutput(codeset)<<" ie="<<HexOutput(ie)<<")**";
	return stream;
}

OMANIP (WORD) IEname( WORD fullie )
{
	return OMANIP (WORD)(IEname, fullie);
}





ostream &DrawIndent( ostream &stream, int size )
{
	if ( size == 0 )
		return stream;
	stream << "<span class=\"rowtype\">";
	for (int j=0; j<size; j++)
		stream << "&nbsp;";
	stream << "</span>";
	return stream;
}

OMANIP (int) DrawIndent( int size )
{
	return OMANIP (int)(DrawIndent, size);
}


ostream &DrawDigit( ostream &stream, BYTE digit )
{
	switch (digit&0x7f) {
		case 0x30:
			stream << "0"; break;
		case 0x31:
			stream << "1"; break;
		case 0x32:
			stream << "2"; break;
		case 0x33:
			stream << "3"; break;
		case 0x34:
			stream << "4"; break;
		case 0x35:
			stream << "5"; break;
		case 0x36:
			stream << "6"; break;
		case 0x37:
			stream << "7"; break;
		case 0x38:
			stream << "8"; break;
		case 0x39:
			stream << "9"; break;
		case 0x2a:
			stream << "*"; break;
		case 0x23:
			stream << "#"; break;
		default:
			stream << "."; break;
	}
	return stream;
}

OMANIP (BYTE) DrawDigit( BYTE digit )
{
	return OMANIP (BYTE)(DrawDigit, digit);
}


bool ExtBitSet(BYTE data)
{
    return (( data & 0x80 ) == 0x80);
}


bool ExtBitClear(BYTE data)
{
    return (( data & 0x80 ) == 0x00);
}

static BYTE Pwr(int a, int b)
{
	if ( b==0) return 1;
//	if ( b==1) return a;
	return a*Pwr(a,b-1);
}


void DisplayDecodeOctet(ofstream f, int indent, BYTE data, char *desc)
{
	f << DrawIndent(indent-1) << HexOutput(data);
	if (strlen(desc)>0) {
		f << " " << desc;
	}
	f << Break << endl;
}
void DisplayDecodeOctet(ofstream f, int indent, BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"");
}

void DrawBits( ofstream f, BYTE data, int msb, int lsb )
{

	f << sFont(FONT_COURIER);
	for ( int j=8; j>0; j--)
    {
      if ( msb>=j && j>=lsb ) {
        BYTE mask = Pwr(2,j-1);
        if ( (data & mask) == mask )
          f << "1";
        else
          f << "0";
      }
      else
        f << "-";
    }
	f << " " << eFont;	
}

void DrawBits( ofstream f, int indent, BYTE data, int msb, int lsb )
{
	f << DrawIndent(indent);
	DrawBits(f, data, msb, lsb );
}

void DrawBits( ofstream f, int indent, BYTE data, int msb, int lsb, const char *label, bool bEndLine )
{
	DrawBits(f, indent, data, msb, lsb );
	f << label;
	if ( bEndLine )
		f<<Break<<endl;
}


bool DecodeBit( ofstream f, int indent, BYTE data, int bit, const char *prefix, const char *setValue, const char *clearValue, const char *suffix )
{
	bool bitSet = (data&(1<<(bit-1)))!=0;
	DrawBits(f,indent,data,bit,bit,prefix);
	f<<(bitSet?setValue:clearValue)<<suffix<<Break<<endl;

	return bitSet;
}


void DecodeExtBit( ofstream f, int indent, BYTE data )
{
	DecodeBit(f,indent,data,8,"Ext=","No","Yes");
}


void DecodeSpare( ofstream f, int indent, BYTE data, int msb, int lsb )
{
	DrawBits(f,indent,data,msb,lsb,"Spare (should be 0)",true);
}


void DecodeReserved( ofstream f, int indent, BYTE data, int msb, int lsb )
{
	DrawBits(f,indent,data,msb,lsb,"Reserved",true);
}


void DecodeNumber(ofstream f, int indent, BYTE data[] )
{
    int hasExt=0;
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
    if (ExtBitClear(data[1])) 
		hasExt=1;
    DecodeTypeOfNumber(f,indent,data[1]);
    DecodeNumberPlanID(f,indent,data[1]);
    if (hasExt==1) {
	    DisplayDecodeOctet(f,indent,data[2]);
		DecodeExtBit(f,indent,data[2]);
		DecodePresentationIndicator(f,indent,data[2]);
		DecodeSpare(f,indent,data[2],5,3);
		DecodeScreeningIndicator(f,indent,data[2]);
	}
    f<<DrawIndent(indent)<<"Number=";
    for (int i=0; i<data[0]-1-hasExt;i++)
      f<<DrawDigit(data[2+hasExt+i]);
    f<<Break<<endl;
}


eChannelType DecodeChannelType(ofstream f, int indent, BYTE data)
{
	eChannelType BChannelUnits = none;
    DrawBits(f,indent,data,4,1,"Channel/Map element type=");
    switch(data&0x0f) {
		case 0x03:
			f<<"B-channel units"; 
			BChannelUnits = BChannel;
			break;
		case 0x06:
			f<<"H0-channel units";  
			BChannelUnits = H0Channel;
			break;
		case 0x08:
			f<<"H11-channel units";  
			BChannelUnits = H11Channel;
			break;
		case 0x09:
			f<<"H12-channel units"; 
			BChannelUnits = H12Channel;
			break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
	return BChannelUnits;
}


static void GenCodingStandard( ofstream f, BYTE data )
{
	f<<"Coding=";
    switch (data&0x03) {
		case 0x00:
			f<<"ITU-T standardized"; break;
		case 0x01:
			f<<"ISO/IEC Standard"; break;
		case 0x02:
			f<<"National standard"; break;
		case 0x03:
			f<<"standard defined for the network (either public or private) present on the network side of the interface"; break;
    }
}

void DecodeCodingStandard76( ofstream f, int indent, BYTE data )
{
	f << DrawIndent(indent);
	DrawBits(f, data, 7, 6);
	GenCodingStandard(f,(data&0x60)>>5);
	f<<Break<<endl;
}

void DecodeCodingStandard87( ofstream f, int indent, BYTE data )
{
	f << DrawIndent(indent);
	DrawBits(f, data, 8, 7);
	GenCodingStandard(f,(data&0xc0)>>6);
	f<<Break<<endl;
}


void DecodeLocation(ofstream f, int indent, BYTE data )
{
    DrawBits(f,indent,data,4,1,"Location=");
    switch(data&0x0f) {
    case 0x00:
      f<<"User (U)"; break;
      break;
    case 0x01:
      f<<"Private network serving the local user (LPN)"; break;
      break;
    case 0x02:
      f<<"Public network serving the local user (LN)"; break;
      break;
    case 0x03:
      f<<"Transit network (TN)"; break;
      break;
    case 0x04:
      f<<"Public network serving the remote user (RLN)"; break;
      break;
    case 0x05:
      f<<"Private network serving the remote user (RPN)"; break;
      break;
    case 0x07:
      f<<"International network (INTL)"; break;
      break;
	case 0x0a:
		f<<"Network beyond interworking point (BI)"; break;
	case 0x0c:
	case 0x0d:
	case 0x0e:
	case 0x0f:
		f<<"reserved for national use"; break;
    default:
      f<<USAGE_RESERVED;
    }
    f<<Break<<endl;
}

void DecodeTypeOfNumber(ofstream f, int indent, BYTE data )
{
	DrawBits(f,indent,data,7,5,"Type of Number=");
    switch(data&0x70) {
		case 0x00:
			f<<"Unknown"; break;
		case 0x10:
			f<<"International"; break;
		case 0x20:
			f<<"National"; break;
		case 0x30:
			f<<"Network specific"; break;
		case 0x40:
			f<<"Subscriber"; break;
		case 0x60:
			f<<"Abbreviated"; break;
		case 0x70:
			f<<"reserved for extension"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
}

void DecodeNumberPlanID(ofstream f, int indent, BYTE data )
{
    DrawBits(f,indent,data,4,1,"Numbering Plan ID=");
    switch(data&0x0f) {
		case 0x00:
			f<<"Unknown"; break;
		case 0x01:
			f<<"ISDN/Telephony numbering plan " << Recommendation("(E.164)"); break;
		case 0x03:
			f<<"Data numbering plan " << Recommendation("(X.121)"); break;
		case 0x04:
			f<<"Telex numbering plan " << Recommendation("(F.69)"); break;
		case 0x08:
			f<<"National standard numbering plan"; break;
		case 0x09:
			f<<"Private numbering plan"; break;
		case 0x0f:
			f<<"Reserved for extension"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
}




void DecodeNetworkIdentificationType(ofstream f, int indent, BYTE data)
{
    DrawBits(f,indent,data,7,5,"Type of network identification=");
    switch( data&0x70) {
		case 0x00:
			f<<"User specified"; break;
		case 0x20:
			f<<"National network identification"; break;
		case 0x30:
			f<<"International network identification"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
}


void DecodeNetworkIdentificationPlan(ofstream f, int indent, BYTE data)
{
    DrawBits(f,indent,data,4,1,"Network identification plan=");
    switch( data&0x0f) {
		case 0x00:
			f<<"Unknown"; break;
		case 0x01:
			f<<"Carrier identification code"; break;
		case 0x02:
			f<<"User specific"; break;
		case 0x03:
			f<<"Data network identification code (Recommendation X.121)"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
}


void DecodeHighLayerCharacteristics(ofstream f, int indent, BYTE data, bool ExtendedCharacteristics)
{
	register BYTE chars=data&0x7f;
	switch(chars) {
		case 0x01:
			f<<"Telephony"; break;
		case 0x04:
			f<<"Facsimilie Group 2/3 ("<<Recommendation("F.182") << ")"; break;
		case 0x21:
			f<<"Facsimilie Group 4 Class I ("<<Recommendation("F.184")<<")"; break;
		case 0x24:
			f<<"Facsimilie service Group 4, Classes II and III ("<<Recommendation("F.184")<<")"; break;
		case 0x28:
			f<<"Telex service, basic and processable mode of operation ("<<Recommendation("F.220")<<")"; break;
		case 0x31:
			f<<"Telex service, basic mode of operation ("<<Recommendation("F.200")<<")"; break;
		case 0x32:
			f<<"International interworking for Videotex services ("<<Recommendation("F.300,T.102")<<")"; break;
		case 0x35:
			f<<"Telex service ("<<Recommendation("F.60")<<")"; break;
		case 0x38:
			f<<"Message Handling Systems (MHS) ("<<Recommendation("X.400 series")<<")"; break;
		case 0x41:
			f<<"OSI application ("<<Recommendation("X.200 series")<<")"; break;
		case 0x42:
			f<<"FTAM application (ISO 8571)"; break;
		case 0x5e:
			if ( ExtendedCharacteristics)
				f<<"Not available for assignment";
			else
				f<<"Reserved for maintenance"; 
			break;
		case 0x5f:
			if ( ExtendedCharacteristics)
				f<<"Not available for assignment";
			else
				f<<"Reserved for management"; 
			break;
		case 0x60:
			f<<"Videatelephony ("<<Recommendation("F.720,F.721,F.731 profile 1a")<<")"; break;
		case 0x61:
			f<<"Videoconferencing "<<Recommendation("F.702,F.731 profile 1b"); break;
		case 0x62:
			f<<"Audiographc conferencing "<<Recommendation("F.702,F.731 (including profile 2a2 and optionally 2a1, 2a3, 2b1, 2b2 and 2bc)"); break;
		case 0x68:
			f<<"Multimedia serices "<<Recommendation("F.700-series"); break;
		case 0x7f:
			f<<"Reserved"; break;
		default:
			if ((chars>=0x63 && chars<=0x67) || (chars>=0x69 && chars<=0x6f))
				f<<"Reserved for audiovisual service ("<<Recommendation("F.700-series")<<")";
			else
				f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}


void DecodeInformationTransferCapability(ofstream f, int indent, BYTE data)
{
	bool bDummy;
	DecodeInformationTransferCapability(f,indent,data,bDummy);
}
void DecodeInformationTransferCapability(ofstream f, int indent, BYTE data, bool &bUnrestrictedDigital)
{
	bUnrestrictedDigital = false;
    DrawBits(f,indent,data,5,1,"Information transfer capability=");
	switch (data&0x1f) {
		case 0x00:
			f<<"Speech"; break;
		case 0x08:
			f<<"Unrestricted digital information"; 
			bUnrestrictedDigital = true;
			break;
		case 0x09:
			f<<"Restricted digital information"; break;
		case 0x10:
			f<<"3.1 kHz audio"; break;
		case 0x11:
			f<<"Unrestricted digital information with tones/announcements (was: 7 kHz audio)"; break;
		case 0x18:
			f<<"Video"; break;
		default:
			f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
}


static void DecodeITR(ofstream f, int indent, BYTE data, bool &bIsMultirate, char *label)
{
	bIsMultirate=false;
    DrawBits(f,indent,data,5,1,label);
    switch (data&0x1f) {
		case 0x00:
			f<<"Packet rate"; break;
		case 0x10:
			f<<"64 kbit/s"; break;
		case 0x11:
			f<<"2 x 64 kbit/s"; break;
		case 0x13:
			f<<"384 kbit/s"; break;
		case 0x15:
			f<<"1536 kbit/s"; break;
		case 0x17:
			f<<"1920 kbit/s"; break;
		case 0x18:
			f<<"Multirate (64 kbit/s base rate)";
			bIsMultirate = true;
			break;
		default:
		f<<USAGE_RESERVED;
    }
	f<<Break<<endl;
}

void DecodeInformationTransferRate(ofstream f, int indent, BYTE data)
{
	bool bDummy;
	DecodeInformationTransferRate(f,indent,data,bDummy);
}
void DecodeInformationTransferRate(ofstream f, int indent, BYTE data, bool &bIsMultirate)
{
	DecodeITR(f,indent,data,bIsMultirate,"Information transfer rate=");
}


void DecodeInformationTransferRateDO(ofstream f, int indent, BYTE data)
{
	bool bDummy;
	DecodeInformationTransferRateDO(f,indent,data,bDummy);
}
void DecodeInformationTransferRateDO(ofstream f, int indent, BYTE data, bool &bIsMultirate)
{
	DecodeITR(f,indent,data,bIsMultirate,"Information transfer rate (dest->orig)=");
}



void DecodeStructure(ofstream f, int indent, BYTE data)
{
	DrawBits(f,indent,data,7,5,"Structure=");
	switch (data&0x70) {
		case 0x00:
			f<<"Default"; break;
		case 0x10:
			f<<"8 kHz integrity"; break;
		case 0x40:
			f<<"service data unit integrity"; break;
		case 0x70:
			f<<"unstructured"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}


void DecodeConfiguration(ofstream f, int indent, BYTE data)
{
	DrawBits(f,indent,data,4,3,"Configuration=");
	switch (data&0xc0) {
		case 0x00:
			f<<"point-to-point"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}



void DecodeEstablishment(ofstream f, int indent, BYTE data)
{
	DrawBits(f,indent,data,2,1,"Establishment=");
	switch (data&0x03) {
		case 0x00:
			f<<"Demand"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}


void DecodeInformationTransferMode(ofstream f, int indent, BYTE data)
{
	DrawBits(f,indent,data,7,6,"Transfer mode=");
	switch( data&0x60 ) {
		case 0x00:	
			f<<"circuit mode"; break;
		case 0x40:
			f<<"packet mode"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}

void DecodeSymmetry(ofstream f, int indent, BYTE data)
{
	DrawBits(f,indent,data,7,6,"symmetry=");
	switch (data&0x60) {
		case 0x00:
			f<<"bidirectional symmetric"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}

void DecodeLayerIdentification(ofstream f, int indent, BYTE data)
{
	DrawBits(f,indent,data,7,6,"Layer identification=");
	f<<((data&0x60)>>5)<<Break<<endl;
}

void DecodeRateMultiplier(ofstream f, int indent, BYTE data)
{
}



void DecodePresentationIndicator(ofstream f, int indent, BYTE data)
{
	DrawBits(f,indent,data,7,6,"Presentation=");
	switch(data&0x60) {
		case 0x00:
			f<<"Allowed"; break;
		case 0x20:
			f<<"Restricted"; break;
		case 0x40:
			f<<"Not Available"; break;
		case 0x60:
			f<<"Reserved"; break;
	}
	f<<Break<<endl;
}


void DecodeScreeningIndicator(ofstream f, int indent, BYTE data)
{
	DrawBits(f,indent,data,2,1,"Screening=");
	switch(data&0x03) {
		case 0x00:
			f<<"User-provided, not screened"; break;
		case 0x01:
			f<<"User-provided, verified and passed"; break;
		case 0x02:
			f<<"User-provided, verified and failed"; break;
		case 0x03:
			f<<"Network provided"; break;
	}
	f<<Break<<endl;
}


void DecodeReasonForRedirection(ofstream f, int indent, BYTE data)
{
	DrawBits(f,indent,data,4,1,"Reason=");
	switch(data&0x0f) {
		case 0x00:
			f<<"Unknown"; break;
		case 0x01:
			f<<"Call forwarding busy or called DTE busy"; break;
		case 0x02:
			f<<"Call forwarding no reply"; break;
		case 0x04:
			f<<"Call deflection"; break;
		case 0x09:
			f<<"Called DTE out of order"; break;
		case 0xa:
			f<<"Call forwarded by the called DTE"; break;
		case 0x0f:
			f<<"call forwarding unconditional or symmetric call redirection"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}


void DisplayChars(ofstream f, int indent, BYTE data[], int start, int end)
{
	f<<DrawIndent(indent-1);
	for (int j=start;j<end;j++)
		f<<HexOutput(data[j])<<" ";
	f<<Break<<endl;
	f<<DrawIndent(indent);
	for (j=start;j<end;j++)
		f<<((char)(data[j]&0x7f));
	f<<Break<<endl;
}


void DecoderNotImplemented(ofstream f, int indent, BYTE data[], const char *IE)
{
	// as always data[0] contains the IE length
	f<<DrawIndent(indent-1);
	for (int j=0; j<data[0]; j++)
			f<<HexOutput(data[j])<<" ";
	f << Break << endl;
	f << DrawIndent(indent) << "Unhandled Information Element ("<<IE<<")" << Break << endl;
}


void WriteValue(ofstream f, int indent, char *label, BYTE data)
{
	f<<DrawIndent(indent)<<label<<"="<<(int)data<<Break<<endl;
}


void WriteValue(ofstream f, int indent, char *label, int data)
{
	f<<DrawIndent(indent)<<label<<"="<<data<<Break<<endl;
}

void WriteValue(ofstream f, int indent, char *label, char *data)
{
	f<<DrawIndent(indent)<<label<<"="<<data<<Break<<endl;
}


void MoreDataNeeded(ofstream f, int indent)
{
	f<<DrawIndent(indent-1)<<ErrorFontOn<<"Additional data required"<<ErrorFontOff<<Break<<endl;
}

void TooMuchData(ofstream f, int indent, BYTE max)
{
	f<<DrawIndent(indent-1)<<ErrorFontOn<<"Additional data ignored"<<ErrorFontOff<<Break<<endl;
}
