#include "stdafx.h"

#include "StringTokenizer.h"

StringTokenizer::StringTokenizer( CString s )
{
	content = s;
	crt = s;
	token = "";
	delimiter=' ';
}

StringTokenizer::StringTokenizer( CString s, char delim )
{
	content = s;
	crt = s;
	token = "";
	delimiter=delim;
}

CString StringTokenizer::nextToken()
{
	token = "";
	int i=0;

	while (i<crt.GetLength() && crt.GetAt(i) != '\0' && crt.GetAt(i) != delimiter) {
		token += crt.GetAt(i);
		i++;
	}
	while (i<crt.GetLength() && crt.GetAt(i) != '\0' && crt.GetAt(i) == delimiter) 
		i++;
	crt = crt.Right(crt.GetLength()-i);
	return token;

}

