#ifndef AST_H
#define AST_H

typedef enum {
    NODE_ROOT,      // Main Instruction (example: mov, print)
    NODE_INT,       // Digit: 10, 255
    NODE_STR,       // String: "hello", 'A'
    NODE_ID,        // Identifier/Register: gpr0, trans
    NODE_EXPR       // Nested expression: [trans A]
} NodeType;

struct ASTNode {
    NodeType type;
    char *token;
    struct ASTNode **args;   /* Array of pointers to children */
    int argc;
    int capacity;            /* array args capacity (for realloc) */
};

/* Prototypes */
struct ASTNode *ast_create(NodeType type, char *token);
void ast_add_arg(struct ASTNode *parent, struct ASTNode *child);
void ast_free(struct ASTNode *node);
void ast_print(struct ASTNode *node, int level); // for debug

#endif
