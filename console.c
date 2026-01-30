#include "ppc.h"
#include "console.h"
#include "color.h"

#include <stdio.h>
#include <stdarg.h>

static void _console_diag(const char *prefix, const char *fmt, va_list ap, int line)
{
	fprintf(stderr, "%s: ", prefix);
	if (line >= 0 && ppc_runtime.mode == MODE_CODE)
		fprintf(stderr, "%d: ", line);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
}

void console_err(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_console_diag(RED"E"RESET, fmt, ap, ppc_context.line);
}

void console_warn(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_console_diag(YELLOW"W"RESET, fmt, ap, ppc_context.line);
}
