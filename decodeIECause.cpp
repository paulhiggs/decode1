//
// DecodersIMCause.cpp
//
//////////////////////////////////////////////////////////////////
//
// Revision information
//
//
// April 8 2002: ewcpahi:
//  Added length checking for cause IE
//
//////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Decoders.h"

#include "HTMLfmt.h"
#include "ISDN_defs.h"

#include "DecodeIEUtils.h"


typedef enum CauseDiagnostics {
	DIAG_CONDITION					=0x0001,
	DIAG_TRANSIT_NETWORK_IDENTITY	=0x0002,
	DIAG_CCBS_INDICATOR				=0x0004,
	DIAG_CALL_REJECTED				=0x0008,
	DIAG_NEW_DESTINATION			=0x0010,
	DIAG_FACILITY_IDENTIFICATION	=0x0020,
	DIAG_ATTRIBUTE_IDENTITY			=0x0040,
	DIAG_CHANNEL_TYPE				=0x0080,
	DIAG_INCOMPATABLE_PARAMETER		=0x0100,
	DIAG_TIMER_NUMBER				=0x0200,
	DIAG_MESSAGE_TYPE				=0x0400,
	DIAG_PARAMETER_NAME				=0x0800,   // only for ISUP
//	DIAG_CLEARING_CAUSE				=0x4000,
//	DIAG_CHANNEL_IDENTITY			=0x8000
};

