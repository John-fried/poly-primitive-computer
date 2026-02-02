#ifndef PPC_H
#define PPC_H

#define LINESIZE 		256
#define ARGSSIZE 		64
#define INITIAL_CODESIZE 	8

#define likely(x)     		__builtin_expect(!!(x), 1)
#define unlikely(x)    		__builtin_expect(!!(x), 0)

typedef enum {
	MODE_DIRECT,
	MODE_CODE
} RunMode;

typedef struct {
	int 			data;
} MemorySlot;

struct PPC_Code {
	char **			code;
	int 			max_line;
	int 			size;
};

struct PPC_Runtime {
	int 			pointer;
	MemorySlot *		slots;
	int 			slots_capacity;

	struct 			PPC_Code code;
	RunMode 		mode;
};

struct PPC_Ctx {
	int 			line;
	int 			argc;
	char *			argv[ARGSSIZE];
	char *			full_string;
	struct PPC_Runtime *	runtime;
};

extern struct PPC_Runtime ppc_runtime; // global runtime context
extern struct PPC_Ctx ppc_context; // global context


/* utility to initialize an empty PPC_Ctx struct,
 * prevent from garbage data from a uininitialized struct
 */
void init_ctx(struct PPC_Ctx *ctx);

/* Utility to free context, avoiding the memory leak */
void free_ctx(struct PPC_Ctx *ctx);

/* Utility to execute instruction from context */
void interpret(struct PPC_Ctx *ctx);

#endif /* PPC_H */
