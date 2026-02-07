#ifndef PPC_CONSOLE_H
#define PPC_CONSOLE_H

void console_err(const char *fmt, ...);
void console_warn(const char *fmt, ...);

/* console_errno - directly print last errno with strerrno */
void console_errno(void);

#endif /* PPC_CONSOLE_H */
