/*
 * Поиск последовательности бит
 * На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). Требуется взять K подряд идущих битов числа N так, чтобы полученное число было максимальным. Программа должна вывести полученное число.
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

uint32_t OnesBitCounter(uint32_t value){
    uint32_t counter = 0;
    for(int i = 0; i <= 32; value >>= 1u){
        if (value & 1u)
            counter++; 
        i++;
    }
    return counter;
}

int main() {
    uint32_t val = 0;
    scanf("%u", &val);
    printf("%u", OnesBitCounter(val));
    return 0;
}