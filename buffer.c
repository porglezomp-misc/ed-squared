#include "buffer.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "string_util.h"

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

line *buffer_goto_line(buffer *buf, int n) {
  if (n <= 0) return NULL;
  line *l = buf->first_line;
  while (--n > 0) {
    if (l == NULL) return NULL;
    l = l->next;
  }
  if (l != NULL) buf->current_line = l;
  return l;
}

line *buffer_goto_line_relative(buffer *buf, int n) {
  line *l = buf->current_line;
  while (n < 0) {
    if (l == NULL) return NULL;
    l = l->prev;
    n++;
  }
  while (n > 0) {
    if (l == NULL) return NULL;
    l = l->next;
    n--;
  }
  if (l != NULL) buf->current_line = l;
  return l;
}


int buffer_get_line_number(buffer *buf) {
  line *scan = buf->first_line;
  int lineno = 1;
  while (scan != buf->current_line) {
    scan = scan->next;
    lineno++;
  }
  return lineno;
}
