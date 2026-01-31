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

uint32_t biggestValueInBits(uint32_t value, uint32_t bits){
    uint32_t max = 0;
    bits = (1u << bits) - 1; // Получить маску по кол-ву бит (прим. 3 бит: 111, 4 бит: 1111)
    for(int i = 0; i <= 32; i++){
        // сравнить по маске размером bits (прим. 3 бит: 0000 0111) 
        uint32_t val = value & bits; // Получившуюся последовательность положить в val
        val >>= i; // Сдвинуть на i последовательность вправо
        if( max < val) 
            max = val;
        bits <<= 1; // сдвинуть маску на 1 влево (прим 3 бит: 0000 1110)
    }
    return max;
}

int main() {
    uint32_t n = 0;
    uint32_t k = 0;
    scanf("%u %u", &n, &k);
    uint32_t max = biggestValueInBits(n, k);
    printf("%u", max);
    return 0;
}