static int DecodeCauseOctetQ931(ofstream f, int indent, BYTE data)
{
	int cClass=data&0x70, cValue=data&0x7f;
	int iDiagMode=0;
    DisplayDecodeOctet(f,indent,data);
    DecodeExtBit(f,indent,data);
    DrawBits(f,indent,data,7,5,"Class=");
    switch(cClass) {
		case 0x00:
		case 0x10:
			f<<"Normal event"; break;
		case 0x20:
			f<<"Resource unavailable"; break;
		case 0x30:
			f<<"Service or option not available"; break;
		case 0x40:
			f<<"Service or option not implemented"; break;
		case 0x50:
			f<<"Invalid message (i.e. parameter out of range)"; break;
		case 0x60:
			f<<"Protocol error (i.e. unknown message)"; break;
		case 0x70:
			f<<"Interworking"; break;
    }
	f<<Break<<endl;
    DrawBits(f,indent,data,4,1,"Definition=");
	switch(cValue) {
		case 0x01:
			f<<"Unallocated (unassigned) number"; 
			iDiagMode = DIAG_CONDITION;
			break;
		case 0x02:
			f<<"No route to specified transit network";  
			iDiagMode = DIAG_TRANSIT_NETWORK_IDENTITY;
			break;
		case 0x03:
        	f<<"No route to destination"; 
			iDiagMode = DIAG_CONDITION;
			break;
		case 0x04:
        	f<<"Send special information time"; break;
		case 0x05:
        	f<<"Misdialled trunk prefix"; break;
		case 0x06:
        	f<<"Channel unacceptable"; break;
		case 0x07:
        	f<<"Call awarded and being delivered in an established channel"; break;
		case 0x08:
        	f<<"Preemption"; break;
		case 0x09:
        	f<<"Preemption-circuit reserved for reuse"; break;
		case 0x0e:			// Q.850 Add.1 //
			f<<"QoR: ported number"; break;
      	case 0x10:
        	f<<"Normal call clearing"; 
			iDiagMode = DIAG_CONDITION;
			break;
      	case 0x11:
        	f<<"User busy"; 
			iDiagMode = DIAG_CCBS_INDICATOR;
			break;
      	case 0x12:
        	f<<"No user responding"; break;
      	case 0x13:
        	f<<"No answer from user (user alerted)"; break;
		case 0x14:
			f<<"Subscriber absent"; break;
      	case 0x15:
        	f<<"Call rejected"; 
			iDiagMode = DIAG_CALL_REJECTED;
			break;
      	case 0x16:
        	f<<"Number changed"; 
			iDiagMode = DIAG_NEW_DESTINATION;
			break;
		case 0x17:
			f<<"Redirection to new destination"; break;
		case 0x18:			// Q.850 Amd.1 //
			f<<"Call rejected due to feature at the destination"; break;
		case 0x19:
			f<<"Exchange routing error"; break;
		case 0x1a:
			f<<"Non-selected user clearing"; break;
      	case 0x1b:
        	f<<"Destination out of order"; break;
      	case 0x1c:
        	f<<"Invalid number format (address incomplete)"; break;
      	case 0x1d:
        	f<<"Facility rejected";  
			iDiagMode = DIAG_FACILITY_IDENTIFICATION;
			break;
      	case 0x1e:
        	f<<"Response to STATUS ENQUIRY"; break;
      	case 0x1f:
        	f<<"Normal, unspecified"; break;
      	case 0x22:
        	f<<"No circuit/channel available";  
			iDiagMode = DIAG_CCBS_INDICATOR;
			break;
		case 0x26:
			f<<"Network out of order"; break;
		case 0x27:
			f<<"Permanent frame mode connection out of service"; break;
		case 0x28:
			f<<"Permanent frame mode connection operational"; break;
      	case 0x29:
        	f<<"Temporary failure"; break;
      	case 0x2a:
        	f<<"Switch equipment congestion"; break;
      	case 0x2b:
        	f<<"Access information discarded"; break;
      	case 0x2c:
        	f<<"Requested circuit/channel not available"; break;
		case 0x2e:
			f<<"Precedence call blocked"; break;
      	case 0x2f:
        	f<<"Resources unavailable, unspecified"; break;
		case 0x31:
			f<<"Quality of service not available";   
			iDiagMode = DIAG_CONDITION;
			break;
      	case 0x32:
        	f<<"Requested facility not subscriber";    
			iDiagMode = DIAG_FACILITY_IDENTIFICATION;
			break;
		case 0x35:
			f<<"Outgoing calls barred within CUG"; break;
      	case 0x36:
        	f<<"Incoming calls barred within CUG"; break;
      	case 0x39:
        	f<<"Bearer capability not authorized";    
			iDiagMode = DIAG_ATTRIBUTE_IDENTITY;
			break;
      	case 0x3a:
        	f<<"Bearer capability not presently available";    
			iDiagMode = DIAG_ATTRIBUTE_IDENTITY;
			break;
		case 0x3e:
			f<<"Inconsistency in designated outgoing access information and subscriber class"; break;
      	case 0x3f:
        	f<<"Service or option not available, unspecified"; break;
      	case 0x41:
        	f<<"Bearer capability not implemented";    
			iDiagMode = DIAG_ATTRIBUTE_IDENTITY;
			break;
      	case 0x42:
        	f<<"Channel type not implemented";    
			iDiagMode = DIAG_CHANNEL_TYPE;
			break;
		case 0x45:
			f<<"Requested facility not implemented";    
			iDiagMode = DIAG_FACILITY_IDENTIFICATION;
			break;
      	case 0x46:
        	f<<"Only restricted digital information bearer capability is available"; break;
      	case 0x4f:
        	f<<"Service or option not implemented, unspecified"; break;
      	case 0x51:
        	f<<"Invalid call reference value"; break;
      	case 0x52:
        	f<<"Identified channel does not exist";    
//			iDiagMode = DIAG_CHANNEL_IDENTITY;
			break;
		case 0x53:
			f<<"A suspended call exists, but this call identity does not"; break;
		case 0x54:
			f<<"Call identity in use"; break;
		case 0x55:
			f<<"No call suspended"; break;
		case 0x56:
			f<<"Call having the requested call identity has been cleared";    
//			iDiagMode = DIAG_CLEARING_CAUSE;
			break;
		case 0x57:
			f<<"User not member of CUG"; break;
      	case 0x58:
        	f<<"Incompatable destination";    
			iDiagMode = DIAG_INCOMPATABLE_PARAMETER;
			break;
/*
      	case 0x5a:
        	f<<"Destination address missing, and direct call not subscribed"; break;
*/
		case 0x5a:
			f<<"Non-exustan CUG"; break;
		case 0x5b:
			f<<"Invalid transit network selection"; break;
		case 0x5f:
        	f<<"Invalid message, unspecified"; break;
      	case 0x60:
        	f<<"Mandatory information element is missing"; break;
      	case 0x61:
        	f<<"Message type non-existant or not implemented";    
			iDiagMode = DIAG_MESSAGE_TYPE;
			break;
		case 0x62:
			f<<"Message not compatable with call state or message type non-existant or not implemented";    
			iDiagMode = DIAG_MESSAGE_TYPE;
			break;
      	case 0x63:
        	f<<"Information element/parameter non-existant or not implemented"; break;
      	case 0x64:
        	f<<"Invalid information element contents"; break;
      	case 0x65:
        	f<<"Message not compatable with call state";    
			iDiagMode = DIAG_MESSAGE_TYPE;
			break;
      	case 0x66:
        	f<<"Recovery on timer expiry";    
			iDiagMode = DIAG_TIMER_NUMBER;
			break;
		case 0x67:
			f<<"Parameter non-existant or not implemented, passed on";    
			iDiagMode = DIAG_PARAMETER_NAME;
			break;
		case 0x6e:
			f<<"Message with unrecognized parameter, discarded";    
			iDiagMode = DIAG_PARAMETER_NAME;
			break;
      	case 0x6f:
        	f<<"Protocol error, unspecified"; break;
      	case 0x7f:
        	f<<"Interworking, unspecified"; break;
		default:
			f << USAGE_RESERVED;
	}
	f<<Break<<endl;
	return iDiagMode;
}



