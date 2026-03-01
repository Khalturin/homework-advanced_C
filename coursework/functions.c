#include "functions.h"

// f1 = 0.6x + 3
float f1(float x) { return (0.6 * x) + 3; }
// f2 = (x - 2)^3 - 1
float f2(float x) { return pow(x - 2, 3) - 1; }
// f3 = 3 / x
float f3(float x) { return 3 / x; }

// Вспомогательная функция: возвращает знак разности f1(x) - f2(x)
int signF(float x, function f1, function f2) {
  float val = f1(x) - f2(x);
  return (val > 0) ? 1 : (val < 0) ? -1 : 0;
}

// Поиск интеграла методом трапеций
float integral(function f, float a, float b, float eps) {
  float sum = 0;
  float h = (b - a) / eps;
  for (float x = a + h; x < b - h; x += h) {
    sum += 0.5 * h * (f(x) + f(x + h));
  }
  return sum;
}

// Поиск точки пересечения f(x) = g(x) методом деления отрезка пополам
float root(function f, function g, float a, float b, float eps,
           int* stepcount) {
  float c;

  while (fabs(b - a) > eps) {  // вещественный модуль разницы
    (*stepcount)++;            // инкремент счетчика шагов
    c = (a + b) / 2;           // середина отрезка

    float diff_xl = f(a) - g(a);
    float diff_xr = f(b) - g(b);

    // Проверка на точное попадание в корень
    if (diff_xr == 0) return b;
    if (diff_xl == 0) return a;

    // Если знак на [a, c] различается — корень там
    if (signF(a, f, g) != signF(c, f, g))
      b = c;
    else
      a = c;
  }
  return (a + b) / 2;  // возврат середины финального отрезка
}
