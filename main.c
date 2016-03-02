#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv) {
  while (true) {
    char line_buffer[513];  // 512 characters and '\0'
    if (fgets(line_buffer, 513, stdin) != NULL) {
      if (line_buffer[0] == 'q' && line_buffer[1] == '\n') {
        break;
      }
    }
    puts("?");
  }
  return 0;
}
