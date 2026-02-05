#include "ppc.h"
#include "console.h"
#include "eval.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	ppc_init();
	FILE *fp;
	size_t len = 0;
	char *line = NULL;

	if (argc == 1) {
		console_err("No input files");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (!fp) {
		console_errno();
		return 1;
	}

	struct PPC_Ctx ctx;
	init_ctx(&ctx);

	while ((getline(&line, &len, fp)) != -1) {
		ppc_runtime.line++;
		parse_line(line, &ctx);
		eval(&ctx);
	}
	fclose(fp);
	free(line);
	return 0;
}
