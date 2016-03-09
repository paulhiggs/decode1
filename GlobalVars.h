#ifndef __GLOBALVARS_H__
#define __GLOBALVARS_H__

#include "stdafx.h"

class GlobalVars 
{
public:
	int g_timestampMode;
	int g_splitLine;
	CString g_lineDelim;
	int g_dropCallFilter;
	int g_decodeVersion;
	int g_doISDNdecode;
	
	const GlobalVars& operator=(const GlobalVars& srcVars);

};

bool AFXAPI operator==(const GlobalVars& v1, const GlobalVars& v2);
bool AFXAPI operator!=(const GlobalVars& v1, const GlobalVars& v2);


#endif