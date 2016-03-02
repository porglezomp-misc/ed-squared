#include <stdio.h>
#include <stdbool.h>

/* precondition: out should be char[513] */
bool get_line(char *out) {
  return fgets(out, 513, stdin) != NULL;
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
