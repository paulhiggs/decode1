#ifndef __TYPES_H__
#define __TYPES_H__


typedef struct {
	char	*ver;
	int		nVer;
	char **Signals;
	char **States;
	char **Events;
} WSInfoElements;


typedef unsigned int  PortType;

#endif