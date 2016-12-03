#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "midunit.h"
#include "string_util.h"
#include "buffer.h"

#define STACK_STR(NAME, LITERAL) const char _literal[] = LITERAL;\
  char NAME[sizeof _literal];\
  strcpy(NAME, _literal);

static char *test_strip() {
  STACK_STR(text, "  here's a string  ");
  strip(text);
  mu_assert_eq_str("strip strings correctly", text, "here's a string");
  return 0;
}

static char *test_strip_nl() {
  STACK_STR(text, "  remove a newline  \n");
  strip(text);
  mu_assert_eq_str("remove a newline in strip()", text, "remove a newline");
  return 0;
}

static char *test_strip_empty() {
  STACK_STR(text, "");
  strip(text);
  mu_assert_eq_str("strip empty string should be empty", text, "");
  return 0;
}

static char *test_strip_only_nl() {
  STACK_STR(text, "\n");
  strip(text);
  mu_assert_eq_str("strip newline should be empty", text, "");
  return 0;
}

static char *test_strip_tabs() {
  STACK_STR(text, "	indent	\n");
  strip(text);
  mu_assert_eq_str("strip tabs", text, "indent");
  return 0;
}

static char *test_lstrip() {
  STACK_STR(text, "  here's a string  ");
  lstrip(text);
  mu_assert_eq_str("strip left correctly", text, "here's a string  ");
  return 0;
}

static char *test_lstrip_empty() {
  STACK_STR(text, "");
  lstrip(text);
  mu_assert_eq_str("lstrip empty string should be empty", text, "");
  return 0;
}

static char *test_lstrip_only_nl() {
  STACK_STR(text, "\n");
  lstrip(text);
  mu_assert_eq_str("lstrip newline should be empty", text, "");
  return 0;
}

static char *test_lstrip_tabs() {
  STACK_STR(text, "	indent	\n");
  lstrip(text);
  mu_assert_eq_str("lstrip tabs", text, "indent	\n");
  return 0;
}

static char *test_rstrip() {
  STACK_STR(text, "  here's a string  ");
  rstrip(text);
  mu_assert_eq_str("strip right correctly", text, "  here's a string");
  return 0;
}

static char *test_rstrip_nl() {
  STACK_STR(text, "remove a newline\n");
  rstrip(text);
  mu_assert_eq_str("remove a newline", text, "remove a newline");
  return 0;
}

static char *test_rstrip_empty() {
  STACK_STR(text, "");
  strip(text);
  mu_assert_eq_str("rstrip empty string should be empty", text, "");
  return 0;
}

static char *test_rstrip_only_nl() {
  STACK_STR(text, "\n");
  rstrip(text);
  mu_assert_eq_str("rstrip newline should be empty", text, "");
  return 0;
}

static char *test_rstrip_tabs() {
  STACK_STR(text, "	indent	\n");
  rstrip(text);
  mu_assert_eq_str("rstrip tabs", text, "	indent");
  return 0;
}

static char *test_line_append() {
  line *l1 = alloc_line();
  line *l2 = alloc_line();
  mu_assert("next line starts out null", l1->next == NULL);
  mu_assert("previous line starts out null", l2->prev == NULL);
  line *l = line_append_line(l1, l2);
  mu_assert("the new last line should be returned", l2 == l);
  mu_assert("the second line should be next after the first", l1->next == l2);
  mu_assert("the first line should be prev to the second", l2->prev == l1);
  free_line(l1);
  free_line(l2);
  return 0;
}

static char *test_buffer_append() {
  line *l = alloc_line();
  buffer *buf = alloc_buffer();
  buffer_append_line(buf, l);
  mu_assert("new line should be first line", buf->first_line == l);
  mu_assert("new line should be current line", buf->current_line == l);
  mu_assert("new line should be last line", buf->last_line == l);
  line *l2 = alloc_line();
  buffer_append_line(buf, l2);
  mu_assert("first line should still be first", buf->first_line == l);
  mu_assert("second line should be current line", buf->current_line == l2);
  mu_assert("second line should be last line", buf->last_line == l2);
  free_line(l);
  free_line(l2);
  free_buffer(buf);
  return 0;
}

static char *test_buffer_advance() {
  buffer *buf = alloc_buffer();
  line *l1 = alloc_line();
  line *l2 = alloc_line();
  buffer_append_line(buf, l1);
  buffer_append_line(buf, l2);
  buf->current_line = buf->first_line;
  mu_assert("current line should be the first line", buf->current_line == l1);
  bool value = buffer_advance_line(buf);
  mu_assert("current line should now be forward", buf->current_line == l2);
  mu_assert("buffer advancing should return true", value == true);
  value = buffer_advance_line(buf);
  mu_assert("buffer should not advance past the last line", buf->current_line == l2);
  mu_assert("buffer pausing should return false", value == false);
  free_line(l1);
  free_line(l2);
  free_buffer(buf);
  return 0;
}

