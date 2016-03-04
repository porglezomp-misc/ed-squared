#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdbool.h>

typedef struct line {
  struct line *prev, *next;
  char text[513];
} line;

typedef struct buffer {
  line *first_line, *last_line, *current_line;
  int line_number, line_count;
} buffer;

buffer *alloc_buffer();
void free_buffer(buffer *buf);
line *alloc_line();
void free_line(line *l);
line *append_line(line *base, line *new);

#endif
