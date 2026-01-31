#include "stdint.h"

typedef struct list {
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

size_t totalMemoryUsage(list *head){
    size_t totalMemory = 0;
    if(head == NULL)
        return totalMemory;
    totalMemory = head->size;
    while(head->next != NULL){
        head = head->next;
        totalMemory += head->size;
    }
    return totalMemory;
}


int main(){

    return 0;
}