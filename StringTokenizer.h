#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _STRINGTOKENIZER_H_
#define _STRINGTOKENIZER_H_


class StringTokenizer
{
public:
	StringTokenizer( CString s );
	StringTokenizer( CString s, char delim );
	CString nextToken();
private:
	CString content, crt;
	CString token;
	char	delimiter;
};

#endif
