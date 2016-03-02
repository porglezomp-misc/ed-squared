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
  while (*scan == ' ' && *scan != '\0') {
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

int main(int argc, char **argv) {
  while (true) {
    char line_buffer[513];  // 512 characters and '\0'
    if (get_line(line_buffer)) {
      if (line_buffer[0] == 'q' && line_buffer[1] == '\n') {
        break;
      }
    }
    puts("?");
  }
  return 0;
}
