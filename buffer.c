#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "string_util.h"

typedef struct line {
  struct line *prev, *next;
  char text[513];
} line;

typedef struct buffer {
  line *first_line, *last_line, *current_line;
  int line_number, line_count;
} buffer;

buffer *alloc_buffer() {
  return calloc(sizeof(buffer), 1);
}

void free_buffer(buffer *buf) {
  free(buf);
}

line *alloc_line() {
  return calloc(sizeof(line), 1);
}

void free_line(line *l) {
  free(l);
}

line *append_line(line *base, line *new) {
  if (base == NULL) {
    return new;
  } else {
    if (base->next != NULL) {
      base->next->prev = new;
      new->next = base->next;
    }
    base->next = new;
    new->prev = base;
    return base;
  }
}

#endif
