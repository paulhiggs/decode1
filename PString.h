#ifndef __PSTRING_H__
#define __PSTRING_H__

class PString : public CString 
{
public:
	PString( CString i );
	bool startsWith( CString s );
	bool endsWith( CString e );
//	void PrepHTML(void);
};
#endif