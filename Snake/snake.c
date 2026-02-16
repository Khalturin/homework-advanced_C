#include <stdlib.h>
#include <stdint.h>
#include "snake.h"


struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

/*
 * Инициализация хвоста
 */
void initTail(tail_t t[], size_t size){
    tail_t init_t = {0,0};
    for(size_t i = 0; i < size; i++){
        t[i] = init_t;
    }
}

/*
 * Инициализация головы
 */
void initHead(snake_t *head, int x, int y){
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

/*
 * Инициализация змеи
 * выделает память под хвост и производит инициализацию головы и хвоста
 */
void initSnake(snake_t *head, size_t size, int x, int y){
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size + 1;
    head->controls = default_controls;
}

int isCrush(snake_t *snake){
    for(int i = 1; i < snake->tsize; i++){
        if(snake->x == snake->tail[i].x && snake->y == snake->tail[i].y)
            return 1;
    }
    return 0;
}

/*
 * Движение головы с учетом текущего направления движения
 */
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
    char ch = '*';
    mvprintw(snake->tail[snake->tsize - 1].y,
             snake->tail[snake->tsize - 1].x, " ");
    for(size_t i = snake->tsize - 1; i > 0; i--){
        snake->tail[i] = snake->tail[i - 1];
        if(snake->tail[i].y || snake->tail[i].x)
            mvprintw(snake->tail[i].y, snake->tail[i].x, "%c", ch);
    }
    snake->tail[0].x = snake->x;
    snake->tail[0].y = snake->y;
}

void changeDirection(snake_t* snake, const int32_t key){
    if(key == snake->controls.down && snake->direction != UP)    snake->direction = DOWN;
    if(key == snake->controls.up && snake->direction != DOWN)    snake->direction = UP;
    if(key == snake->controls.right && snake->direction != LEFT) snake->direction = RIGHT;
    if(key == snake->controls.left && snake->direction != RIGHT) snake->direction = LEFT;   
}

// void initFood(food_t f[], size_t size){
//     food_t init = {0,0,0,0,0};
//     int max_y = 0; 
//     int max_x = 0;
//     for(size_t i = 0; i < size; i++){
//         //???
//     }
// }

// void putFoodSeed(food_t *fp){
//     int max_x = 0, max_y = 0;
//     char spoint[2] = {0};
//     getmaxyx(stdscr, max_y, max_x);
//     mvprintw(fp->y, fp->x, " ");
//     // fp->x
// }

// void putFood(food_t f[], size_t number_seeds){
//     for (size_t i = 0; i <  number_seeds; i++){
//         putFoodSeed(&f[i]);
//     }   
// }

// void refreshFood(food_t f[], int nfood){
    
// }