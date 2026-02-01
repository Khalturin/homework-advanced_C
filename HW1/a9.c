/*
 * Упаковать массив
 *  В программе реализована структура данных:
 *  struct pack_array {
 *  uint32_t array; // поле для хранения упакованного массива из 0 и 1
 *  uint32_t count0 : 8; // счетчик нулей в array
 *  uint32_t count1 : 8; // счетчик единиц в array
 *  }
 *  Необходимо реализовать программу, которая упаковывает переданный ей массив из 32-ух элементов 0 и 1 в указанную структуру данных.
 *  Функция должна строго соответствовать прототипу:
    void array2struct(int [], struct pack_array *)
*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct pack_array {
    uint32_t array; // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8; // счетчик нулей в array
    uint32_t count1 : 8; // счетчик единиц в array
};

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

void array2struct(int mass[], struct pack_array * packedArray){
    int j = 31;
    for(int i = 0; i < 32; i++){
        if(mass[i] == 1){
            packedArray->array |= 1 << j;
            packedArray->count1++;
        }
        // printf("[%d] %d ", i, mass[i], packedArray->array);
        // printBinary(packedArray->array, "array");
        j--;
    }
    packedArray->count0 = 32 - packedArray->count1;
}

int main(){
    // int mass[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1};
    // int mass[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    // int mass[] = {1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1};
    int mass[32] = {0};
    for(int i = 0; i < 32; i++){
        scanf("%d", &mass[i]);
    }
    struct pack_array parray;
    memset(&parray, 0, sizeof(parray));

    array2struct(mass, &parray);

    printf("%u %u %u\n", parray.array, parray.count0, parray.count1);
}