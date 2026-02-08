/* memory.c - Memory management utility for PPC */
#include "ppc.h"
#include "console.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* mem_write(idx, c) - write c into memory idx
 * return -1 if fail, otherwise 0
 */
int mem_write(int idx, uint8_t c)
{
	if (idx >= MEM_SIZE) {
		console_err("write to unitialized storage %d", idx);
		return -1;
	}
	ppc_runtime.memory[idx] = c;
	return 0;
}

/* mem_get(idx) - get and return value of memory idx */
int mem_get(int idx)
{
	return ppc_runtime.memory[idx];
}
