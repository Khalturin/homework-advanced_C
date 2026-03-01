#include "functions.h"
#include "print_info.h"
/*
 * TODO-list:
 * f1 = 0.6x + 3
 * f2 = (x - 2)^3 - 1
 * f3 = 3 / x
 * 1. Опции командной строки:
 *  - печатать абсциссы точек пересечения кривых
 *  - печатать число итераций
 *  - help (печатать все допустимые ключи командной строки)
 *  - запуск тестирования
 * 2. help
 * 3. Вычисление с точностью е1 корня x уравнения f(x) = g(x) на отрезке [a, b]
 * должно быть реализовано в отдельной Си-функции root(f, g, a, b, eps1).
 * 4. Вычисление с точностью е2 величины определённого интеграла от функции
 * f(x) на отрезке [a, b] должно быть реализовано отдельной функцией
 * integral(f, a, b, eps2)
 * 5. Си-функции root и intergal должны быть предварительно протестированы.
 * Основная программа должна предоставлять возможности тестирования
 * активируемые опцией командной строки
 * 6. Сборка программы с помощью make: all, clean.
 * 7. Добавить комментарии для понимания. Все глобальные и статические
 * переменные должны быть документированы в комментариях
 *
 */

static int opt_print_intersections = 0; /* Печатать координаты пересечения */
static int opt_print_steps = 0;         /* Печатать число шагов */
static int opt_run_tests = 0;           /* Запустить режим тестирования */
static int opt_show_help = 0;           /* Показать справку */

// Количество шагов поиска корня
int steps_count1 = 0, steps_count2 = 0, steps_count3 = 0;

/*
 * Парсит аргументы командной строки.
 */
void parse_args(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-help") == 0) {
      opt_show_help = 1;
    } else if (strcmp(argv[i], "-test") == 0) {
      opt_run_tests = 1;
    } else if (strcmp(argv[i], "-intersections") == 0) {
      opt_print_intersections = 1;
    } else if (strcmp(argv[i], "-steps") == 0) {
      opt_print_steps = 1;
    } else {
      fprintf(stderr, "Unknown argument: %s\n", argv[i]);
      fprintf(stderr, "Use -help key for usage information.\n");
      exit(1);
    }
  }
}

// Сортировка корней (трёх значений)
void sort_roots(float* x1, float* x2, float* x3) {
  if (*x1 > *x2) {
    float t = *x1;
    *x1 = *x2;
    *x2 = t;
  }
  if (*x2 > *x3) {
    float t = *x2;
    *x2 = *x3;
    *x3 = t;
  }
  if (*x1 > *x2) {
    float t = *x1;
    *x1 = *x2;
    *x2 = t;
  }
}

int main(int argc, char* argv[]) {
  parse_args(argc, argv);

  if (opt_show_help) {  // Если есть опция help выводим только help
    print_help();
    return 0;
  }

  if (opt_run_tests) {  // Если есть опция test запускается тестирование
    run_tests();
    return 0;
  }

  // Параметры расчёта
  const float XL = 0.5f;      // левая граница
  const float XR = 4.5f;      // правая граница
  const float EPS = 0.0001f;  // точность
  const size_t N = 100000;    // количество для точности интегрирования

  int steps_count1 = 0, steps_count2 = 0, steps_count3 = 0;
  float x1 = root(f1, f3, XL, XR, EPS, &steps_count1);
  float x2 = root(f2, f3, XL, XR, EPS, &steps_count2);
  float x3 = root(f1, f2, XL, XR, EPS, &steps_count3);

  if (opt_print_steps) print_steps(steps_count1, steps_count2, steps_count3);
  if (opt_print_intersections) print_intersections(x1, x2, x3);

  sort_roots(&x1, &x2, &x3);  // Сортировка корней

//   printf("x1: %f x2: %f x3: %f\n", x1, x2, x3);

  // Часть 1: [x1, x2] - между f1 и f3
  float area1 = integral(f1, x1, x2, N) - integral(f3, x1, x2, N);

  // Часть 2: [x2, x3] - между f1 и f2
  float area2 = integral(f1, x2, x3, N) - integral(f2, x2, x3, N);

  // Полная площадь
  float totalArea =
      fabsf(area1) + fabsf(area2);  // fabs на случай неверного порядка функций
  printf("Full area: %.6f\n", totalArea);

  return 0;
}