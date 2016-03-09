
#ifndef __DECODERSIM_Q932_H__
#define __DECODERSIM_Q932_H__

#include <fstream.h>
#include <windows.h>

#include "DecodeIETypes.h"

#define IE_EXTENDED_FACILITY						0x0e
#define IE_FACILITY									0x1c
#define IE_INFORMATION_REQUEST						0x32
#define IE_FEATURE_ACTIVATION						0x38
#define IE_FEATURE_INDICATION						0x39
#define IE_SERVICE_PROFILE_IDENTIFICATION			0x3a
#define IE_ENDPOINT_IDENTIFIER						0x3b


void DecodeExtendedFacility(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeFacility(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeInformationRequest(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

void DecodeFeatureActivation(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeFeatureIndication(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeServiceProfileIdentification(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeEndpointIdentifier(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

#endif 