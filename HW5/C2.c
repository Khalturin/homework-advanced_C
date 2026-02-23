#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdlib.h>

#define false 0
#define true 1

// размер стека 255 элементов
#define MAX_STACK_SIZE 255
// Объявляем глобальный массив типа int для хранения элементов стека
int st[MAX_STACK_SIZE]; // массив - стек

int pst = 0; // заполненность стека


void push(int v) {
    if (pst >= MAX_STACK_SIZE) {
        fprintf(stderr, "Error. Stack overflow\n");
        return;
    }
    st[pst++] = v; 
}

int pop() {
    if (pst <= 0) {
        fprintf(stderr, "Error. Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return st[--pst];
}

void operate(char c) { 
    int arg1 = pop(), arg2 = pop();
    if (c == '+') push(arg1 + arg2);
    else if (c == '-') push(arg2 - arg1);
    else if (c == '*') push(arg1 * arg2);
    else if (c == '/') {
        if (arg1 == 0) {
            fprintf(stderr, "Warning: division by zero\n");
            push(arg2);
            push(arg1);
        } else {
            push(arg2 / arg1);
        }
    }
    else {
        fprintf(stderr, "Warning: unknown operator '%c'\n", c);
        push(arg2);
        push(arg1);
    }
}

int main(void) {
    int number;
    char c;
    char buffer[1024];
    char *endptr;
    
    // Читаем строку с клавиатуры в buffer, максимум 1023 символа + нуль-терминатор, с помощью fgets
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    for (int i = 0; buffer[i] != '\0'; i++) {
        // Присваиваем переменной c текущий символ из строки buffer по индексу i
        c = buffer[i];
        
        // Пропуск  пробельных символов
        if (isspace((unsigned char)c)) {
            continue;
        } else if(c == '.'){// является ли символ точкой
            break;
        // проверяем, является ли символ цифрой, точкой (начало дробной части) или минусом (возможный знак числа)
        } else if (isdigit((unsigned char)c)) {
            // Вызываем функцию strtod для преобразования подстроки, начиная с позиции i, в число int
            // endptr получит адрес первого символа после числа
            number = strtol(&buffer[i], &endptr, 10);
            
            // Проверяем, было ли преобразование успешным (endptr сдвинулся вперёд относительно &buffer[i])
            if (endptr != &buffer[i]) {
                // Если число успешно распарсено, добавляем его в стек с помощью функции push
                push(number);
                // Выводим отладочное сообщение о прочитанном числе в стандартный вывод
                // printf("number: %d\n", number);
                
                // Обновляем индекс i: ставим на позицию перед последним обработанным символом числа
                // Цикл for увеличит i на 1, поэтому следующая итерация начнётся с первого символа после числа
                i = endptr - buffer - 1;
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {// является ли символ одним из поддерживаемых арифметических операторов
            // printf("operate: %c\n", c);
            operate(c);
        } else {
            fprintf(stderr, "Warning: ignoring unknown character '%c'\n", c);
        }
    }
    // После обработки всей строки проверяем, остался ли в стеке ровно один элемент (результат вычислений)
    if (pst == 1) {
        // Если да, извлекаем и выводим итоговый ответ в стандартный вывод с форматированием для int
        printf("%d\n", pop());
    }
    // Иначе, если в стеке не один элемент, выражение было некорректным
    else {
        // Выводим сообщение об ошибке некорректного выражения в поток stderr
        fprintf(stderr, "Error: invalid expression, stack size: %d\n", pst);
    }
    
    // Возвращаем 0 операционной системе, сигнализируя об успешном завершении программы
    return 0;
}