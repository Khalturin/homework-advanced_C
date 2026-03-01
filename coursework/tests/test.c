#include "test.h"

#include "../functions.h"

/* Глобальные переменные для статистики тестов */
static int tests_passed = 0;
static int tests_failed = 0;

/* Тестовые функции */
static float test_f_quad(float x) { return x * x - 4.0; } /* Корень 2 */
static float test_g_zero(float x) {
  (void)x;
  return 0.0;
}
static float test_f_lin(float x) { return x; } /* Интеграл от 0 до 1 = 0.5 */

void run_tests() {
  printf("=== Starting Tests ===\n");

  /* Тест 1: Поиск корня x^2 - 4 = 0 на [1, 3] методом бисекции */
  int steps = 0;
  float r = root(test_f_quad, test_g_zero, 1.0, 3.0, 0.001, &steps);
  if (fabs(r - 2.0) < 1e-4) {
    printf("[PASS] Root test (bisection): x^2-4=0, found %.6f (steps: %d)\n", r,
           steps);
    tests_passed++;
  } else {
    printf("[FAIL] Root test (bisection): x^2-4=0, expected 2.0, found %.6f\n",
           r);
    tests_failed++;
  }

  /* Тест 2: Интеграл от x на [0, 1] */
  float val = integral(test_f_lin, 0.0, 1.0, 10000);
  if (fabs(val - 0.5) < 1e-4) {
    printf("[PASS] Integral test: x on [0,1], found %.6f\n", val);
    tests_passed++;
  } else {
    printf("[FAIL] Integral test: x on [0,1], expected 0.5, found %.6f\n", val);
    tests_failed++;
  }

  printf("=== Tests Completed: %d passed, %d failed ===\n", tests_passed,
         tests_failed);
}