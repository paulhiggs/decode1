// GlobalVars.cpp

#include "stdafx.h"
#include "GlobalVars.h"


const GlobalVars& GlobalVars::operator=(const GlobalVars& srcVars)
{
	static GlobalVars x;
	x.g_timestampMode = srcVars.g_timestampMode;
	x.g_splitLine = srcVars.g_splitLine;
	x.g_lineDelim = srcVars.g_lineDelim;
	x.g_dropCallFilter = srcVars.g_dropCallFilter;
	x.g_doISDNdecode = srcVars.g_doISDNdecode;

	return x;
}

bool AFXAPI operator==(const GlobalVars& v1, const GlobalVars& v2)
{
	return (v1.g_decodeVersion == v2.g_decodeVersion) 
		&& (v1.g_doISDNdecode == v2.g_doISDNdecode)
		&& (v1.g_dropCallFilter == v2.g_dropCallFilter)
		&& (v1.g_lineDelim == v2.g_lineDelim)
		&& (v1.g_splitLine == v2.g_splitLine)
		&& (v1.g_timestampMode == v2.g_timestampMode);
}

bool AFXAPI operator!=(const GlobalVars& v1, const GlobalVars& v2)
{
	return !(v1==v2);
}