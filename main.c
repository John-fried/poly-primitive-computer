#include "ppc.h"
#include "console.h"
#include "eval.h"
#define PARSER_DEBUG
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	ppc_init();
	FILE *fp;
	size_t len = 0;
	int i = 1;
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
		ppc_runtime.line = i++;
		struct ASTNode *node = parser_parse_line(line);
		if (node) {
			eval_ast(node);
			ast_free(node);
		}
	}
	fclose(fp);
	free(line);
	return 0;
}
