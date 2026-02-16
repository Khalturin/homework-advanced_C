#ifndef SNAKE_H
#define SNAKE_H

#include <curses.h>

#define MIN_Y 2

enum{
    LEFT = 1,
    UP,
    RIGHT,
    DOWN,
    STOP_GAME = 'q' // KEY_F(10)
};

enum {
    MAX_TAIL_SIZE = 100,
    START_TAIL_SIZE = 30,
    MAX_FOOD_SIZE = 20,
    FOOD_EXPIRE_SECONDS = 10
};

struct control_buttons{
    int down;
    int up;
    int left;
    int right;
};

/*
 * Голова змейки содержит в себе
 * x,y - координаты текущей позиции
 * direction - направление движения
 * tsize - размер хвоста
 * tail - ссылка на хвост
 * control_buttons - кнопки управления
*/
typedef struct snake_t{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
} snake_t;

/*
 * Хвост - это массив сосотоящий из координат x, y
*/
typedef struct tail_t{
    int x;
    int y;
} tail_t;

typedef struct food{
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
}food_t;

void initTail(tail_t t[], size_t size);
void initHead(snake_t *head, int x, int y);
void initSnake(snake_t *head, size_t size, int x, int y);
void go(snake_t* snake);
void goTail(snake_t* snake);
void changeDirection(snake_t* snake, const int32_t key);
int isCrush(snake_t *snake);
void initFood(food_t f[], size_t size);
void putFoodSeed(food_t *fp);
void putFood(food_t f[], size_t number_seeds);
void refreshFood(food_t f[], int nfood);
#endif //SNAKE_H