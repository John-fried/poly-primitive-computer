/* c11util -- some utility in the standard library that doesn't support c11 implemented explicityly */

#include "c11util.h"
#include <stdlib.h>
#include <string.h>

char *c11_strdup(char *s)
{
	int len = strlen(s);
	char *dst = malloc(len + 1);
	if (dst != NULL)
		memcpy(dst, s, len);
	return dst;
}
