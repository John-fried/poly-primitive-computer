/* memory.c - Memory management utility for PPC */
#include "ppc.h"
#include "console.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* out_bounds_check(idx)- to check if an idx is out-of-bounds
 * return -1 if idx > bounds
 * (0 or lower capacity (invalid capacity size) will return -2)
 * nothing conditional was satisfied will return its current capacity
 */
int out_bounds_check(int idx)
{
	int capacity = ppc_runtime.memory_capacity;

	if (idx < 0 || idx >= capacity)
		return -1;
	if (capacity <= 0)
		return -2;

	return capacity;
}

/* mem_expand(size) - expand memory capacity with size
 * return the number of capacity written, or -1 if error
 */
int mem_expand(int size)
{
	if (size < 1) {
		console_err("Invalid size %d", size);
		return -1;
	}

	int capacity = ppc_runtime.memory_capacity;
	int add_capacity = capacity + size + 1;

	void *tmp = realloc(ppc_runtime.memory, add_capacity);
	if (unlikely(!tmp)) {
		console_errno();
		return -1;
	}

	ppc_runtime.memory = tmp;
	ppc_runtime.memory_capacity = add_capacity;
	return add_capacity;
}

/* mem_write(idx, c) - write c into memory idx
 * return -1 if fail, otherwise 0
 */
int mem_write(int idx, uint8_t c)
{
	int bounds = out_bounds_check(idx);

	if (bounds <= -2) {
		console_err("Invalid size %d", ppc_runtime.memory_capacity);
		return -1;
	}

	if (bounds < 0) {
		if (mem_expand(idx) == -1) {
			console_err("Invalid write %d", idx);
			return -1;
		}
	}

	ppc_runtime.memory[idx] = c;
	return 0;
}

/* mem_get(idx) - get and return value of memory idx */
int mem_get(int idx)
{
	int bounds = out_bounds_check(idx);

	if (bounds <= -2) {
		console_err("Invalid size %d", ppc_runtime.memory_capacity);
		return -1;
	}

	if (bounds < 0) {
		console_err("Invalid read %d", idx);
		return -1;
	}

	return ppc_runtime.memory[idx];
}
