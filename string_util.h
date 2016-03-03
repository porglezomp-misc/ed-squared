#ifndef _STRING_UTIL_H
#define _STRING_UTIL_H
#include <stdbool.h>

void strip_newline(char *out);
void strip(char *out);
void lstrip(char *out);
void rstrip(char *out);
bool get_command(char *out);

#endif
