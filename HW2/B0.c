#include "stdint.h"

typedef struct list {
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

uint64_t findMaxBlock(list *head){
    size_t sizelist = 0;
    uint64_t address = 0;
    if(head == NULL)
        return address;
    sizelist = head->size;
    address = head->address;
    while(head->next != NULL){
        head = head->next;
        if(sizelist < head->size){
            sizelist = head->size;
            address = head->address;
        }
    }
    return address;
}

int main(){

    return 0;
}