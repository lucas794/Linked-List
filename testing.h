#ifndef _TESTING_H
#define _TESTING_H

#include <stdbool.h>

// Imprime el mensaje seguido de OK o ERROR. Contabiliza el número
// total de errores en una variable interna.
#define print_test(mensaje, result) do { \
    real_print_test(mensaje, result, #result, __FILE__, __LINE__, __func__); \
  } while (0)

void real_print_test(const char* mensaje, bool ok, const char* failed_expr,
		     const char* file, int line, const char* func_name);

// Devuelve el número total de errores registrados por print_test().
int failure_count(void);

#endif // _TESTING_H
