/*
 * Циклический сдвиг
 * На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). Требуется циклически сдвинуть битычисла N вправо на K битов и вывести полученное таким образом число.
*/

#include <stdio.h>
#include <stdint.h>


int rightRotate(uint32_t n, uint32_t rotate){
    return (n >> rotate)|(n << (32 - rotate));
}

int main() {
    uint32_t n;
    uint32_t k;
    scanf("%u %u", &n, &k);

    n = rightRotate(n, k);

    printf("%u\n", n);
    return 0;
}