// decode Condition Cause Diagnostic per Q.850 2.2.6.1
static void DecodeDiagnosticCondition(ofstream f,int indent,BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"Diagnostic=Condition");
	DrawBits(f,indent,data,8,8,"Must be 1", true);
	DrawBits(f,indent,data,7,5,"Must be 000", true);
	DrawBits(f,indent,data,4,4,"Network Service - ");
	f<<((data&0x08)?"User":"Provider")<<Break<<endl;
	DrawBits(f,indent,data,3,3);
	f<<((data&0x04)?"Abnormal":"Normal")<<Break<<endl;
	DrawBits(f,indent,data,2,1);
	switch(data&0x03) {
		case 0x00:
			f<<"Unknown"; break;
		case 0x01:
			f<<"Permanent"; break;
		case 0x02:
			f<<"Transient"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
}



// decode Transit Network Identity Cause Diagnostic per Q.850 2.2.6.2
static void DecodeDiagnosticTransitNetworkIdentity(ofstream f,int indent,BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"Diagnostic=Transit Network Identity");
	DrawBits(f,indent,data,8,1, "Transit network identity (!!ph!!)",true);
}


// decode CCBS Cause Diagnostic per Q.850 2.2.6.3
static void DecodeDiagnosticCCBS(ofstream f,int indent,BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"Diagnostic=CCBS");
	DrawBits(f,indent,data,8,1);
	if ( data==0x00 )
		f<<"Spare";
	else if ( data==0x01 )
		f<<"CCBS possible";
	else if ( data==0x02 )
		f<<"CCBS not possible";
	else if ( data>=0x03 && data<=0x7f)
		f<<"Spare";
	else if ( data>=0x80 && data<=0xfe)
		f<<"Spare for national use";
	else 
		f<<"Reserved for Extension";
	f<<Break<<endl;
}


