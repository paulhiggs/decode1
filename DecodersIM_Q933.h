
#ifndef __DECODERSIM_Q933_H__
#define __DECODERSIM_Q933_H__

#include <fstream.h>
#include <windows.h>

#include "DecodeIETypes.h"

#define IE_DATA_LINK_CONNECTION_IDENTIFIER			0x19
#define IE_LINK_LAYER_CORE_PARAMETERS				0x48
#define IE_LINK_LAYER_PROTOCOL_PARAMETERS			0x49
#define IE_X213_PRIORITY							0x50
#define IE_REPORT_TYPE								0x51
#define IE_LINK_INTEGRITY_VERIFICATION				0x52
#define IE_PVC_STATUS								0x57

void DecodeDataLinkConnectionIdentifier(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeLinkLayerCoreParameters(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeLinkLayerProtocolParameters(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeX213Priority(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeReportType(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodeLinkIntegrityVerification(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
void DecodePVCStatus(ofstream f, int indent, psGlobalDefs vars, BYTE data[]);


#endif 