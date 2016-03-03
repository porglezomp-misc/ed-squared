#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "midunit.h"
#include "string_util.h"

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

int all_tests() {
  mu_run_test(test_strip);
  mu_run_test(test_strip_nl);
  mu_run_test(test_lstrip);
  mu_run_test(test_rstrip);
  mu_run_test(test_rstrip_nl);
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
