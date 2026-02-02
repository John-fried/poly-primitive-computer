/* mmagutil.c - Memory management utility for PPC */
#include "ppc.h"
#include "console.h"

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
	int capacity = ppc_runtime.slots_capacity;

	if (idx > capacity)
		return -1;
	if (capacity <= 0)
		return -2;

	return capacity;
}

/* mmag_expand(size) - expand memory capacity with size
 * return the number of capacity written, or -1 if error
 */
int mmag_expand(int size)
{
	if (size < 1) {
		console_err("Invalid size %d", size);
		return -1;
	}

	int capacity = ppc_runtime.slots_capacity;
	int add_capacity = capacity + size + 1;
	int new_capacity = add_capacity * sizeof(MemorySlot);

	void *tmp = realloc(ppc_runtime.slots, new_capacity);
	if (!tmp) {
		console_errno();
		return -1;
	}

	ppc_runtime.slots = tmp;
	ppc_runtime.slots_capacity = new_capacity;
	return new_capacity;
}

/* mmag_write(idx, c) - write c into memory idx
 * return -1 if fail, otherwise 0
 */
int mmag_write(int idx, uint8_t c)
{
	int bounds = out_bounds_check(idx);

	if (bounds <= -2) {
		console_err("Invalid size %d", ppc_runtime.slots_capacity);
		return -1;
	}

	if (bounds < 0) {
		console_err("Invalid write to %d", idx);
		return -1;
	}

	ppc_runtime.slots[idx].data = c;
	return 0;
}

/* mmag_get(idx) - get and return value of memory idx */
int mmag_get(int idx)
{
	int bounds = out_bounds_check(idx);

	if (bounds <= -2) {
		console_err("Invalid size %d", ppc_runtime.slots_capacity);
		return -1;
	}

	if (bounds < 0) {
		console_err("Invalid read to %d", idx);
		return -1;
	}

	return ppc_runtime.slots[idx].data;
}
