#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "string_util.h"
#include "buffer.h"

/* precondition: out should be char[513] */
bool get_line(char *out) {
  return fgets(out, 513, stdin) != NULL;
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
