/* mmagutil.c - Memory management utility for PPC */
#include "ppc.h"
#include "console.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* _out_bounds_check - throw -1 if the input idx was so big
 *(0 or lower capacity will return -3)
 * nothing conditional was satisfied will return its current capacity
 */
static int _out_bounds_check(int idx)
{
	int capacity = ppc_runtime.slots_capacity;
	if (idx > capacity)
		return -1;
	if (capacity <= 0)
		return -3;
	return capacity;
}

/* mmag_expand(size) - expand memory capacity with size
 * return the number of capacity written, or -1 if error
 */
int mmag_expand(int size)
{
	if (size < 1) {
		console_err("Expanding with %d", size);
		return -1;
	}

	int capacity = ppc_runtime.slots_capacity;
	int new_capacity = capacity + size * sizeof(MemorySlot);

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
int mmag_write(int idx, int c)
{
	int bounds = _out_bounds_check(idx);

	if (bounds <= -3) {
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
	return ppc_runtime.slots[idx].data;
}
