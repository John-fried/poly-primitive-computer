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

struct PPC_Runtime {
	int pointer; // the current pointer index
	MemorySlot *slots;
	RunMode mode;
	int slots_count;
	int slots_capacity; // max capacity before realloc
};

struct PPC_Ctx {
	int argc;
	char *argv[ARGSSIZE];
	struct PPC_Runtime *runtime;
};

extern struct PPC_Runtime ppc_runtime;

#endif /* PPC_H */
