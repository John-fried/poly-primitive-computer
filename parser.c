#include "parser.h"

#include <stdio.h>
#include <string.h>

void readtoken(char *line, struct PPC_Ctx *ctx)
{
	int i = 0;
	ctx->argc = 0;
	char *token;

	while ((token = strsep(&line, " \n\t\r")) != NULL && i < ARGSSIZE) {
		if (*token == '\0') continue;

		ctx->argv[i++] = token;
		ctx->argc++;
	}
}


