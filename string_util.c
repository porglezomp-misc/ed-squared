#include "string_util.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* precondition: out should be char[513] */
void strip_newline(char *out) {
  do {
    if (*out == '\n') {
      *out = '\0';
    }
  } while (*out++);
}

void strip(char *out) {
  char *scan = out;
  while (*scan == ' ' || *scan == '\t' || *scan == '\n') scan++;
  char *first = scan;
  char *last = scan - 1;
  while (*scan != '\0') {
    if (*scan != ' ' && *scan != '\n') {
      last = scan;
    }
    scan++;
  }
  int count = last - first + 1;
  memmove(out, first, count);
  out[count] = '\0';
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
    if (*scan != ' ' && *scan != '\n') {
      last = scan;
    }
    scan++;
  }
  *(last+1) = '\0';
}
