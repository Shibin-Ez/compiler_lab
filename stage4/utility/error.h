#ifndef ERROR_H
#define ERROR_H

/**
 * Report a fatal error and exit the program.
 * Prints to stderr with "[Error] " prefix.
 *
 * @param fmt Format string (printf-style)
 * @param ... Variable arguments
 */
void report_error(const char *fmt, ...);

/**
 * Report a warning (does not exit).
 * Prints to stderr with "[Warning] " prefix.
 *
 * @param fmt Format string (printf-style)
 * @param ... Variable arguments
 */
void report_warning(const char *fmt, ...);

#endif
