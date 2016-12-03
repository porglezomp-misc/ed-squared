#include "string_util.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void strip_newline(char *out) {
  do {
    if (*out == '\n') {
      *out = '\0';
    }
  } while (*out++);
}

void strip(char *out) {
  // We rstrip first so that lstrip doesn't have to memmove as much
  rstrip(out);
  lstrip(out);
}

void lstrip(char *out) {
  char *scan = out;
  while (*scan == ' ' || *scan == '\t' || *scan == '\n') scan++;
  char *first = scan;
  while (*scan != '\0') scan++;
  memmove(out, first, scan - first + 1);
}

void rstrip(char *out) {
  char *scan = out;
  char *last = out - 1;
  while (*scan != '\0') {
    if (*scan != ' ' && *scan != '\t' && *scan != '\n') {
      last = scan;
    }
    scan++;
  }
  *(last+1) = '\0';
}
