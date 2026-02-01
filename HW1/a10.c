/*
 * Распаковать порядок
 * Необходимо реализовать программу, которой на входе передаётся вещественное число в типе float, она возвращает порядок который хранится в поле EXP в виде десятичного целого числа. Функция должна строго соответствовать прототипу:
    int extractExp(float)
*/

#include <stdint.h>
#include <stdio.h>

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
union floatbit {
    float value;
    struct {
        uint32_t mant : 23;
        uint32_t exp : 8;
        uint32_t sign : 1;
    } bit;
} f;

int extractExp(float value){
    union floatbit fb;
    fb.value = value;
    return fb.bit.exp;
}




int main(){
    float value;
    scanf("%f", &value);
    printf("%d\n", extractExp(value));
}