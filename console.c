#include "ppc.h"
#include "console.h"
#include "color.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

STATIC void _console_diag(const char *prefix, const char *fmt, va_list ap, int line)
{
	fprintf(stderr, "%s:", prefix);
	fprintf(stderr, " %d:", line);
	putc(' ', stderr);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
}

void console_err(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_console_diag("Error", fmt, ap, ppc_runtime.line);
}

void console_warn(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_console_diag("Warning", fmt, ap, ppc_runtime.line);
}

void console_errno(void)
{
	console_err("%s ", strerror(errno));
}
