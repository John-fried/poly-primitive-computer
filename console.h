#ifndef CONSOLE_H
#define CONSOLE_H

void console_err(const char *fmt, ...);
void console_warn(const char *fmt, ...);

/* console_errno - directly print error with str errno */
void console_errno(void);

#endif /* CONSOLE_H */
