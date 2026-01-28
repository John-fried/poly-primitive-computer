#ifndef PPC_H
#define PPC_H

#define LINESIZE 256
#define ARGSSIZE 64

typedef enum {
	MODE_DIRECT,
	MODE_CODE
} RunMode;

typedef struct {
	int data;
} MemorySlot;

struct PPC_Code {
	char **code;
	int max_line;
};

struct PPC_Runtime {
	int pointer; // the current pointer index
	MemorySlot *slots;
	int slots_capacity;

	//code - 10 ..., stores the code & the run mode DIRECT & CODE
	struct PPC_Code code;
	RunMode mode;
};

struct PPC_Ctx {
	int line;
	int argc;
	char *argv[ARGSSIZE];
	struct PPC_Runtime *runtime;
};

extern struct PPC_Runtime ppc_runtime; // global runtime context
extern struct PPC_Ctx ppc_context; // global context

//fn
void init_ctx(struct PPC_Ctx *ctx);
void interpret(struct PPC_Ctx *ctx);

#endif /* PPC_H */
