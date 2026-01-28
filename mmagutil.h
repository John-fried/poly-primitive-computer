#ifndef MMAGUTIL_H
#define MMAGUTIL_H

/* mmag_expand(size) - expand memory capacity with size
 * return the number of capacity written, or -1 if error
 */
int mmag_expand(int size);

/* mmag_write(idx, c) - write c into memory idx
 * return -1 if fail, otherwise 0
 */
int mmag_write(int idx, int c);

/* mmag_get(idx) - get and return value of memory idx */
int mmag_get(int idx);


#endif /* MMAGUTIL_H */
