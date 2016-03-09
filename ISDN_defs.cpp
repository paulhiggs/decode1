#include "StdAfx.h"
#include "ISDN_defs.h"

#include "Decoders.h"

BYTE GET_CODESET(WORD fullie)
{
	return (fullie&0xff00)>>8;
}
BYTE GET_IE(WORD fullie)
{
	return (fullie&0x00ff);
}
WORD MAKE_FULLIE(BYTE codeset, BYTE ie)
{
	return (codeset<<8)+ie;
}


eMessageMode ElementType( BYTE MessageType, BYTE InformationElement )
{
	if ( InformationElement==IE_PROTOCOL_DISCRIMINATOR ||
		 InformationElement==IE_CALL_REFERENCE ||
		 InformationElement==IE_MESSAGE_TYPE )
		 return mandatory;

	switch ( MessageType ) {
		case MESSAGE_ALERTING:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_BEARER_CAPABILITY:
				case IE_CHANNEL_IDENTIFICATION:
				case IE_FACILITY:
				case IE_PROGRESS_INDICATOR:
				case IE_DISPLAY:
//				case IE_USER_USER:
				case IE_SIGNAL:
				case IE_HIGH_LAYER_COMPATABILITY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_CALL_PROCEEDING:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_BEARER_CAPABILITY:
				case IE_CHANNEL_IDENTIFICATION:
				case IE_PROGRESS_INDICATOR:
				case IE_DISPLAY:
				case IE_HIGH_LAYER_COMPATABILITY:
					return optional;
				default:
					return other;
			}
			break;
/**/	case MESSAGE_CONGESTION_CONTROL:
			switch (InformationElement) {
				case IE_CONGESTION_LEVEL:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_CAUSE:
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_CONNECT:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_BEARER_CAPABILITY:
				case IE_CHANNEL_IDENTIFICATION:
				case IE_FACILITY:
				case IE_PROGRESS_INDICATOR:
				case IE_DISPLAY:
				case IE_DATE_TIME:
				case IE_SIGNAL:
				case IE_LOW_LAYER_COMPATABILITY:
				case IE_HIGH_LAYER_COMPATABILITY:
//				case IE_USER_USER:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_CONNECT_ACKNOWLEDGE:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
//				case IE_CHANNEL_IDENTIFICATION:
				case IE_DISPLAY:
				case IE_SIGNAL:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_DISCONNECT:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
				case IE_CAUSE:
					return mandatory;
				case IE_FACILITY:
				case IE_PROGRESS_INDICATOR:
				case IE_DISPLAY:
//				case IE_USER_USER:
				case IE_SIGNAL:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_INFORMATION:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_SENDING_COMPLETE:
//				case IE_CAUSE:
				case IE_DISPLAY:
				case IE_KEYPAD_FACILITY:
				case IE_CALLED_PARTY_NUMBER:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_NOTIFY:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
//				case IE_NOTIFICATION_INDICATOR:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_BEARER_CAPABILITY:
				case IE_NOTIFICATION_INDICATOR:
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_PROGRESS:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_PROGRESS_INDICATOR:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_BEARER_CAPABILITY:
				case IE_CAUSE:
				case IE_DISPLAY:
//				case IE_USER_USER:
				case IE_HIGH_LAYER_COMPATABILITY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_RELEASE:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_CAUSE:
				case IE_FACILITY:
				case IE_DISPLAY:
//				case IE_USER_USER:
				case IE_SIGNAL:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_RELEASE_COMPLETE:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_CAUSE:
				case IE_FACILITY:
				case IE_DISPLAY:
//				case IE_USER_USER:
				case IE_SIGNAL:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_RESUME:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_CALL_IDENTITY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_RESUME_ACKNOWLEDGE:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_CHANNEL_IDENTIFICATION:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_RESUME_REJECT:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_CAUSE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_SETUP:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_BEARER_CAPABILITY:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_SENDING_COMPLETE:
				case IE_REPEAT_INDICATOR:
				case IE_CHANNEL_IDENTIFICATION:
				case IE_FACILITY:
				case IE_PROGRESS_INDICATOR:
				case IE_NETWORK_SPECIFIC_FACILITIES:
				case IE_DISPLAY:
				case IE_DATE_TIME:
				case IE_KEYPAD_FACILITY:
				case IE_SIGNAL:
				case IE_CALLING_PARTY_NUMBER:
				case IE_CALLING_PARTY_SUBADDRESS:
				case IE_CALLED_PARTY_NUMBER:
				case IE_CALLED_PARTY_SUBADDRESS:
				case IE_TRANSIT_NETWORK_SELECTION:
				case IE_LOW_LAYER_COMPATABILITY:
				case IE_HIGH_LAYER_COMPATABILITY:
//				case IE_USER_USER:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_SETUP_ACKNOWLEDGE:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_CHANNEL_IDENTIFICATION:
				case IE_PROGRESS_INDICATOR:
				case IE_DISPLAY:
				case IE_SIGNAL:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_STATUS:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_CAUSE:
				case IE_CALL_STATE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_STATUS_ENQUIRY:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_SUSPEND:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_CALL_IDENTITY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_SUSPEND_ACKNOWLEDGE:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
		case MESSAGE_SUSPEND_REJECT:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_CAUSE:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
/**/	case MESSAGE_USER_INFORMATION:
			switch (InformationElement) {
				case IE_PROTOCOL_DISCRIMINATOR:
				case IE_CALL_REFERENCE:
				case IE_USER_USER:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_MORE_DATA:
					return optional;
				default:
					return other;
			}
			break;
/**/	case MESSAGE_RESTART:
			switch (InformationElement) {
				case IE_RESTART_INDICATOR:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_CHANNEL_IDENTIFICATION:
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
/**/	case MESSAGE_RESTART_ACKNOWLEDGE:
			switch (InformationElement) {
				case IE_RESTART_INDICATOR:
				case IE_MESSAGE_TYPE:
					return mandatory;
				case IE_CHANNEL_IDENTIFICATION:
				case IE_DISPLAY:
					return optional;
				default:
					return other;
			}
			break;
	}

	return other;
}