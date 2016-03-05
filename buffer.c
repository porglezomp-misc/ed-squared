#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

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

line *line_append_line(line *base, line *new) {
  if (base == NULL) {
    return new;
  } else {
    if (base->next != NULL) {
      base->next->prev = new;
      new->next = base->next;
    }
    base->next = new;
    new->prev = base;
    return new;
  }
}

void buffer_append_line(buffer *buf, line *new) {
  if (buf->first_line == NULL) {
    assert(buf->last_line == NULL);
    buf->first_line = buf->last_line = new;
  }
  line_append_line(buf->current_line, new);
  if (buf->current_line == buf->last_line) {
    buf->last_line = new;
  }
  buf->current_line = new;
}

bool buffer_advance_line(buffer *buf) {
  if (buf->current_line && buf->current_line->next) {
    buf->current_line = buf->current_line->next;
    return true;
  }
  return false;
}

bool buffer_retreat_line(buffer *buf) {
  if (buf->current_line && buf->current_line->prev) {
    buf->current_line = buf->current_line->prev;
    return true;
  }
  return false;
}
