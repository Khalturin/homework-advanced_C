#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "snake.h"

int is_run = 1;  // флаг работы программы

typedef enum { GAME_START, GAME_OVER } GAME_MENU;
typedef enum {
  OPTION_CHOOSE_SNAKE_ONE_COLOR,
  OPTION_CHOOSE_SNAKE_TWO_COLOR,
  OPTION_START_GAME,
  OPTION_EXIT_GAME,
  OPTION_ITEMS
} MENU_OPTION;

CONTROL_TYPE color_snake_one = CYELLOW;
CONTROL_TYPE color_snake_two = CCYAN;

void init_colors() {
  start_color();
  init_pair(CGREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(CRED, COLOR_RED, COLOR_BLACK);
  init_pair(CYELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(CBLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(CMAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(CCYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(CWHITE, COLOR_WHITE, COLOR_BLACK);
}

void init_curses() {
  // Инициализация curses
  initscr();
  keypad(stdscr, TRUE);  // Включаем F1, F2, стрелки и т.д.
  raw();                 // Отключаем line buffering
  noecho();              // Отключаем echo() режим при вызове getch()
  curs_set(FALSE);       // Отключаем курсор
  mvprintw(0, 0, "Use arrows for control. Press 'q' for EXIT");
  timeout(0);  // Отключаем таймаут после нажатия клавиши в цикле
}

GAME_MENU startMenu() {
  MENU_OPTION current_option = 0;  // Текущий выбранный пункт меню (0-3)
  int key;                         // Код нажатой клавиши

  /* Доступные цвета и их соответствия в ncurses/PDCurses */
  const char* COLOR_NAMES[] = {"NONE", "GREEN",   "RED",  "YELLOW", "BLUE",
                               "MAGENTA", "CYAN", "WHITE"};

  // --- Главный цикл меню ---
  while (1) {
    clear();  // Очистить экран перед перерисовкой
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);  // Получить размеры терминала

    // --- Отрисовка заголовка и описания ---
    // Используем attron для жирного текста
    attron(A_BOLD);
    mvprintw(1, (max_x - 20) / 2, "SNAKE GAME MENU");
    attroff(A_BOLD);

    mvprintw(3, 2, "Controls:");
    mvprintw(4, 4, "Snake 1: W, A, S, D");
    mvprintw(5, 4, "Snake 2: Arrow Keys");

    mvprintw(7, 2, "Settings:");
    mvprintw(9, 4, "Choose color(use arrow): <- ->");

    // --- Отрисовка пунктов меню ---
    for (MENU_OPTION i = 0; i < OPTION_ITEMS; i++) {
      int y_pos = 11 + i * 2;  // Позиция по вертикали для каждого пункта

      // Подсветка текущего выбранного пункта
      if (i == current_option) {
        attron(A_REVERSE);  // Инверсия цвета для выделения
      }

      switch (i) {
        case OPTION_CHOOSE_SNAKE_ONE_COLOR:  // Выбор цвета Змеи 1
          mvprintw(y_pos, 4, "Snake 1 Color: %s", COLOR_NAMES[color_snake_one]);
          // Отображаем цвет текстом
          attron(COLOR_PAIR(color_snake_one));
          mvprintw(y_pos, 28, "[SNAKE ONE]");
          attroff(COLOR_PAIR(color_snake_one));
          break;

        case OPTION_CHOOSE_SNAKE_TWO_COLOR:  // Выбор цвета Змеи 2
          mvprintw(y_pos, 4, "Snake 2 Color: %s", COLOR_NAMES[color_snake_two]);
          attron(COLOR_PAIR(color_snake_two));
          mvprintw(y_pos, 28, "[SNAKE TWO]");
          attroff(COLOR_PAIR(color_snake_two));
          break;

        case OPTION_START_GAME:  // Кнопка Запуска
          mvprintw(y_pos, 4, "START GAME");
          break;

        case OPTION_EXIT_GAME:  // Кнопка Выхода
          mvprintw(y_pos, 4, "EXIT");
          break;
      }

      if (i == current_option) {
        attroff(A_REVERSE);  // Убрать выделение
      }
    }

    // --- Подсказка по навигации ---
    mvprintw(max_y - 2, 2,
             "Navigation: UP/DOWN - select, LEFT/RIGHT - change color, ENTER - "
             "confirm");

    refresh();  // Обновить экран

    // --- Обработка ввода ---
    key = getch();

    switch (key) {
      case KEY_UP:
        // Перемещение вверх по меню
        current_option--;
        if (current_option < 0) current_option = OPTION_ITEMS - 1;
        break;

      case KEY_DOWN:
        // Перемещение вниз по меню
        current_option++;
        if (current_option >= OPTION_ITEMS) current_option = 0;
        break;

      case KEY_LEFT:
        // Смена цвета влево (только для пунктов 0 и 1)
        if (current_option == 0) {
          color_snake_one--;
          if (color_snake_one < CGREEN) color_snake_one = CFULL - 1;
        } else if (current_option == 1) {
          color_snake_two--;
          if (color_snake_two < CGREEN) color_snake_two = CFULL - 1;
        }
        break;

      case KEY_RIGHT:
        // Смена цвета вправо (только для пунктов 0 и 1)
        if (current_option == 0) {
          color_snake_one++;
          if (color_snake_one >= CFULL) color_snake_one = CGREEN;
        } else if (current_option == 1) {
          color_snake_two++;
          if (color_snake_two >= CFULL) color_snake_two = CGREEN;
        }
        break;

      case '\r':  // Enter (Windows/PDCurses)
      case 10:    // Enter (Linux/Unix) (код 10) '\n'
      case KEY_ENTER:
        if (current_option == 2) {
          return GAME_START;
        } else if (current_option == 3) {
          return GAME_OVER;
        }
        break;
    }
  }
}

int game_loop() {
  clear(); // Очистить экран перед перерисовкой
  snake_t* snake[PLAYERS] = {0};  // = (snake_t *)malloc(sizeof(snake_t));
  snake[0] = initSnake(START_TAIL_SIZE, 10, 15, color_snake_one);
  snake[1] = initSnake(START_TAIL_SIZE, 10, 10, color_snake_two);
  setSnakeControls(snake[0], CONTROL_WASD);
  setSnakeControls(snake[1], CONTROL_ARROWS);

  food_t food[MAX_FOOD_SIZE];
  initFood(food, MAX_FOOD_SIZE);
  putFood(food, SEED_NUMBER);  // Кладем зерна
  int key_pressed = 0;
  _Bool isGameOver = false;

  while (key_pressed != STOP_GAME) {
    key_pressed = getch();  // Считываем клавишу
    for (int i = 0; i < PLAYERS; i++) {
      update(snake[i], food, key_pressed);
      if (isCrush(snake[i])) {
        isGameOver = true;
        printf("Oops snake %d eat yourself!\n", i);
        break;
      }
      repairSeed(food, SEED_NUMBER, snake[i]);
    }
    if (isGameOver) {
      break;
    }
  }
  for (int i = 0; i < PLAYERS; i++) {
    free(snake[i]->tail);
    free(snake[i]);
  }
}

int main() {
  init_curses();
  init_colors();

  //   Main program loop
  while (is_run) {
    GAME_MENU res = startMenu();
    switch (res) {
      case GAME_START:
        game_loop();
        break;
      case GAME_OVER:
        is_run = 0;
        break;

      default:
        break;
    }
  }

  endwin();  // Завершаем cursed mod
  return 0;
}