// decode Call Rejected Cause Diagnostic per Q.850 2.2.6.4
static void DecodeDiagnosticCallRejected(ofstream f,int indent,BYTE data[], int startIndex)
{
	int ofs=0;	
	bool bUserSpecificReason = false, bIElementError = false;
	DisplayDecodeOctet(f,indent,data[startIndex],"Diagnostic=Call Rejected");
	DecodeExtBit(f,indent,data[startIndex]);
	DrawBits(f,indent,data[startIndex],7,3,"Rejection reason=");
	switch (data[startIndex]&0x7c) {
		case 0x00:
			f<<"user specific"; 
			bUserSpecificReason=true;
			break;
		case 0x04:
			f<<"information element missing"; 
			bIElementError=true;
			break;
		case 0x08:
			f<<"information element contents are not sufficient"; 
			bIElementError=true;
			break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;
	DrawBits(f,indent,data[startIndex],2,1,"Condition=");
	switch (data[startIndex]&0x03) {
		case 0x00:
			f<<"unknown"; break;
		case 0x01:
			f<<"permanent"; break;
		case 0x02:
			f<<"transient"; break;
		case 0x03:
			f<<"spare"; break;
	}
	f<<Break<<endl;
	
	if ( bUserSpecificReason ) {
		// data[startIndex+1] contains the User-specific diagnostic;
		DisplayDecodeOctet(f,indent,data[startIndex+1]);
		DrawBits(f,indent,data[startIndex+1],8,1,"User-specific diagnostic",true);
		ofs++;
	}
	if ( bIElementError ) {
		// data[startIndex+1+ofs] contains the offending IE
		DisplayDecodeOctet(f,indent,data[startIndex+1+ofs]);
		DrawBits(f,indent,data[startIndex+1+ofs],8,8,"IE type=");
		f<<( (data[startIndex+1+ofs]&0x80)?"fixed":"variable" )<<" length information element"<<Break<<endl;
		
		DrawBits(f,indent,data[startIndex+1+ofs],7,1,"IE=");
		f<<IEname(MAKE_FULLIE(0,data[startIndex+1+ofs]))<<Break<<endl;
	}
}


// decode New Destination Cause Diagnostic per Q.850 2.2.6.5
static void DecodeDiagnosticNewDestination(ofstream f,int indent,BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"Diagnostic=New Destination");
	DrawBits(f,indent,data,8,1, "New destination (!!ph!!)",true);
}



// decode Facility Identification Cause Diagnostic per Q.850 2.2.6.6
static void DecodeDiagnosticFacilityIdentification(ofstream f,int indent,BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"Diagnostic=Facility Identification");
	DrawBits(f,indent,data,8,1, "Facility identification (!!ph!!)",true);
}



// decode Attribute Identity Cause Diagnostic per Q.850 2.2.6.7
//
// display attribute information accoring to Q.850 table-3b
static void DecodeAttribute(ofstream f, int indent, BYTE data, int AttributeNo)
{
	DisplayDecodeOctet(f,indent,data);
	DecodeExtBit(f,indent,data);
	switch (AttributeNo) {
		case 1:		// Information transfer capability
			DecodeSpare(f,indent,data,7,6);
			DecodeInformationTransferCapability(f,indent,data);
			break;
		case 2:		// Information transfer mode
			DecodeInformationTransferMode(f,indent,data);
			DecodeSpare(f,indent,data,5,1);
			break;
		case 3:		// Infomation transfer rate
			DecodeSpare(f,indent,data,7,6);
			DecodeInformationTransferRate(f,indent,data);
			break;
		case 4:		// Structure
			DecodeSpare(f,indent,data,7,5);
			DecodeStructure(f,indent,data);
			DecodeSpare(f,indent,data,2,1);
			break;
		case 5:		// Configuration
			DecodeSpare(f,indent,data,7,3);
			DecodeConfiguration(f,indent,data);
			break;
		case 6:		// Establishment
			DecodeSpare(f,indent,data,7,6);
			DecodeEstablishment(f,indent,data);
			break;
		case 7:		// Symmetry
			DecodeSymmetry(f,indent,data);
			DecodeSpare(f,indent,data,5,1);
			break;
		case 8:		// Information transfer rate (dest->orig)
			DecodeSpare(f,indent,data,7,6);
			DecodeInformationTransferRateDO(f,indent,data);
			break;
		case 9:		// Layer Identification
			DecodeSpare(f,indent,data,7,6);
			DecodeLayerIdentification(f,indent,data);
			break;
		case 10:	// Rate multiplier
			DecodeRateMultiplier(f,indent,data);
			break;
	}
}

