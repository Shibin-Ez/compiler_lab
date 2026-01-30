#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void report_error(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "[Error] ");
  vfprintf(stderr, fmt, args);
  va_end(args);
  exit(1);
}

void report_warning(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "[Warning] ");
  vfprintf(stderr, fmt, args);
  va_end(args);
}
