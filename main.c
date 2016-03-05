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

void write_buffer(const buffer *buf, const char *name) {
  FILE *f = fopen(name, "w");
  line *l = buf->first_line;
  while (l) {
    fprintf(f, "%s", l->text);
    l = l->next;
  }
  printf("%ld\n", ftell(f));
  fclose(f);
}

int main(int argc, char **argv) {
  char line_buffer[513];  /* 512 characters and '\0' */
  buffer *buf = alloc_buffer();
  while (true) {
    if (get_command(line_buffer)) {
      if (line_buffer[0] == 'a' && line_buffer[1] == '\0') {
      while (true) {
        line *new_line = alloc_line();
        get_line(new_line->text);
        if (new_line->text[0] == '.' && new_line->text[1] == '\n' && new_line->text[2] == '\0') {
          free_line(new_line);
          break;
        }
        buffer_append_line(buf, new_line);
      }
      } else if (line_buffer[0] == 'q' && line_buffer[1] == '\0') {
        break;
      } else if (line_buffer[0] == 'w' && line_buffer[1] == '\0') {
        write_buffer(buf, "edsq-out");
      } else {
        puts("?");
      }
    }
  }
  return 0;
}
