#ifndef MMAGUTIL_H
#define MMAGUTIL_H

#include <stdint.h>

/* out_bounds_check(idx)- to check if an idx is out-of-bounds
 * return -1 if idx > bounds
 * (0 or lower capacity (invalid capacity size) will return -2)
 * nothing conditional was satisfied will return its current capacity
 */
int out_bounds_check(int idx);

/* mmag_expand(size) - expand memory capacity with size
 * return the number of capacity written, or -1 if error
 */
int mmag_expand(int size);

/* mmag_write(idx, c) - write c into memory idx
 * return -1 if fail, otherwise 0
 */
int mmag_write(int idx, uint8_t c);

/* mmag_get(idx) - get and return value of memory idx */
int mmag_get(int idx);


#endif /* MMAGUTIL_H */
