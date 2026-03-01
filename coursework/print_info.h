#include "stdio.h"

/**
 * Выводит справку по использованию программы.
 */
void print_help() {
  printf("Program for calculating the area bounded by curves:\n");
  printf("  f1 = 0.6x + 3\n");
  printf("  f2 = (x - 2)^3 - 1\n");
  printf("  f3 = 3 / x\n\n");
  printf("Usage: ./area_calc [options]\n\n");
  printf("Available options:\n");
  printf("  -help          Print this help message\n");
  printf("  -test          Run internal function tests\n");
  printf("  -intersections Print abscissas of curve intersection points\n");
  printf("  -steps    Print number of bisection method steps\n");
  printf("\nExample: ./area_calc -intersections -steps\n");
}

void print_intersections(float x1, float x2, float x3) {
  printf("Intersection points (abscissas):\n");
  printf("  f1 and f3: x = %.8f\n", x1);
  printf("  f3 and f2: x = %.8f\n", x2);
  printf("  f2 and f1: x = %.8f\n", x3);
}

void print_steps(int steps1, int steps2, int steps3) {
  printf("Number of bisection method steps:\n");
  printf("  For f1=f3: %d\n", steps1);
  printf("  For f3=f2: %d\n", steps2);
  printf("  For f2=f1: %d\n", steps3);
}