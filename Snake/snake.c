#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "snake.h"

#define DELAY 0.1

struct control_buttons default_controls_one[CONTROLS] = {'s', 'w', 'a', 'd', 'S', 'W', 'A', 'D'};
struct control_buttons default_controls_two[CONTROLS] = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT, 0, 0, 0, 0};

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
snake_t* initSnake(size_t size, int x, int y,  COLOR_TYPES color){
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(snake, x, y);
    snake->tail = tail; // прикрепляем к голове хвост
    snake->tsize = size + 1;
    snake->color = color;
    return snake;
}

void setSnakeControls(snake_t *snake, CONTROL_TYPE typeControl){
    switch (typeControl) {
    case CONTROL_WASD:
        for(int i = 0; i < CONTROLS; i++)
            snake->controls[i] = default_controls_one[i];
        break;
    case CONTROL_ARROWS:
        for(int i = 0; i < CONTROLS; i++)
            snake->controls[i] = default_controls_two[i];
        break;
    default:
        break;
    }
    
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
    // setColor(head->type);
    setColor(head->color);
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

uint8_t checkDirection(snake_t* snake, const int32_t key){
    for(int i = 0; i < CONTROLS; i++){
        if(key == snake->controls[i].down && snake->direction != UP)
            return 1;
        else if (key == snake->controls[i].up && snake->direction != DOWN)
            return 1;
        else if (key == snake->controls[i].right && snake->direction != LEFT)
            return 1;
        else if(key == snake->controls[i].left && snake->direction != RIGHT)
            return 1;
    }
    return 0;
}

void changeDirection(snake_t* snake, const int32_t key){
    for(int i = 0; i < CONTROLS; i++){
        if(key == snake->controls[i].down)  snake->direction = DOWN;
        if(key == snake->controls[i].up )   snake->direction = UP;
        if(key == snake->controls[i].right) snake->direction = RIGHT;
        if(key == snake->controls[i].left)  snake->direction = LEFT;   
    }   
}

//Проверка того, является ли какое-то из зерен съеденным,
_Bool haveEat(struct snake_t *snake, struct food f[], size_t food_size){
    for(int i = 0; i < food_size; i++){
        if(snake->x == f[i].x && snake->y == f[i].y)
            return true;
    }
    return false;
}

/*
 Увеличение хвоста на 1 элемент
 */

void addTail(struct snake_t *snake){
    snake->tsize++; // increase tail
}

void initFood(food_t f[], size_t size){
    food_t init = {0, 0, 0, 0, 0};
    for(size_t i = 0; i < size; i++){
        f[i] = init;
    }
}

// Обновить/разместить текущее зерно на поле
void putFoodSeed(food_t *fp){
    int max_x = 0, max_y = 0;
    char spoint[2] = {0};
    setColor(CRED);// Красный цвет еды
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(fp->y, fp->x, " ");
    fp->x = rand() % (max_x - 1);
    fp->y = rand() % (max_y - 2) + 1; //Не занимаем верхнюю строку
    fp->put_time = time(NULL);
    fp->point = '$';
    fp->enable = 1;
    spoint[0] = fp->point;
    mvprintw(fp->y, fp->x, "%s", spoint);
}

void putFood(food_t f[], size_t number_seeds){
    for (size_t i = 0; i < number_seeds; i++){
        putFoodSeed(&f[i]);
    }   
}

void refreshFood(food_t f[], int nfood){
    for(size_t i = 0; i < nfood; i++) {
        if( f[i].put_time ) {
            if( !f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS ) {
                putFoodSeed(&f[i]);
            }
        }
    }
}

void repairSeed(struct food f[], size_t nfood, struct snake_t *head){
    for( size_t i = 0; i < head->tsize; i++ )
        for( size_t j = 0; j < nfood; j++ ) {
            /* Если хвост совпадает с зерном */
            //...нужно написать код...//
        }
    for( size_t i = 0; i < nfood; i++ )
        for( size_t j = 0; j < nfood; j++ ) {
            /* Если два зерна на одной точке */
            //...нужно написать код...//
        }
}

void update(snake_t *head, food_t food[], const int32_t key){
    clock_t begin = clock();
    go(head);
    goTail(head);
    if (checkDirection(head,key)) {
        changeDirection(head, key);
    }
    refreshFood(food, SEED_NUMBER);// Обновляем еду
    if (haveEat(head, food, SEED_NUMBER)) {
        addTail(head);
    }
    refresh();
    while ((double)(clock() - begin) / CLOCKS_PER_SEC < DELAY){}
}

// void setColor(OBJECT_TYPES objectType){
//     for(int i = 0; i < CFULL; i++){
//         attroff(COLOR_PAIR(i));
//     }
//     switch (objectType) {
//     case OBJ_SNAKE_ONE: 
//         attron(COLOR_PAIR(CMAGENTA));
//         break;
//     case OBJ_SNAKE_TWO: 
//         attron(COLOR_PAIR(CCYAN));
//         break;
//     case OBJ_EAT: 
//         attron(COLOR_PAIR(CRED));
//         break;
//     default:
//         break;
//     }
// }

void setColor(COLOR_TYPES color){
    for(int i = CGREEN; i < CFULL; i++){
        attroff(COLOR_PAIR(i));
    }
    attron(COLOR_PAIR(color));
}