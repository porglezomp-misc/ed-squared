#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  struct line *prev, *next;
  char text[513];
} line;

typedef struct {
  line *first_line, *last_line, *current_line;
  int line_number, line_count;
} document;

document *alloc_document() {
  return calloc(sizeof document, 1);
}

line *alloc_line() {
  return calloc(sizeof line, 1);
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

/* precondition: out should be char[513] */
bool get_line(char *out) {
  return fgets(out, 513, stdin) != NULL;
}

void strip_newline(char *out) {
  do {
    if (*out == '\n') {
      *out = '\0';
    }
  } while (*out++);
}

void strip(char *out) {
  char *scan = out;
  while (*scan == ' ' && *scan != '\0' && *scan != '\n') {
    scan++;
  }
  char *first = scan;
  char *last = scan;
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
  while (*scan == ' ') {
    scan++;
  }
  int distance = scan - out;
  int count = 513 - distance;
  memmove(out, scan, count);
}

void rstrip(char *out) {
  char *scan = out;
  char *last = out;
  while (*scan != '\0') {
    if (*scan != ' ' && *scan != '\n') {
      last = scan;
    }
    scan++;
  }
  *(last+1) = '\0';
}

bool get_command(char *out) {
  if (!get_line(out)) {
    return false;
  }
  strip_newline(out);
  lstrip(out);
  return true;
}

int main(int argc, char **argv) {
  char line_buffer[513];  /* 512 characters and '\0' */
  while (true) {
    if (get_command(line_buffer)) {
      if (line_buffer[0] == 'q' && line_buffer[1] == '\0') {
        break;
      }
    }
    puts("?");
  }
  return 0;
}
