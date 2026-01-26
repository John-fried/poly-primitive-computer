#include "console.h"
#include "color.h"

#include <stdio.h>
#include <stdarg.h>

void console_err(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "%s?Error%s: ", RED, RESET);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
}

