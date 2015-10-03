#include "testing.h"
#include <stdio.h>

static int _failure_count;

void real_print_test(const char* mensaje, bool ok, const char* failed_expr,
		     const char* file, int line, const char* func_name) {
    if (ok) {
	printf("%s... OK\n", mensaje);
    } else {
	printf("%s: ERROR\n"  "FAILED: %s\n"  "%s:%d: %s()\n",
	       mensaje, failed_expr, file, line, func_name);
    }
    fflush(stdout);
    _failure_count += !ok;
}

int failure_count() {
    return _failure_count;
}
