#include "ppc.h"
#include "console.h"
#include "color.h"

#include <stdio.h>
#include <stdarg.h>

void console_err(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "%s?Error:", RED);
	if (ppc_runtime.mode == MODE_CODE)
		fprintf(stderr, "%d:", ppc_context.line);
	fprintf(stderr, "%s ", RESET);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
}

