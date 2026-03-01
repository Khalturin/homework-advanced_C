#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// f1 = 0.6x + 3
float f1(float x);
// f2 = (x - 2)^3 - 1
float f2(float x);
// f3 = 3 / x
float f3(float x);

// Тип указателя на функцию: float func(float)
typedef float (*function)(float);

/*
 * @brief Поиск точки пересечения f(x) = g(x) методом деления отрезка пополам
 * @param eps - точность
 * @param step_count - указатель на счётчик шагов
*/
float root(function f, function g, float a, float b, float eps, int *step_count);

// Поиск интеграла методом трапеций
/*
 * @brief Поиск интеграла методом трапеций
 * @param eps - количество разбиений отрезка [a, b] 
*/
float integral(function f, float a, float b, float eps);


#endif /* FUNCTIONS_H */