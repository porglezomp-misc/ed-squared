#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

buffer *read_buffer(buffer *buf, const char *name) {
  FILE *f = fopen(name, "r");
  if (!f) return NULL;
  if (!buf) buf = alloc_buffer();
  while (!feof(f)) {
    line *l = alloc_line();
    fgets(l->text, 513, f);
    buffer_append_line(buf, l);
  }
  printf("%ld\n", ftell(f));
  fclose(f);
  return buf;
}

char filename[256];
void replace_buffer(buffer **buf, const char *name) {
  buffer *newbuf = read_buffer(NULL, filename);
  if (newbuf) {
    free_buffer(*buf);
    *buf = newbuf;
  } else {
    puts("?");
  }
}

void append_text(buffer *buf) {
  while (true) {
    line *new_line = alloc_line();
    get_line(new_line->text);
    if (new_line->text[0] == '.' && new_line->text[1] == '\n' && new_line->text[2] == '\0') {
      free_line(new_line);
      break;
    }
    buffer_append_line(buf, new_line);
  }
}

void print_line(buffer *buf) {
  if (buf->current_line) fputs(buf->current_line->text, stdout);
  else puts("?");
}

line *navigate(buffer *buf, const char *command) {
  int start_line = -1;
  if (isdigit(*command)) {
    int count;
    sscanf(command, "%d%n", &start_line, &count);
    command += count;
    buffer_goto_line(buf, start_line);
  }
  int motion = 0;
  while (*command == '-' || *command == '+' || *command == ' ') {
    char c = *command;
    command++;
    if (isdigit(*command)) {
      int offset, n_consumed;
      sscanf(command, "%d%n", &offset, &n_consumed);
      if (c == '+' || c == ' ') motion += offset;
      else if (c == '-') motion -= offset;
      command += n_consumed;
    } else {
      if (c == '+') motion++;
      else if (c == '-') motion--;
    }
  }
  line *new_line;
  if (start_line == -1) new_line = buffer_goto_line_relative(buf, motion);
  else new_line = buffer_goto_line(buf, start_line + motion);
  return new_line;
}

int main(int argc, char **argv) {
  char line_buffer[513];  /* 512 characters and '\0' */
  buffer *buf = alloc_buffer();
  while (true) {
    if (get_command(line_buffer)) {
      if (line_buffer[0] == 'a' && line_buffer[1] == '\0') {
        append_text(buf);
      } else if (line_buffer[0] == 'q' && line_buffer[1] == '\0') {
        break;
      } else if (line_buffer[0] == 'w' && line_buffer[1] == '\0') {
        if (filename[0] != '\0') write_buffer(buf, filename);
        else puts("?");
      } else if (line_buffer[0] == 'w' && line_buffer[1] == ' ' && line_buffer[2] != '\0') {
        strncpy(filename, line_buffer+2, 255);
        write_buffer(buf, filename);
      } else if (line_buffer[0] == 'r' && line_buffer[1] == '\0') {
        if (!read_buffer(buf, filename)) puts("?");
      } else if (line_buffer[0] == 'r' && line_buffer[1] == ' ' && line_buffer[2] != '\0') {
        strncpy(filename, line_buffer+2, 255);
        if (!read_buffer(buf, filename)) puts("?");
      } else if (line_buffer[0] == 'e' && line_buffer[1] == '\0') {
        replace_buffer(&buf, filename);
      } else if (line_buffer[0] == 'e' && line_buffer[1] == ' ' && line_buffer[2] != '\0') {
        strncpy(filename, line_buffer+2, 255);
        replace_buffer(&buf, filename);
      } else if (line_buffer[0] == 'p' && line_buffer[1] == '\0') {
        print_line(buf);
      } else if (line_buffer[0] == '-' || line_buffer[0] == '+' || isdigit(line_buffer[0])) {
        if (!navigate(buf, line_buffer)) puts("?");
        else print_line(buf);
      } else {
        puts("?");
      }
    }
  }
  return 0;
}
