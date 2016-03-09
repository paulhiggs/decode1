#ifndef __ISDN_DEFS_H__
#define __ISDN_DEFS_H__

//
// ISDN_defs.h
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
//
//////////////////////////////////////////////////////////////////


#define PROTOCOL_MAINTENANCE	0x03
#define PROTOCOL_Q931			0x08
#define PROTOCOL_Q2931			0x09

//
// Message types according to Q.931 05/98 Table 4-2
//
#define MESSAGE_ALERTING				0x01
#define MESSAGE_CALL_PROCEEDING			0x02
#define MESSAGE_CONNECT					0x07
#define MESSAGE_CONNECT_ACKNOWLEDGE		0x0f
#define MESSAGE_PROGRESS				0x03
#define MESSAGE_SETUP					0x05
#define MESSAGE_SETUP_ACKNOWLEDGE		0x0d

#define MESSAGE_RESUME					0x26
#define MESSAGE_RESUME_ACKNOWLEDGE		0x2e
#define MESSAGE_RESUME_REJECT			0x22
#define MESSAGE_SUSPEND					0x25
#define MESSAGE_SUSPEND_ACKNOWLEDGE		0x2d
#define MESSAGE_SUSPEND_REJECT			0x21
#define MESSAGE_USER_INFORMATION		0x20

#define MESSAGE_DISCONNECT				0x45
#define MESSAGE_RELEASE					0x4d
#define MESSAGE_RELEASE_COMPLETE		0x5a
#define MESSAGE_RESTART					0x46
#define MESSAGE_RESTART_ACKNOWLEDGE		0x4e

#define MESSAGE_SEGMENT					0x60
#define MESSAGE_CONGESTION_CONTROL		0x79
#define MESSAGE_INFORMATION				0x7b
#define MESSAGE_NOTIFY					0x6e
#define MESSAGE_STATUS					0x7d
#define MESSAGE_STATUS_ENQUIRY			0x75


//
// Message types according to ETS 300 102-1 Table 3.1
//
#define MESSAGE_FACILITY					0x62
#define MESSAGE_FACILITY_REJECT				0x72

//
// Maintenance Protocol message types
//
#define MESSAGE_SERVICE					0x0f
#define MESSAGE_SERVICE_ACKNOWLEDGE		0x07


#define IE_PROTOCOL_DISCRIMINATOR		0x43
#define IE_CALL_REFERENCE				0x42
#define IE_MESSAGE_TYPE					0x41

//
// Information elements according to Q.931 05/98 Table III-1 (Appendix III)
//
// Single octet information elements:
//  these have bit 8 == 1
#define IE_RESERVED									0x80
#define IE_SHIFT									0x90
#define IE_MORE_DATA								0xa0
#define IE_SENDING_COMPLETE							0xa1
#define IE_CONGESTION_LEVEL							0xb0
#define IE_REPEAT_INDICATOR							0xd0

// Variable length information elements:
//
// Information elements according to Q.931 05/98 Annex M-VPN
//  (CodeSet 4)
// Variable length information elements:
#define IE_TRANSIT_COUNTER							0x31
#define IE_VPN_INDICATOR							0x05


// Codeset 6
#define IE_ORIGINATION								0x01
#define IE_DESTINATION								0x02
#define IE_OPTIONS									0x0a
#define IE_REASON_FOR_RETURN						0x09



BYTE GET_CODESET(WORD fullie);
BYTE GET_IE(WORD fullie);
WORD MAKE_FULLIE(BYTE codeset, BYTE ie);


typedef enum eMessageMode { mandatory, optional, other };
eMessageMode ElementType( BYTE MessageType, BYTE InformationElement );

typedef enum {
	none,
	BChannel,
	H0Channel,
	H11Channel,
	H12Channel
} eChannelType;


#endif