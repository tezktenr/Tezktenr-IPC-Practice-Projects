#include "ipc.h"

char* getMsgAtIndex(int n, char* buf)
{
	if (n >= maxMsg)
		return 0;
	else
		return buf+n*msgSize;
}


