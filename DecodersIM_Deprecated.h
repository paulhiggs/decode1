#ifndef __DECODERSIM_DEPRECATED_H__
#define __DECODERSIM_DEPRECATED_H__

#include <fstream.h>
#include <windows.h>

#include "DecodeIETypes.h"

#define IE_CONNECTED_ADDRESS						0x0c
#define IE_TERMINAL_CAPABILITIES					0x24
#define IE_KEYPAD_ECHO								0x30
#define IE_SWITCHHOOK								0x36

void DecodeConnectedAddress(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeTerminalCapabilities(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeKeypadEcho(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeSwitchhook(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);

#endif