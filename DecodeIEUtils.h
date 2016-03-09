#ifndef __DECODEIMUTILS_H__
#define __DECODEIMUTILS_H__

#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <windows.h>

#include "HTMLfmt.h"
//#include "types.h"

#include "ISDN_defs.h"

extern  const char *USAGE_RESERVED;

#ifndef __BYTEDECLARED
#define __BYTEDECLARED
IOMANIPdeclare( BYTE )
#endif

#ifndef __WORDDECLARED
#define __WORDDECLARED
IOMANIPdeclare( WORD )
#endif


OMANIP (WORD) IEname( WORD fullie );
ostream &IEname( ostream &stream, WORD fullie );

OMANIP (int) DrawIndent( int size );
ostream &DrawIndent( ostream &stream );

OMANIP (BYTE) DrawDigit( BYTE digit );
ostream &DrawDigit( ostream &stream );


bool ExtBitClear(BYTE data);
bool ExtBitSet(BYTE data);

void DisplayDecodeOctet(ofstream f, int indent, BYTE data);
void DisplayDecodeOctet(ofstream f, int indent, BYTE data, char *desc);

void DrawBits( ofstream f, BYTE data, int msb, int lsb );
void DrawBits( ofstream f, int indent, BYTE data, int msb, int lsb );
void DrawBits( ofstream f, int indent, BYTE data, int msb, int lsb, const char *label, bool bEndLine=false );

void DecodeExtBit( ofstream f, int indent, BYTE data );
void DecodeSpare( ofstream f, int indent, BYTE data, int msb, int lsb );
void DecodeReserved( ofstream f, int indent, BYTE data, int msb, int lsb );
bool DecodeBit( ofstream f, int indent, BYTE data, int bit, const char *prefix, const char *setValue, const char *clearValue, const char *suffix="" );

void DecodeNumber(ofstream f, int indent, BYTE data[] );

eChannelType DecodeChannelType(ofstream f, int indent, BYTE data);
void DisplayChars(ofstream f, int indent, BYTE data[], int start, int end);

void DecodeCodingStandard76( ofstream f, int indent, BYTE data );

void DecodeCodingStandard87( ofstream f, int indent, BYTE data );

void DecodeLocation(ofstream f, int indent, BYTE data );

void DecodeTypeOfNumber(ofstream f, int indent, BYTE data );

void DecodeNumberPlanID(ofstream f, int indent, BYTE data );

void DecodeNetworkIdentificationPlan(ofstream f, int indent, BYTE data);
void DecodeNetworkIdentificationType(ofstream f, int indent, BYTE data);

void DecodeHighLayerCharacteristics(ofstream f, int indent, BYTE data, bool ExtendedCharacteristics);

void DecodeInformationTransferCapability(ofstream f, int indent, BYTE data);
void DecodeInformationTransferCapability(ofstream f, int indent, BYTE data, bool &bUnrestrictedDigital);

void DecodeInformationTransferRate(ofstream f, int indent, BYTE data);
void DecodeInformationTransferRate(ofstream f, int indent, BYTE data, bool &bIsMultirate);
void DecodeInformationTransferRateDO(ofstream f, int indent, BYTE data);
void DecodeInformationTransferRateDO(ofstream f, int indent, BYTE data, bool &bIsMultirate);

void DecodeInformationTransferMode(ofstream f, int indent, BYTE data);
void DecodeSymmetry(ofstream f, int indent, BYTE data);
void DecodeLayerIdentification(ofstream f, int indent, BYTE data);
void DecodeRateMultiplier(ofstream f, int indent, BYTE data);

void DecodeConfiguration(ofstream f, int indent, BYTE data);
void DecodeStructure(ofstream f, int indent, BYTE data);
void DecodeEstablishment(ofstream f, int indent, BYTE data);

void DecodeDestination(ofstream f, int indent, BYTE data[]);
void DecodeOptions(ofstream f, int indent, BYTE data[]);
void DecodeOrigination(ofstream f, int indent, BYTE data[]);
void DecodeReasonForReturn(ofstream f, int indent, BYTE data[]);

void DecodePresentationIndicator(ofstream f, int indent, BYTE data);
void DecodeScreeningIndicator(ofstream f, int indent, BYTE data);
void DecodeReasonForRedirection(ofstream f, int indent, BYTE data);


void DecoderNotImplemented(ofstream f, int indent, BYTE data[], const char *IE);

void WriteValue(ofstream f, int indent, char *label, BYTE data);
void WriteValue(ofstream f, int indent, char *label, int data);
void WriteValue(ofstream f, int indent, char *label, char *data);

void MoreDataNeeded(ofstream f, int indent);
void TooMuchData(ofstream f, int indent, BYTE max);

#endif