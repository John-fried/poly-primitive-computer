#ifndef PPC_H
#define PPC_H

#define LINESIZE 		256
#define ARGSSIZE 		64
#define INITIAL_CODESIZE 	8

#define likely(x)     		__builtin_expect(!!(x), 1)
#define unlikely(x)    		__builtin_expect(!!(x), 0)

#define STATIC 			static

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
	uint32_t 		max_line;
	uint32_t 		size;
};

struct PPC_Runtime {
	uint8_t			gpr[3];	/* general purpose register */
	uint32_t 		pointer;
	MemorySlot *		slots;
	uint32_t 		slots_capacity;

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

struct PPC_Reg {
	char			alias[16];
	void *			setter;
};

typedef enum {
	VAL_STRING,
	VAL_INTEGRER
} ValueType;

typedef struct PPC_Value {
	ValueType		type;
	char *			string;
	int 			value;
} PPC_Value;

#define VAL_ERROR 		(PPC_Value){VAL_INTEGRER, "", 1}
#define VAL_SUCCESS 		(PPC_Value){VAL_INTEGRER, "", 0}
#define VAL_STR(x)		(PPC_Value){VAL_STRING, #x, 0}
#define VAL_INT(x)		(PPC_Value){VAL_INTEGRER, "", x}

/* Global struct */
extern struct PPC_Runtime ppc_runtime;
extern struct PPC_Ctx ppc_context;
extern struct PPC_Reg ppc_registers[];

/* utility to initialize an empty PPC_Ctx struct,
 * prevent from garbage data from a uininitialized struct
 */
void init_ctx(struct PPC_Ctx *ctx);

/* Utility to free context, avoiding the memory leak */
void free_ctx(struct PPC_Ctx *ctx);

void ppc_init(void);
void ppc_loop(void);
void ppc_exit(void);

void *ppc_get_register(char *alias);

#endif /* PPC_H */
