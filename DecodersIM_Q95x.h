
#ifndef __DECODERSIM_Q95x_H__
#define __DECODERSIM_Q95x_H__

#include <fstream.h>
#include <windows.h>

#include "DecodeIETypes.h"

// Q.955 (clause 3)
#define IE_PRECEDENCE_LEVEL							0x41

// Q.951
#define IE_CONNECTED_NUMBER							0x4c
#define IE_CONNECTED_SUBADDRESS						0x4d

// Q.952
#define IE_REDIRECTING_NUMBER						0x74
#define IE_REDIRECTION_NUMBER						0x76

void DecodePrecedenceLevel(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeConnectedNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeConnectedSubaddress(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeRedirectingNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeRedirectionNumber(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);


#endif 