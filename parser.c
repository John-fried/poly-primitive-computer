#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
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

void find_range(const char *str, int *min, int *max)
{
        char *result;

        if ((result = strstr(str, ".."))) {
                int str_len = strlen(str);
                int result_len = strlen(result);
                char *strtemp = strdup(str);
                strtemp[str_len - (result_len)] = 0; // n1\0.n2

                int n1 = atoi(strtemp);
                free(strtemp);

                int n2 = atoi(str + (str_len - (result_len - 2)));

                if (n1 > n2) {
                        *min = n2;
                        *max = n1;
                        return;
                }

                *min = n1;
                *max = n2;
                return;
        }

        // default to 1
        *min = 0;
        *max = 1;
}
