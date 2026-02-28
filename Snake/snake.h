#ifndef SNAKE_H
#define SNAKE_H

#include <curses.h>

#define MIN_Y 2
#define CONTROLS 2

enum{
    LEFT = 1,
    UP,
    RIGHT,
    DOWN,
    STOP_GAME = 'q' // KEY_F(10)
};


#define PLAYERS  2
#define SEED_NUMBER 13

enum {
    MAX_TAIL_SIZE = 100,
    START_TAIL_SIZE = 3,
    MAX_FOOD_SIZE = 20,
    FOOD_EXPIRE_SECONDS = 10
};

typedef enum{
    CONTROL_WASD,
    CONTROL_ARROWS
}CONTROL_TYPE;

typedef enum{
    CGREEN,
    CRED,
    CYELLOW,
    CBLUE,
    CMAGENTA,
    CCYAN,
    CWHITE,
    CFULL
}COLOR_TYPES;

// typedef enum{
//     OBJ_SNAKE_ONE,
//     OBJ_SNAKE_TWO,
//     OBJ_EAT
// }OBJECT_TYPES;

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
    struct control_buttons controls[CONTROLS];
    // OBJECT_TYPES type;
    COLOR_TYPES color;
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
snake_t* initSnake(size_t size, int x, int y, COLOR_TYPES color);
void setSnakeControls(snake_t *snake, CONTROL_TYPE typeControl);
void go(snake_t* snake);
void goTail(snake_t* snake);
void changeDirection(snake_t* snake, const int32_t key);
int isCrush(snake_t *snake);
void initFood(food_t f[], size_t size);
void putFoodSeed(food_t *fp);
void putFood(food_t f[], size_t number_seeds);
void refreshFood(food_t f[], int nfood);
void update(struct snake_t *head, struct food f[], const int32_t key);
void playSound(int type);
_Bool haveEat(struct snake_t *head, struct food f[], size_t food_size); // Проверка того, является ли какое-то из зерен съеденным,
void addTail(struct snake_t *head); // Увеличение хвоста на 1 элемент
void repairSeed(struct food f[], size_t nfood, struct snake_t *head);
// void setColor(OBJECT_TYPES objectType);
void setColor(COLOR_TYPES color);
#endif //SNAKE_H