static char *test_buffer_retreat() {
  buffer *buf = alloc_buffer();
  line *l1 = alloc_line();
  line *l2 = alloc_line();
  buffer_append_line(buf, l1);
  buffer_append_line(buf, l2);
  mu_assert("current line should be the last line", buf->current_line == l2);
  bool value = buffer_retreat_line(buf);
  mu_assert("current line should be the first line", buf->current_line == l1);
  mu_assert("retreat should return true when lines move", value == true);
  value = buffer_retreat_line(buf);
  mu_assert("should not retreat past the beginning of the buffer", buf->current_line == l1);
  mu_assert("retreat should return false when nothing changes", value == false);
  free_line(l1);
  free_line(l2);
  free_buffer(buf);
  return 0;
}

static char *test_buffer_line() {
  buffer *buf = alloc_buffer();
  mu_assert("going to 0th should be null", buffer_goto_line(buf, 0) == NULL);
  mu_assert("going to nth should be null on empty", buffer_goto_line(buf, 3) == NULL);
  line *l1 = alloc_line();
  line *l2 = alloc_line();
  buffer_append_line(buf, l1);
  mu_assert("going to first on single line should be it", buffer_goto_line(buf, 1) == l1);
  mu_assert("going to zeroth should always be null", buffer_goto_line(buf, 0) == NULL);
  buffer_append_line(buf, l2);
  mu_assert("going to second should be line", buffer_goto_line(buf, 2) == l2);
  mu_assert("going to off the end should null", buffer_goto_line(buf, 4) == NULL);
  return 0;
}

static char *test_buffer_line_relative() {
  buffer *buf = alloc_buffer();
  line *l1 = alloc_line();
  line *l2 = alloc_line();
  buffer_append_line(buf, l1);
  buffer_append_line(buf, l2);
  mu_assert("minus should be the first line", buffer_goto_line_relative(buf, -1) == l1);
  mu_assert("plus should then be the second line", buffer_goto_line_relative(buf, 1) == l2);
  mu_assert("plus should then be null", buffer_goto_line_relative(buf, 1) == NULL);
  mu_assert("the current should still be the second", buf->current_line == l2);
  mu_assert("-2 should then be null", buffer_goto_line_relative(buf, -2) == NULL);
  mu_assert("the current should still be the second line", buf->current_line == l2);
  free_line(l1);
  free_line(l2);
  free_buffer(buf);
  return 0;
}

static char *test_buffer_get_line_number() {
  buffer *buf = alloc_buffer();
  line *l1 = alloc_line();
  line *l2 = alloc_line();
  buffer_append_line(buf, l1);
  buffer_append_line(buf, l2);
  mu_assert("current line number should be 2", buffer_get_line_number(buf) == 2);
  buffer_retreat_line(buf);
  mu_assert("current line number should be 1", buffer_get_line_number(buf) == 1);
  free_line(l1);
  free_line(l2);
  free_buffer(buf);
  return 0;
}

int all_tests() {
  mu_run_test(test_strip);
  mu_run_test(test_strip_nl);
  mu_run_test(test_strip_empty);
  mu_run_test(test_strip_only_nl);
  mu_run_test(test_strip_tabs);
  mu_run_test(test_lstrip);
  mu_run_test(test_lstrip_empty);
  mu_run_test(test_lstrip_only_nl);
  mu_run_test(test_lstrip_tabs);
  mu_run_test(test_rstrip);
  mu_run_test(test_rstrip_nl);
  mu_run_test(test_rstrip_empty);
  mu_run_test(test_rstrip_only_nl);
  mu_run_test(test_rstrip_tabs);
  mu_run_test(test_line_append);
  mu_run_test(test_buffer_append);
  mu_run_test(test_buffer_advance);
  mu_run_test(test_buffer_retreat);
  mu_run_test(test_buffer_line);
  mu_run_test(test_buffer_line_relative);
  mu_run_test(test_buffer_get_line_number);
  return 0;
}

int main(int argc, char **argv) {
  all_tests();
  printf("Tests run: %d\n", tests_run);
  if (tests_failed == 0) {
    puts("All tests passed\n");
  } else {
    printf("Tests passed: %d/%d\n", tests_run - tests_failed, tests_run);
  }
  return tests_failed != 0;
}
