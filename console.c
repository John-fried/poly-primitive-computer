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
	if (line >= 0 && ppc_runtime.mode == MODE_CODE)
		fprintf(stderr, "%d:", line);
	putc(' ', stderr);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
}

void console_err(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_console_diag(RED "Err" RESET, fmt, ap, ppc_runtime.line);
}

void console_warn(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_console_diag(YELLOW "Warn" RESET, fmt, ap, ppc_runtime.line);
}

void console_errno(void)
{
	console_err("%s (code: %d)", strerror(errno), errno);
}
