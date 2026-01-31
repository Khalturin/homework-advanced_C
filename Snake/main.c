#include <stdio.h>
#include <stdlib.h>

#include "snake.h"

/*
 * TODO (ДЗ)
 * 1. Доработать функционал: реализовать ситуацию, когда змея врезается сама в себя.
 * 2. Выход за границы экрана
 * 3. * Переписать timeout через clock
*/

int main(){
    snake_t* snake = (snake_t *)malloc(sizeof(snake_t));
    initSnake(snake, START_TAIL_SIZE, 10, 10);
    initscr();
    keypad(stdscr, TRUE);// Включаем F1, F2, стрелки и т.д.
    raw();// Отключаем line buffering
    noecho(); // Отключаем echo() режим при вызове getch()
    curs_set(FALSE); // Отключаем курсор
    mvprintw(0, 0, "Use arrows for control. Press 'q' for EXIT");
    timeout(0); // Отключаем таймаут после нажатия клавиши в цикле
    int key_pressed = 0;
    while(key_pressed != STOP_GAME){
        key_pressed = getch(); // Считываем клавишу
        go(snake);
        goTail(snake);
        timeout(100); // Задержка при отрисовке
        changeDirection(snake, key_pressed);
        refresh();
    }
    free(snake->tail);
    free(snake);
    endwin(); // Завершаем cursed mod
    return 0;
}