static void DecodeDiagnosticAttributeIdentity(ofstream f,int indent, BYTE data[],int startIndex)
{
	DisplayDecodeOctet(f,indent,data[startIndex],"Diagnostic=Attribute Identity");
	DecodeExtBit(f,indent,data[startIndex]);
	DrawBits(f,indent,data[startIndex],7,1);
	switch ( data[startIndex]&0x7f ) {
		case 0x31:
			f<<"1 Information transfer capability"; break;
		case 0x32:
			f<<"2 Information transfer mode"; break;
		case 0x33:
			f<<"3 Information transfer rate"; break;
		case 0x34:
			f<<"4 Structure"; break;
		case 0x35:
			f<<"5 Configuration"; break;
		case 0x36:
			f<<"6 Establishment"; break;
		case 0x37:
			f<<"7 Symmetry"; break;
		case 0x38:
			f<<"8 Information tranfser rate (dest->orig)"; break;
		case 0x39:
			f<<"9 Layer identification"; break;
		default:
			f<<USAGE_RESERVED;
	}
	f<<Break<<endl;

	
	if ( ExtBitClear(data[startIndex]) ) {
		DecodeAttribute(f,indent,data[startIndex+1],(data[startIndex]&0x7f)-0x30);

		if ( ExtBitClear(data[startIndex+1]) )
			DecodeAttribute(f,indent,data[startIndex+2],(data[startIndex]&0x7f)-0x30);
	}

}


// decode Channel Type Cause Diagnostic per Q.850 2.2.6.8
static void DecodeDiagnosticChannelType(ofstream f,int indent,BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"Diagnostic=Channel Type");
    DecodeExtBit(f,indent,data);
	DecodeSpare(f,indent,data,7,5);
	DecodeChannelType(f,indent,data);
}



// decode Incompatible Parameter Cause Diagnostic per Q.850 2.2.6.9
static void DecodeDiagnosticIncompatableParameter(ofstream f,int indent,BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"Diagnostic=Incompatable Parameter");
	DrawBits(f,indent,data,8,1, "Incompatible Parameter (!!ph!!)",true);
}


// decode Timer Number Cause Diagnostic per Q.850 2.2.6.10
static void DecodeDiagnosticTimerNumber(ofstream f,int indent,BYTE data[], int startIndex)
{
	f<<DrawIndent(indent-1);
	int i=-1;
	do {
		i++;
		f<<HexOutput(data[startIndex+i])<<" ";
	} while (ExtBitClear(data[startIndex+i]));
	f<<Break<<endl;
	f<<DrawIndent(indent)<<"Timer Number=";
	i=-1;
	do {
		i++;
		f<<(char)(data[startIndex+i]&0x7f);
	} while (ExtBitClear(data[startIndex+i]));
}



// decode Message Type Cause Diagnostic per Q.850 2.2.6.11
static void DecodeDiagnosticMessageType(ofstream f,int indent,BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"Diagnostic=Message Type");
	DecodeMessageType(f,indent,PROTOCOL_Q931,data);
}



// decode ParameterName Cause Diagnostic per Q.850 2.2.6.12
void DisplayQ763ParameterName(ofstream f, BYTE data);

static void DecodeDiagnosticParameterName(ofstream f,int indent,BYTE data)
{
	DisplayDecodeOctet(f,indent,data,"Diagnostic=Parameter Name");
	DrawBits(f,indent,data,8,1, "Parameter name=");
	DisplayQ763ParameterName(f, data);
}




