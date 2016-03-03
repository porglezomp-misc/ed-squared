#ifndef _MIDUNIT_H
#define _MIDUNIT_H

/* midunit.h, a medium unit test framework */
/* derived from minunit, http://www.jera.com/techinfo/jtns/jtn002.html */

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int tests_run = 0, tests_failed = 0;
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_assert_eq_str(message, a, b) mu_assert(message, strcmp(a, b) == 0)
#define mu_run_test(test) _mu_run_test(test, #test)

int _mu_run_test(char* (*test)(), char *name) {
  printf("Running %s\n", name);
  int pid, status;
  char *message;
  tests_run++;
  switch (pid = fork()) {
  case -1:
    perror("fork");
    _exit(1);
  case 0:
    message = test();
    if (message) {
      printf("Assertion failed: %s\n", message);
      _exit(1);
    }
    puts("Succeded!");
    _exit(0);
  default:
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
      printf("Forced to close with signal %d\n", WTERMSIG(status));
    }
    if (status) tests_failed++;
    return status;
  }
}

#endif
