#ifndef PPC_H
#define PPC_H

#define LINESIZE 		256
#define ARGSSIZE 		32
#define INITIAL_SLOTSIZE 	8
#define INITIAL_CODESIZE 	8

#define likely(x)     		__builtin_expect(!!(x), 1)
#define unlikely(x)    		__builtin_expect(!!(x), 0)

#define STATIC 			static

#include <stdint.h>

typedef enum {
	MODE_DIRECT,				/* on normal input mode*/
	MODE_CODE				/* on running code*/
} RunMode;

typedef struct {
	uint8_t 		data;		/* integrer data 0-255 */
} MemorySlot;

struct PPC_Code {
	char **			code;		/* code slots */
	uint32_t 		max_line;	/* code max_line */
	uint32_t 		size;		/* code available size */
};

struct PPC_Runtime {
	uint16_t 		line;		/* line number for running process */
	uint8_t			gpr[3];		/* general purpose register */
	uint32_t 		pointer; 	/* current memory pointer/stack pointer */
	MemorySlot *		slots;		/* the memory slots */
	uint32_t 		slots_capacity;	/* memory slots capacity */

	struct 			PPC_Code code;	/* code data */
	RunMode 		mode;		/* running mode: code || direct*/
};

struct PPC_State {
	unsigned int 		pipeline : 1;	/* (bool) on pipeline mode (example: from subevaluate) */
};

struct PPC_Ctx {
	uint8_t 		argc;		/* arguments count */
	char *			argv[ARGSSIZE]; /* arguments vector */
	char *			full_string;	/* original input */
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

/* Utility to free context, avoiding the memory leak */
void free_ctx(struct PPC_Ctx *ctx);

void ppc_init(void);
void ppc_loop(void);
void ppc_exit(void) __attribute__((destructor));

/* utiltity to get register from an alias */
void *ppc_get_register(char *alias);

#endif /* PPC_H */
