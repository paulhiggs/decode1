#include "StdAfx.h"
#include "PString.h"

PString::PString( CString i ) : CString(i)
{
}


bool PString::startsWith( CString s )
{
	return ( this->Left( s.GetLength()) == s );
}


bool PString::endsWith( CString e ) 
{
	return ( this->Right( e.GetLength()) == e );
}

/*
void PString::PrepHTML(void)
{
	this->Replace(_T("<"),_T("&lt;"));
	this->Replace(_T(">"),_T("&gt;"));
}
*/