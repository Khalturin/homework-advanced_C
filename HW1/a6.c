/*
 * Инверсия старших
 * На вход программе подается беззнаковое 32-битное целое число N. Требуется изменить значения всех битов старшего байта числа на противоположные и вывести полученное таким образом число.
*/

#include <stdio.h>
#include <stdint.h>

void printBinary(int n, char * str) {
    printf("%s: ", str);
    if (n == 0) {
        printf("0\n");
        return;
    }
    for (int i = sizeof(n) * 8 - 1; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}

uint32_t inversBits(uint32_t value){
    return value ^ 0xFF000000u;
}

int main() {
    uint32_t val = 0;
    scanf("%u", &val);
    printf("%u\n", inversBits(val));
    return 0;
}