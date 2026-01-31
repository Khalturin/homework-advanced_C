#include <stdlib.h>
#include <stdint.h>
#include "snake.h"


struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

void initTail(tail_t t[], size_t size){
    tail_t init_t = {0,0};
    for(size_t i = 0; i < size; i++){
        t[i] = init_t;
    }
}

void initHead(snake_t *head, int x, int y){
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y){
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail; // прикрепляем к голове хвост
    head->controls = default_controls;
}

void go(snake_t *head){
    char ch = '@';
    int max_x = 0;
    int max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(head->y, head->x, " ");
    switch (head->direction)
    {
    case LEFT:
        if(head->x <= 0) // Циклическое движение, чтобы не уходить за пределы экрана
            head->x = max_x;
        mvprintw(head->y, --(head->x), "%c", ch);
        break;
    
    case RIGHT:
        if(head->x >= max_x) // Циклическое движение, чтобы не уходить за пределы экрана
            head->x = 0;
        mvprintw(head->y, ++(head->x), "%c", ch);
        break;
        
    case UP:
        if(head->y <= 0) // Циклическое движение, чтобы не уходить за пределы экрана
            head->y = max_y;
        mvprintw(--(head->y), head->x, "%c", ch);
        break;

    case DOWN:
        if(head->y >= max_y) // Циклическое движение, чтобы не уходить за пределы экрана
            head->y = 0;
        mvprintw(++(head->y), head->x, "%c", ch);
        break;
    default:
        break;
    }
}

void goTail(snake_t* snake){
    // char ch = '*';
    // mvprintw(snake->tail[snake->tsize - 1].y,
    //          snake->tail[snake->tsize - 1].x, " ");
    // for(size_t i = snake->tsize - 1; i > 0; i--){
    //     snake->tail[i] = snake->tail[i - 1];
    //     if(snake->tail[i].y || snake->tail[i].x)
    //         mvprintw(snake->tail[i].y, snake->tail[i].x, "%c", ch);
    // }
    // snake->tail[0].x = snake->x;
    // snake->tail[0].y = snake->y;
}

void changeDirection(snake_t* snake, const int32_t key){
    // TODO Убрать реверсивное движение - если двигаемся вправо, то влево уже никак
    if(key == snake->controls.down)  snake->direction = DOWN;
    if(key == snake->controls.up)    snake->direction = UP;
    if(key == snake->controls.right) snake->direction = RIGHT;
    if(key == snake->controls.left)  snake->direction = LEFT;
    
}