#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void merge_array(char **arr, int n, char *buf)
{
        char *ptr = buf;

        for (int i = 0; i < n; i++) {
                strcpy(ptr, arr[i]);
                ptr += strlen(ptr);
                if (i < n - 1) strcpy(ptr++, " ");
        }
}

static void _readtoken(char *line, struct PPC_Ctx *ctx)
{
        int i = 0;
        ctx->argc = 0;
        char *token;

        while ((token = strsep(&line, PARSER_TOK_DELIM)) != NULL && i < ARGSSIZE) {
                if (*token == '\0') continue;

                ctx->argv[i++] = token;
                ctx->argc++;
        }
}

char *remove_comment(char *line)
{
        char *found;

        if ((found = strstr(line, PARSER_TOK_COMMENT)))
                *found = 0;

        return line;
}

void parse_line(char *line, struct PPC_Ctx *ctx)
{
        if (ctx->full_string != NULL) {
                free(ctx->full_string);
                ctx->full_string = NULL;
        }

        ctx->full_string = strdup(line);
        _readtoken(line, ctx);
}

void find_range(const char *str, int *min, int *max)
{
        char *result;

        if ((result = strstr(str, ".."))) {
                int str_len = strlen(str);
                int result_len = strlen(result);
                char *strtemp = strdup(str);
                strtemp[str_len - (result_len)] = 0; /* "n1\0.n2" */

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

        /* default value */
        *min = 0;
        *max = 1;
}

int hasdigit(const char *str)
{
        while (*str)
                if (!isdigit(*str++)) return 0;

        return 1;
}
