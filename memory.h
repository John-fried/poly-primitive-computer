#ifndef MMAGUTIL_H
#define MMAGUTIL_H

#include <stdint.h>

/* out_bounds_check(idx)- to check if an idx is out-of-bounds
 * return -1 if idx > bounds
 * (0 or lower capacity (invalid capacity size) will return -2)
 * nothing conditional was satisfied will return its current capacity
 */
int out_bounds_check(int idx);

/* mem_expand(size) - expand memory capacity with size
 * return the number of capacity written, or -1 if error
 */
int mem_expand(int size);

/* mem_write(idx, c) - write c into memory idx
 * return -1 if fail, otherwise 0
 */
int mem_write(int idx, uint8_t c);

/* mem_get(idx) - get and return value of memory idx */
int mem_get(int idx);


#endif /* MMAGUTIL_H */
