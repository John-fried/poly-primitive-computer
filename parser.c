#include "ppc.h"
#include "parser.h"
#include "eval.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void merge_array(char **arr, int n, char *buf)
{
	char *ptr = buf;

	for (int i = 0; i < n; i++) {
		memcpy(ptr, arr[i], strlen(arr[i]));
		ptr += strlen(ptr);
		if (i < n - 1)
			memcpy(ptr++, " ", 1);
	}
}

void slice_string(char *line, struct PPC_Ctx *ctx)
{
	int i = 0;
	ctx->argc = 0;
	char *token;

	while ((token = strsep(&line, PARSER_TOK_DELIM)) != NULL && i < ARGSSIZE) {
		if (*token == '\0')
			continue;

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
	slice_string(line, ctx);
}

void find_range(const char *str, int *min, int *max)
{
	char *result;

	if ((result = strstr(str, ".."))) {
		int str_len = strlen(str);
		int result_len = strlen(result);
		char *strtemp = strdup(str);
		strtemp[str_len - (result_len)] = 0;	/* "n1\0.n2" */

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
		if (!isdigit(*str++))
			return 0;

	return 1;
}

/* Preprocessing input handler logic*/

/* stitch_string - utility to stitch orig string from open/close tag into replacement
 * example:
 *      tag: "[", "]"
 *      orig: "mov 0, [trans A]",
 *      replacement: "65",
 *      final: "mov 0, 65"
 */
STATIC char *stitch_string(char *orig, const char *open_tag, const char *close_tag, const char *replacement)
{
	int prefix_len = open_tag - orig;
	int middle_len = strlen(replacement);
	int suffix_len = strlen(close_tag + 1);

	char *new_string = malloc(prefix_len + middle_len + suffix_len + 1);
	if (!new_string)
		return orig;

	/* stitching process */
	memcpy(new_string, orig, prefix_len);	/* prefix (example 'mov 0, ')
						 * memcpy take len as a character count,
						 * not index, so it will only take to 'mov 0, ' (7 characters),
						 * not 'mov 0, [' (7 index)
						 */
	memcpy(new_string + prefix_len, replacement, middle_len);	/* replacement */
	memcpy(new_string + prefix_len + middle_len, close_tag + 1, suffix_len);	/* after close tag */

	return new_string;
}

/* process_subevaluate(line) - utility to process subevaluate instruction
 * from a string line, and return the final result
 */
STATIC void process_subevaluate(char *line)
{
	char *open, *close;

	while ((open = strstr(line, PARSER_TOK_SUBEVAL_OPEN)) && (close = strstr(open, PARSER_TOK_SUBEVAL_CLOSE))) {
		size_t inner_len = close - (open + 1);
		char *inner_cmd = strndup(open + 1, inner_len);

		/* initialize context */
		struct PPC_Ctx sub_ctx;
		init_ctx(&sub_ctx);
		parse_line(inner_cmd, &sub_ctx);
		sub_ctx.state.pipeline = 1;	/* mark as a pipeline for subevaluate */

		/* evaluate */
		PPC_Value res = eval(&sub_ctx);

		/* handle result value */
		char res_buffer[32];
		char *final_replacement;

		if (res.type == VAL_INTEGRER) {
			sprintf(res_buffer, "%d", res.value);
			final_replacement = res_buffer;
		} else
			final_replacement = res.string;

		/* slitch string - replace subeval to result */
		char *temp_line = stitch_string(line, open, close, final_replacement);
		strcpy(line, temp_line);

		/* cleanup */
		free(inner_cmd);
		free(temp_line);
	}
}

void preprocess_line(char *line, struct PPC_Ctx *ctx)
{
	/* preprocessing */
	line = remove_comment(line);
	process_subevaluate(line);

	/* final parse */
	parse_line(line, ctx);
}
