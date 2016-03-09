// BitSet.cpp : implementation file
//

#include "stdafx.h"
#include "BitSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitSet


CBitSet::CBitSet()
{
	for (int j=0; j<buff_units; j++)
		buff[j]=0;
}

CBitSet::~CBitSet()
{
}


void CBitSet::setBit(WORD bitNo)
{
	int unit = (bitNo+1)/unit_size;
	DWORD bit = 1<<((bitNo+1)%unit_size);

	buff[unit]|=bit;
}


bool CBitSet::getBit(WORD bitNo)
{
	int unit = (bitNo+1)/unit_size;
	DWORD bit = 1<<((bitNo+1)%unit_size);

	return ((buff[unit]&bit) == bit);
}

