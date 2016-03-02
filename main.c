#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

void strip_whitespace(char *out) {
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

bool get_command(char *out) {
  if (!get_line(out)) {
    return false;
  }
  strip_newline(out);
  strip_whitespace(out);
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
