#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "midunit.h"
#include "string_util.h"
#include "buffer.h"

#define STACK_STR(NAME, LITERAL) const char _literal[] = LITERAL;\
  char NAME[sizeof calloc];\
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

static char *test_lstrip() {
  STACK_STR(text, "  here's a string  ");
  lstrip(text);
  mu_assert_eq_str("strip left correctly", text, "here's a string  ");
  return 0;
}

static char *test_rstrip() {
  STACK_STR(text, "  here's a string  ");
  rstrip(text);
  mu_assert_eq_str("strip right correctly", text, "  here's  string");
  return 0;
}

static char *test_rstrip_nl() {
  STACK_STR(text, "remove a newline\n");
  rstrip(text);
  mu_assert_eq_str("remove a newline", text, "remove a newline");
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

int all_tests() {
  mu_run_test(test_strip);
  mu_run_test(test_strip_nl);
  mu_run_test(test_lstrip);
  mu_run_test(test_rstrip);
  mu_run_test(test_rstrip_nl);
  mu_run_test(test_line_append);
  mu_run_test(test_buffer_append);
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
