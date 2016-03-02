#include <stdio.h>
#include <string.h>

#include "minunit.h"
#include "string_util.h"
int tests_run = 0;

static char *test_strip() {
  char *text = "  here's a string   ";
  strip(text);
  mu_assert("strip strings correctly", strcmp(text, "here's a string") == 0);
  return 0;
}

static char *test_strip_nl() {
  char *text = "  remove a newline  \n";
  strip(text);
  mu_assert("remove a newline in strip()", strcmp(text, "remove a newline") == 0);
  return 0;
}

static char *test_lstrip() {
  char *text = "  here's a string  ";
  lstrip(text);
  mu_assert("strip left correctly", strcmp(text, "here's a string  ") == 0);
  return 0;
}

static char *test_rstrip() {
  char *text = "  here's a string  ";
  rstrip(text);
  mu_assert("strip right correctly", strcmp(text, "  here's  string") == 0);
  return 0;
}

static char *test_rstrip_nl() {
  char *text = "remove a newline\n";
  rstrip(text);
  mu_assert("remove a newline", strcmp(text, "remove a newline") == 0);
  return 0;
}

static char *all_tests() {
  mu_run_test(test_strip);
  mu_run_test(test_strip_nl);
  mu_run_test(test_lstrip);
  mu_run_test(test_rstrip);
  mu_run_test(test_rstrip_nl);
  return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();
  if (result != 0) {
    printf("Assertion failed: %s\n", result);
  } else {
    printf("All tests passed\n");
  }
  printf("Tests run: %d\n", tests_run);
  return result != 0;
}
