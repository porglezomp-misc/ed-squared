#ifndef _MIDUNIT_H
#define _MIDUNIT_H

/* midunit.h, a medium unit test framework */
/* derived from minunit, http://www.jera.com/techinfo/jtns/jtn002.html */

#include <string.h>

extern int tests_run, tests_failed;
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_assert_eq_str(message, a, b) do { if (strcmp(a, b) != 0) { \
  printf("\"%s\" != \"%s\"\n", a, b); return message; } } while (0)
#define mu_run_test(test) _mu_run_test(test, #test)

int _mu_run_test(char* (*test)(), char *name);

#endif
