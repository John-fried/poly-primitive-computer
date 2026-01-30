#include "ppc.h"
#include "console.h"
#include "color.h"

#include <stdio.h>
#include <stdarg.h>

static void _console_diag(const char *prefix, const char *fmt, va_list ap, int line)
{
	fprintf(stderr, "%s%s: ", RED, prefix);
	if (line >= 0 && ppc_runtime.mode == MODE_CODE)
		fprintf(stderr, "%d: ", line);
	fprintf(stderr, "%s ", RESET);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
}

void console_err(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_console_diag("E", fmt, ap, ppc_context.line);
}

void console_warn(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_console_diag("W", fmt, ap, ppc_context.line);
}
