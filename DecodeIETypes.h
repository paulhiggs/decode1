#ifndef __DECODEIE_TYPES__
#define __DECODEIE_TYPES__

#include "stdafx.h"
#include <fstream.h>

typedef struct {
	BYTE	ActiveCodeSet,LastCodeSet;
	bool	GlobalCallReference;
	int		LockCount;

} sGlobalDefs, *psGlobalDefs;

typedef void (*pvDecoder_Type) (ofstream f, int indent, psGlobalDefs vars, BYTE data[]);
typedef struct {
	char			*IEname;
	BYTE			CodeSet;
	BYTE			IEid;
	BYTE			IEidMask;
	pvDecoder_Type	DecodeFunction;
} sIEDecoderEntry, *psIEDecoderEntry;


#endif