#ifndef PPC_H
#define PPC_H

#define MEM_SIZE		65536
#define LINESIZE 		256
#define ARGSSIZE 		32

/*************************************************/
#define likely(x)     		__builtin_expect(!!(x), 1)
#define unlikely(x)    		__builtin_expect(!!(x), 0)

#ifndef ONE_SOURCE
# define ONE_SOURCE 1
#endif

#if ONE_SOURCE
#define ST_INLN static inline
#define ST_FUNC static
#define ST_DATA static
#else
#define ST_INLN
#define ST_FUNC
#define ST_DATA extern
#endif

#include <stdint.h>

struct PPC_Register {
	uint8_t			gpr[3];		/* general purpose register */
};

struct PPC_Runtime {
	uint16_t 		line;		/* line number for running process */
	struct PPC_Register 	registers;	/* register slots */
	uint32_t 		pointer; 	/* current memory pointer/stack pointer */
	uint8_t			memory[MEM_SIZE];/* the memory (0-255) */
};

struct PPC_State {
	unsigned int 		pipeline : 1;	/* (bool) on pipeline mode (example: from subevaluate) */
};

struct PPC_Ctx {
	uint8_t 		argc;		/* arguments count */
	char *			argv[ARGSSIZE]; /* arguments vector */
	struct PPC_Runtime *	runtime;	/* runtime link */
	struct PPC_State	state;		/* state dataa */
};

struct PPC_Reg {
	char			alias[16];	/* reg alias, example: sp */
	void *			setter;		/* setter, a value to be changed*/
};

typedef enum {
	VAL_STRING,
	VAL_INTEGRER
} ValueType;

typedef struct PPC_Value {
	ValueType		type;		/* Value type */
	char *			string;		/* If the value type is string */
	int 			value;		/* If the value type is integrer */
} PPC_Value;

/* Global state */
extern struct PPC_Runtime ppc_runtime;
extern struct PPC_Reg ppc_registers[];

/* utility to initialize an empty PPC_Ctx struct,
 * prevent from garbage data from a uininitialized struct
 */
void init_ctx(struct PPC_Ctx *ctx);

void ppc_init(void);
void ppc_halt(void) __attribute__((destructor));

/* utiltity to get register from an alias */
void *ppc_get_register(char *alias);

#endif /* PPC_H */
