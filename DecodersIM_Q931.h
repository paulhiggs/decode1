
#ifndef __DECODERSIM_Q931_H__
#define __DECODERSIM_Q931_H__

#include <fstream.h>
#include <windows.h>

#include "DecodeIETypes.h"

#define IE_SEGMENTED_MESSAGE						0x00
#define IE_BEARER_CAPABILITY						0x04
#define IE_CAUSE									0x08
#define IE_CALL_IDENTITY							0x10
#define IE_CALL_STATE								0x14
#define IE_CHANNEL_IDENTIFICATION					0x18
#define IE_PROGRESS_INDICATOR						0x1e			
#define IE_NETWORK_SPECIFIC_FACILITIES				0x20
#define IE_NOTIFICATION_INDICATOR					0x27
#define IE_DISPLAY									0x28
#define IE_DATE_TIME								0x29
#define IE_KEYPAD_FACILITY							0x2c
#define IE_SIGNAL									0x34
#define IE_INFORMATION_RATE							0x40
#define IE_END_TO_END_TRANSIT_DELAY					0x42
#define IE_TRANSIT_DELAY_SELECTION_AND_INDICATION	0x43
#define IE_PACKET_LAYER_BINARY_PARAMETERS			0x44
#define IE_PACKET_LAYER_WINDOW_SIZE					0x45
#define IE_PACKET_SIZE								0x46
#define IE_CLOSED_USER_GROUP						0x47
#define IE_REVERSE_CHARGING_INDICATION				0x4a
#define IE_CALLING_PARTY_NUMBER						0x6c
#define IE_CALLING_PARTY_SUBADDRESS					0x6d
#define IE_CALLED_PARTY_NUMBER						0x70
#define IE_CALLED_PARTY_SUBADDRESS					0x71
#define IE_TRANSIT_NETWORK_SELECTION				0x78
#define IE_RESTART_INDICATOR						0x79
#define IE_LOW_LAYER_COMPATABILITY					0x7c
#define IE_HIGH_LAYER_COMPATABILITY					0x7d
#define IE_USER_USER								0x7e
#define IE_ESCAPE_FOR_EXTENSION						0x7f

bool DecodeProtocol(ofstream f, int indent, BYTE data);
bool DecodeCallReferenceLength(ofstream f, int indent, BYTE data);
void DecodeCallReference(ofstream f, int indent, BYTE len, BYTE data1, BYTE data2);
bool DecodeMessageType(ofstream f, int indent, BYTE Protocol, BYTE MessageType );

// Single Octet Decoders
void DecodeCongestionLevel(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeShift(ofstream f, int indent, psGlobalDefs vars, BYTE data[] );
void DecodeRepeatIndication(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);


void DecodeSegmentedMessage(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeChangeStatus(ofstream f, int indent, psGlobalDefs vars, BYTE data[] );
void DecodeBearerCapability(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeCauseQ931(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeConnectedNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeCalledPartyNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeCallingPartyNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);


void DecodeCallIdentity(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeCallState(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeChannelIdentification(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeProgressIndicator(ofstream f, int indent, psGlobalDefs vars, BYTE data[] );
void DecodeNetworkSpecificFacilities(ofstream f, int indent, psGlobalDefs vars, BYTE data[] );

void DecodeNotificationIndicator(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeDisplay(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeInformationRequest(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeCalledPartySubaddress(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeOriginalCalledNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeTransitNetworkSelection(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeRestartIndicator(ofstream f, int indent, psGlobalDefs vars, BYTE data[] );
void DecodeSignal(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeLowLayerCompatability(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeHighLayerCompatability(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeKeypadFacility(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeDateTime(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeUserUser(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeDestination(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeOptions(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeOrigination(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeReasonForReturn(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);



void DecodeInformationRate(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeEndToEndTransitDelay(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeTransitDelaySelectionAndIndication(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodePacketLayerBinaryParameters(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodePacketLayerWindowSize(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodePacketSize(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeClosedUserGroup(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeReverseChargingInformation(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeCallingPartySubaddress(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeEscapeForExtension(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeVPNIndicator(ofstream f, int indent, psGlobalDefs vars, BYTE data[] );
void DecodeTransitCounter(ofstream f, int indent, psGlobalDefs vars, BYTE data[] );

void NoDecoder(ofstream f, int indent, psGlobalDefs vars, BYTE data[] );


#endif 