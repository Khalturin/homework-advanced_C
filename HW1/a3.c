/*
 * Извлечение бит
 * На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). Требуется взять K младших битов числа N и вывести полученное таким образом число.
 * 
 * Examples
    Input
    2 1
    Output
    0
    Input
    12 3
    Output
    4
    Input
    3 5
    Output
    3
    Input
    1024 3
    Output
    0
*/

#include <stdio.h>
#include <stdint.h>

void printBinary(int n, char * str) {
    printf("%s: ", str);
    if (n == 0) {
        printf("0");
        return;
    }
    for (int i = sizeof(n) * 8 - 1; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}
typedef struct{
    uint8_t threebit : 2;
}threebit;

int main() {
    uint32_t n = 0;
    uint32_t k = 0;
    scanf("%u %u", &n, &k);
    uint32_t val = 0;
    val = n & ((1u << k) - 1);
    // printf("n: %u(%x) val: %hhu(%x)\n", n, n, val, val);
    // printBinary(n, "n");
    // printBinary(val, "val");
    printf("%u\n", val);
    return 0;
}