/* midunit.h, a medium unit test framework */
/* derived from minunit, http://www.jera.com/techinfo/jtns/jtn002.html */
#include <string.h>
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_assert_eq_str(message, a, b) mu_assert(message, strcmp(a, b) == 0)
#define mu_run_test(test) do { puts("Running " #test); \
                               char *message = test(); tests_run++; \
                               if (message) return message; } while (0)
extern int tests_run;