void DecodeCauseQ931(ofstream f, int indent, psGlobalDefs vars, BYTE data[] )
{
	int hasExt=0;
    DisplayDecodeOctet(f,indent,data[1]);
    DecodeExtBit(f,indent,data[1]);
    DecodeCodingStandard76(f,indent,data[1]);
	DecodeSpare(f,indent,data[1],5,5);
    DecodeLocation(f,indent,data[1]);
    if (ExtBitClear(data[1])) {
		// octet 3a in data[2]
		DisplayDecodeOctet(f,indent,data[2]);
		DecodeExtBit(f,indent,data[2]);
		DrawBits(f,indent,data[2],7,1,"Recommendation=");
		switch (data[2]&0x7f) {
			case 0x00:
				f<<"Q.931"; break;
			case 0x03:
				f<<"X.21"; break;
			case 0x04:
				f<<"X.25"; break;
			case 0x05:
				f<<"public land mobile networks, Q.1031/Q.1051"; break;
			default:
				f<<USAGE_RESERVED;
		}
		f<<Break<<endl;
		hasExt++;
	}
	int iDiags = DecodeCauseOctetQ931(f,indent,data[2+hasExt]);

    if (data[0]<=(2+hasExt))
		return;

	switch (iDiags) {
		case DIAG_CONDITION:
			DecodeDiagnosticCondition(f,indent,data[2+hasExt+1]);
			break;
		case DIAG_TRANSIT_NETWORK_IDENTITY:
			DecodeDiagnosticTransitNetworkIdentity(f,indent,data[2+hasExt+1]);
			break;
		case DIAG_CCBS_INDICATOR:
			DecodeDiagnosticCCBS(f,indent,data[2+hasExt+1]);
			break;
		case DIAG_CALL_REJECTED:
			DecodeDiagnosticCallRejected(f,indent,data,2+hasExt+1);
			break;
		case DIAG_NEW_DESTINATION:
			DecodeDiagnosticNewDestination(f,indent,data[2+hasExt+1]);
			break;
		case DIAG_FACILITY_IDENTIFICATION:
			DecodeDiagnosticFacilityIdentification(f,indent,data[2+hasExt+1]);
			break;
		case DIAG_ATTRIBUTE_IDENTITY:
			DecodeDiagnosticAttributeIdentity(f,indent,data,2+hasExt+1);
			break;
		case DIAG_CHANNEL_TYPE:
			DecodeDiagnosticChannelType(f,indent,data[2+hasExt+1]);
			break;
		case DIAG_INCOMPATABLE_PARAMETER:
			DecodeDiagnosticIncompatableParameter(f,indent,data[2+hasExt+1]);
			break;
		case DIAG_TIMER_NUMBER:
			DecodeDiagnosticTimerNumber(f,indent,data, 2+hasExt+1);
			break;
		case DIAG_MESSAGE_TYPE:
			DecodeDiagnosticMessageType(f,indent,data[2+hasExt+1]);
			break;
		case DIAG_PARAMETER_NAME:
			DecodeDiagnosticParameterName(f,indent,data[2+hasExt+1]);
			break;
//		case DIAG_CLEARING_CAUSE:
//			DecodeDiagnosticClearingCause(f,indent,data[2+hasExt+1]);
//			break;
//		case DIAG_CHANNEL_IDENTITY:
//			DecodeDiagnosticChannelIdentity(f,indent,data[2+hasExt+1]);
//			break;
	}
}




static char *reservedBISUP = "Reserved for B-ISUP";
static char *notUsed = "";

