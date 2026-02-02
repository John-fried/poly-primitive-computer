#ifndef PPC_H
#define PPC_H

#define LINESIZE 		256
#define ARGSSIZE 		64
#define INITIAL_CODESIZE 	8

#define likely(x)     		__builtin_expect(!!(x), 1)
#define unlikely(x)    		__builtin_expect(!!(x), 0)

#include <stdint.h>

typedef enum {
	MODE_DIRECT,
	MODE_CODE
} RunMode;

typedef struct {
	uint8_t 		data;
} MemorySlot;

struct PPC_Code {
	char **			code;
	uint16_t 		max_line;
	uint16_t 		size;
};

struct PPC_Runtime {
	uint16_t 		pointer;
	MemorySlot *		slots;
	uint16_t 		slots_capacity;

	struct 			PPC_Code code;
	RunMode 		mode;
};

struct PPC_Ctx {
	uint16_t 		line;
	uint8_t 		argc;
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
