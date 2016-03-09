
#ifndef __DECODERS_H__
#define __DECODERS_H__

#include "ISDN_Defs.h"
#include "DecodeIETypes.h"
#include "DecodeIEUtils.h"

#include "DecodersIM_Q931.h"
#include "DecodersIM_Q932.h"
#include "DecodersIM_Q933.h"
#include "DecodersIM_Q95x.h"
#include "DecodersIM_Deprecated.h"

extern sIEDecoderEntry IEDecoders[];


// LF Decoders
void decodeNewState(ofstream f, CString line, CString lineSelector, int timestampMode);
void decodeSignal(ofstream f, CString line, CString lineSelector, int timestampMode);
void decodeLogEvent(ofstream f, CString line, CString lineSelector, int timestampMode);
void decodeOther(ofstream f, CString line, int timestampMode);
void decodeISDNMessage(ofstream f, CString line, int timestampMode);


#endif __DECODERS_H__