static char *ParameterNames[] = {
// 0x0-
	"End of optional parameters",			//0
	"Call reference (national use)",		//1
	"Transmission medium requirement",		//2
	"Access transport",						//3
	"Called party number",					//4
	"Subsequent number"						//5
	"Nature of connection indicators",		//6
	"Forward call indicators",				//7
	"Optional forward call indicators",		//8
	"Calling party's category"				//9
	"Calling party number",					//a
	"Redirecting number",					//b
	"Redirection number",					//c
	"Connection request",					//d
	"Information request indicators (national use)",	//e
	"Informational indicators (national use)",			//f
// 0x1-
	"Continuity indicators",			//0
	"Backward call indicators",			//1
	"Cause indicators",			//2
	"Redirection information",			//3
	"Reserved (used in 1984 version, Red Book)",			//4
	"Circuit group supervision messge type",			//5
	"Range and status",			//6
	"Reserved (used in 1988 version, Blue Book)",			//7
	"Facility indicator",			//8
	"Reserved (used in 1984 version, Red Book)",			//9
	"Closed user group interlock code",			//a
	"Reserved (used in 1984 version, Red Book)",			//b
	"Reserved (used in 1984 version, Red Book)",			//c
	"User service information",			//d
	"Signalling point code (national use)",			//e
	"Reserved (used in 1984 version, Red Book)",			//f
// 0x2-
	"User-to-user information",			//0
	"Connected number",			//1
	"Suspend/Resume indicators",			//2
	"Transit network selection (national use)",			//3
	"Event information",			//4
	"Circuit assignment map",			//5
	"Circuit state indicator (national use)",			//6
	"Automatic congestion level",			//7
	"Optional called number",			//8
	"Optional backward call indicators",			//9
	"User-to-user indicators",			//a
	"Origination ISC point code",			//b
	"Generic notification indicator",			//c
	"Call history information",			//d
	"Access delivery information",			//e
	"Network specific facility (national use)",			//f
// 0x3-
	"User service information prime",			//0
	"Propagation delay counter",			//1
	"Remote operations (national use)",			//2
	"Service activation",			//3
	"User teleservice information",			//4
	"Transmission medium used",			//5
	"Call diversion information",			//6
	"Echo control information",			//7
	"Message compatibility information",			//8
	"Parameter compatibility information",			//9
	"MLPP precedence",			//a
	"MCID request indicators",			//b
	"MCID response indicators",			//c
	"Hop counter",			//d
	"Transmission medium requirement prime",			//e
	"Location number",			//f
// 0x4-
	"Redirection number restriction",			//0
	notUsed,			//1
	notUsed,			//2
	"Call transfer reference",			//3
	"Loop prevention indicators",			//4
	"Call transfer number",			//5
	reservedBISUP,			//6
	reservedBISUP,			//7
	reservedBISUP,			//8
	reservedBISUP,			//9
	reservedBISUP,			//a
	"CCSS",			//b
	"Forward GVNS",			//c
	"Backward GVNS",			//d
	"Redirect capability (national use)",			//e
	reservedBISUP,			//f
// 0x5-
	reservedBISUP,			//0
	reservedBISUP,			//1
	reservedBISUP,			//2
	reservedBISUP,			//3
	reservedBISUP,			//4
	reservedBISUP,			//5
	reservedBISUP,			//6
	reservedBISUP,			//7
	reservedBISUP,			//8
	reservedBISUP,			//9
	reservedBISUP,			//a
	"Network management controls",			//b
	reservedBISUP,			//c
	reservedBISUP,			//d
	reservedBISUP,			//e
	reservedBISUP,			//f
// 0x6-
	reservedBISUP,			//0
	"Reserved (used in 1992 version)",			//1
	"Reserved (used in 1992 version)",			//2
	reservedBISUP,			//3
	reservedBISUP,			//4
	"Correlation id",			//5
	"SCF id",			//6
	reservedBISUP,			//7
	reservedBISUP,			//8
	reservedBISUP,			//9
	reservedBISUP,			//a
	reservedBISUP,			//b
	reservedBISUP,			//c
	reservedBISUP,			//d
	"Call diversion treatment indicators",			//e
	"Call IN number",			//f
// 0x7-
	"Call offering treatment indicators",			//0
	"Charged perty identification (national use)",			//1
	"Conference treatment indicators",			//2
	"Display information",			//3
	"UID action indicators",			//4
	"UID capability indicators",			//5
	reservedBISUP,			//6
	"Redirect counter (national use)",			//7
	"Application transport",			//8
	"Collect call request",			//9
	"CCNR possible indicator",			//a
	"Pivot capability",			//b
	"Pivot routing indicators",			//c
	"Called directory number (national use)",			//d
	reservedBISUP,			//e
	"Original called IN number",			//f
// 0x8-
	"Reserved for future extension",			//0
	"Called geodetic location",			//1
	"HTR information",			//2
	notUsed,			//3
	"Network routing number (national use)",			//4
	"Query on release capability",			//5
	"Pivot status (national use)",			//6
	"Pivot counter",			//7
	"Pivot routing forward indication",			//8
	"Pivot routing backward indication",			//9
	"Redirect status (national use)",			//a
	"Redirect forward information (national use)",			//b
	"Redirect backward information (national use)",			//c
	"Number portabiity forward information (network option)",			//d
	notUsed,			//e
	reservedBISUP,			//f
// 0x9-
	reservedBISUP,			//0
	reservedBISUP,			//1
	reservedBISUP,			//2
	reservedBISUP,			//3
	reservedBISUP,			//4
	reservedBISUP,			//5
	reservedBISUP,			//6
	reservedBISUP,			//7
	reservedBISUP,			//8
	reservedBISUP,			//9
	notUsed,			//a
	notUsed,			//b
	notUsed,			//c
	notUsed,			//d
	notUsed,			//e
	notUsed,			//f
// 0xA-
	notUsed,			//0
	notUsed,			//1
	notUsed,			//2
	notUsed,			//3
	notUsed,			//4
	notUsed,			//5
	notUsed,			//6
	notUsed,			//7
	notUsed,			//8
	notUsed,			//9
	notUsed,			//a
	notUsed,			//b
	notUsed,			//c
	notUsed,			//d
	notUsed,			//e
	notUsed,			//f
// 0xB-
	notUsed,			//0
	notUsed,			//1
	notUsed,			//2
	notUsed,			//3
	notUsed,			//4
	notUsed,			//5
	notUsed,			//6
	notUsed,			//7
	notUsed,			//8
	notUsed,			//9
	notUsed,			//a
	notUsed,			//b
	notUsed,			//c
	notUsed,			//d
	notUsed,			//e
	notUsed,			//f
// 0xC-
	"Generic number",			//0
	"Generic digits (national use)",			//1
	notUsed,			//2
	notUsed,			//3
	notUsed,			//4
	notUsed,			//5
	notUsed,			//6
	notUsed,			//7
	notUsed,			//8
	notUsed,			//9
	notUsed,			//a
	notUsed,			//b
	notUsed,			//c
	notUsed,			//d
	notUsed,			//e
	notUsed,			//f
// 0xD-
	notUsed,			//0
	notUsed,			//1
	notUsed,			//2
	notUsed,			//3
	notUsed,			//4
	notUsed,			//5
	notUsed,			//6
	notUsed,			//7
	notUsed,			//8
	notUsed,			//9
	notUsed,			//a
	notUsed,			//b
	notUsed,			//c
	notUsed,			//d
	notUsed,			//e
	notUsed,			//f
// 0xE-
	notUsed,			//0
	notUsed,			//1
	notUsed,			//2
	notUsed,			//3
	notUsed,			//4
	notUsed,			//5
	notUsed,			//6
	notUsed,			//7
	notUsed,			//8
	notUsed,			//9
	notUsed,			//a
	notUsed,			//b
	notUsed,			//c
	notUsed,			//d
	notUsed,			//e
	notUsed,			//f
// 0xF-
	notUsed,			//0
	notUsed,			//1
	notUsed,			//2
	notUsed,			//3
	notUsed,			//4
	notUsed,			//5
	notUsed,			//6
	notUsed,			//7
	notUsed,			//8
	notUsed,			//9
	notUsed,			//a
	notUsed,			//b
	notUsed,			//c
	notUsed,			//d
	notUsed,			//e
	notUsed,			//f
};

void DisplayQ763ParameterName(ofstream f, BYTE data)
{
	f<<HexOutput(data)<<" "<<ParameterNames[data]<<Break<<endl;
}


