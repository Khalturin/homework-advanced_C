/*
 * Не пара
 * Преподаватели Geek Brains создали набор, содержащий N (1 ≤ N ≤ 1 000 000) натуральных чисел, не превосходящих 1 000 000. Известно, что ровно одно число в этом наборе встречается один раз, а остальные — ровно по два раза. Помогите им найти это число. Входныеданные: в первой входной строке вводится число N, затем по одному числу в строке вводятся N натуральных чисел, не превосходящих 2000 000 000. Выходные данные: ваша программа должна определить число, встречающееся один раз, и вывести его на экран. Указание: использовать массивы запрещается.
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

uint32_t searchOneFromDoubles(uint32_t amount){
    int32_t res = 0;
    uint32_t val = 0;
    
    for(int i = 0; i < amount; i++){
        scanf("%u", &val);
        res ^= val;
    }
    return res;
}

int main() {
    uint32_t val = 0;
    scanf("%u", &val);
    uint32_t res = searchOneFromDoubles(val);
    printf("%u\n", res);
    return 0;
}