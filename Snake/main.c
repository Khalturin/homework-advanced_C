#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "snake.h"

/*
 * TODO (ДЗ)
 * 1. Доработать функционал: реализовать ситуацию, когда змея врезается сама в себя.
 * 2. Выход за границы экрана
 * 3. * Переписать timeout через clock
*/

// void myTimeout(clock_t delay){
//     clock_t begin = clock();
//     clock_t deltat = clock() - begin;
//     while (deltat < delay){
//         deltat = clock() - begin;
//     }
// }

void init_colors(){
    start_color();
    init_pair(CGREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(CRED, COLOR_RED, COLOR_BLACK);
    init_pair(CYELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CBLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(CMAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CCYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(CWHITE, COLOR_WHITE, COLOR_BLACK);
}

int main(){
    snake_t* snake[PLAYERS] = {0};// = (snake_t *)malloc(sizeof(snake_t));
    food_t food[MAX_FOOD_SIZE];
    snake[0] = initSnake(START_TAIL_SIZE, 10, 15, CBLUE);
    snake[1] = initSnake(START_TAIL_SIZE, 10, 10, CCYAN);
    setSnakeControls(snake[0], CONTROL_WASD);
    setSnakeControls(snake[1], CONTROL_ARROWS);
    // initFood(food, MAX_FOOD_SIZE);
    // putFood(food, MAX_FOOD_SIZE);
    initscr();
    keypad(stdscr, TRUE);// Включаем F1, F2, стрелки и т.д.
    raw();// Отключаем line buffering
    noecho(); // Отключаем echo() режим при вызове getch()
    curs_set(FALSE); // Отключаем курсор
    mvprintw(0, 0, "Use arrows for control. Press 'q' for EXIT");
    timeout(0); // Отключаем таймаут после нажатия клавиши в цикле
    initFood(food, MAX_FOOD_SIZE);
    putFood(food, SEED_NUMBER);// Кладем зерна
    int key_pressed = 0;
    _Bool isGameOver = false;

    init_colors();

    while( key_pressed != STOP_GAME ) {
        key_pressed = getch(); // Считываем клавишу
        for(int i = 0; i < PLAYERS; i++){
            update(snake[i], food, key_pressed);
            if(isCrush(snake[i])){
                isGameOver = true;
                printf("Oops snake %d eat yourself!\n", i);
                break;
            }
            repairSeed(food, SEED_NUMBER, snake[i]);
        }
        if(isGameOver){
            break;
        }
    }
    for(int i = 0; i < PLAYERS; i++){
        free(snake[i]->tail);
        free(snake[i]);
    }
    endwin(); // Завершаем cursed mod
    return 0;
}