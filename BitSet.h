#if !defined(AFX_BITSET_H__3877FF16_A84B_42C3_8C70_7FBC1E66BAFB__INCLUDED_)
#define AFX_BITSET_H__3877FF16_A84B_42C3_8C70_7FBC1E66BAFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitSet view

class CBitSet : public CObject
{
public:
	CBitSet();           // protected constructor used by dynamic creation


// Operations
public:
	void setBit(WORD bitNo);
	bool getBit(WORD bitNo);

private:
	#define buff_units 8
	#define unit_size 32
	DWORD buff[buff_units];
// Implementation

public:
	virtual ~CBitSet();
	// Generated message map functions
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITSET_H__3877FF16_A84B_42C3_8C70_7FBC1E66BAFB__INCLUDED_)
