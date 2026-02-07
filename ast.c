#include "ast.h"
#include "c11util.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

struct ASTNode *ast_create(NodeType type, char *token)
{
	struct ASTNode *node = malloc(sizeof(struct ASTNode));
	node->type = type;
	node->token = token ? c11_strdup(token) : NULL;
	node->argc = 0;
	node->capacity = 2;
	node->args = malloc(sizeof(struct ASTNode *) * node->capacity);
	return node;
}

void ast_add_arg(struct ASTNode *parent, struct ASTNode *child)
{
	if (parent->argc >= parent->capacity) {
		parent->capacity *= 2;
		parent->args = realloc(parent->args,
			sizeof(struct ASTNode *) * parent->capacity);
	}
	parent->args[parent->argc++] = child;
}

void ast_free(struct ASTNode *node)
{
	if (!node)
		return;
	for (int i = 0; i < node->argc; i++) {
		ast_free(node->args[i]);
	}
	if (node->token)
		free(node->token);
	free(node->args);
	free(node);
}

/*************************************************/
void ast_print(struct ASTNode *node, int level)
{
	if (!node)
		return;

	for (int i = 0; i < level; i++)
		printf("  ");	// Indent

	char *type_name = "???";
	switch (node->type) {
	case NODE_ROOT:
		type_name = "ROOT";
		break;
	case NODE_INT:
		type_name = "INT";
		break;
	case NODE_STR:
		type_name = "STR";
		break;
	case NODE_ID:
		type_name = "ID";
		break;
	case NODE_EXPR:
		type_name = "EXPR";
		break;
	}

	if (node->type == NODE_ROOT)
		printf("\n");

	if (level > 0)
		printf("| ");

	printf("[%s] %s\n", type_name, node->token);

	for (int i = 0; i < node->argc; i++) {
		ast_print(node->args[i], level + 1);
	}
}
