#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "snake.h"

typedef enum {
  OPTION_CHOOSE_SNAKE_ONE_COLOR,
  OPTION_CHOOSE_SNAKE_TWO_COLOR,
  OPTION_START_GAME,
  OPTION_EXIT_GAME,
  OPTION_ITEMS
} MENU_OPTION;

typedef enum {
  GAME_MENU,   // Состояние - в Меню
  GAME_START,  // Состояние - Начать Игру / в игре
  GAME_OVER,   // Состояние - Игра закончена (вывести gameover screen)
  GAME_OFF     // Состояние - Выключить игру
} GAME_STATE;

typedef enum {
  RESULT_NONE,     // Нет результата
  RESULT_DRAW,     // Ничья
  RESULT_SNAKE_1,  // Победила змейка 1
  RESULT_SNAKE_2   // Победила змейка 2
} GAME_RESULT;

CONTROL_TYPE color_snake_one = CYELLOW;
CONTROL_TYPE color_snake_two = CCYAN;
int score_snake_one = 0;
int score_snake_two = 0;
GAME_RESULT winner = RESULT_NONE;

int is_run = 1;  // флаг работы программы

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
/*
 * Стартовое меню
 */
GAME_STATE start_menu() {
  MENU_OPTION current_option = 0;  // Текущий выбранный пункт меню (0-3)
  int key;                         // Код нажатой клавиши

  /* Доступные цвета и их соответствия в COLOR_TYPES */
  const char* COLOR_NAMES[] = {"NONE", "GREEN",   "RED",  "YELLOW",
                               "BLUE", "MAGENTA", "CYAN", "WHITE"};

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
          return GAME_OFF;
        }
        break;
    }
  }
}

/*
 * Экран окончания игры.
 * Использует глобальные переменные: winner, score_snake_one, score_snake_two,
 * color_snake_one, color_snake_two.
 *
 * Выход по нажатию: Enter (\r/\n/KEY_ENTER), 'q' или Esc.
 */
GAME_STATE game_over_screen() {
  GAME_STATE state = GAME_MENU;
  int key;

  while (1) {
    clear();  // Очистить экран
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);  // Получить размеры окна

    // --- Заголовок ---
    attron(A_BOLD | A_UNDERLINE);
    mvprintw(2, (max_x - 13) / 2, "GAME OVER!");
    attroff(A_BOLD | A_UNDERLINE);

    // --- Блок с результатом ---
    attron(COLOR_PAIR(CWHITE));
    mvprintw(5, (max_x - 30) / 2, "==============================");
    mvprintw(6, (max_x - 20) / 2, "Match Result:");
    attroff(COLOR_PAIR(CWHITE));

    // Отображение результата с цветовой подсветкой
    switch (winner) {
      case RESULT_DRAW:
        // Ничья - нейтральное отображение
        mvprintw(7, (max_x - 40) / 2, "Mutual self-destruction!");
        mvprintw(8, (max_x - 40) / 2, "2 kamikazes are power!");
        break;

      case RESULT_SNAKE_1:
        // Победа змейки 1 - подсветка её цветом
        attron(COLOR_PAIR(color_snake_one));
        mvprintw(7, (max_x - 25) / 2, "Snake 1 WINS!");
        attroff(COLOR_PAIR(color_snake_one));
        mvprintw(8, (max_x - 25) / 2, "Snake 2 lost.");
        break;

      case RESULT_SNAKE_2:
        // Победа змейки 2 - подсветка её цветом
        attron(COLOR_PAIR(color_snake_two));
        mvprintw(7, (max_x - 25) / 2, "Snake 2 WINS!");
        attroff(COLOR_PAIR(color_snake_two));
        mvprintw(8, (max_x - 25) / 2, "Snake 1 lost.");
        break;

      default:
        break;
    }

    mvprintw(9, (max_x - 30) / 2, "==============================");

    // --- Блок со счетами ---
    mvprintw(11, (max_x - 24) / 2, "Final Scores:");

    // Счет змейки 1 (подсвечен её цветом)
    attron(COLOR_PAIR(color_snake_one));
    mvprintw(12, (max_x - 20) / 2, "Snake 1: %d points", score_snake_one);
    attroff(COLOR_PAIR(color_snake_one));

    // Счет змейки 2 (подсвечен её цветом)
    attron(COLOR_PAIR(color_snake_two));
    mvprintw(13, (max_x - 20) / 2, "Snake 2: %d points", score_snake_two);
    attroff(COLOR_PAIR(color_snake_two));

    // --- Подсказка для продолжения ---
    mvprintw(max_y - 3, (max_x - 45) / 2,
             "Press [ENTER] / [Q] / [ESC] to continue...");

    refresh();  // Обновить экран

    // --- Обработка ввода (блокирующий режим) ---
    timeout(-1);  // Включаем блокирующий ввод
    key = getch();

    // Проверка нажатых клавиш для выхода
    if (key == '\r' || key == '\n' || key == KEY_ENTER || key == 'q' ||
        key == 'Q' || key == 27) {
      // 27 = код клавиши Esc
      break;  // Выход из цикла, возврат в меню
    }

    // Если не вышли, возвращаем неблокирующий режим (на всякий случай)
    timeout(0);
  }
  // Сброс таймаута в исходное состояние (если в игре был timeout(0))
  timeout(0);
  return state;
}

typedef enum {
  SNAKE_COLLISION_NONE,
  SNAKE_COLLISION_KAMIKADZE,
  SNAKE_ONE_WIN,
  SNAKE_TWO_WIN
} SNAKE_COLLISION;
// Проверяет столкновение змей - возвращает индекс змеи врезавшейся в другую
SNAKE_COLLISION isSnakeCollision(snake_t* snake[]) {
  if (snake[0]->x == snake[1]->x && snake[0]->y == snake[1]->y)
    printf("взаимное самоуничтожение / 2 камикадзе это сила\n");

  // Проверка голова второй змеи врезалась в хвост первой
  for (int i = 1; i < snake[0]->tsize; i++) {
    if (snake[1]->x == snake[0]->tail[i].x &&
        snake[1]->y == snake[0]->tail[i].y)
      return SNAKE_ONE_WIN;  // Если врезалась - выиграла первая
  }
  // Проверка голова первой змеи врезалась в хвост второй
  for (int i = 1; i < snake[1]->tsize; i++) {
    if (snake[0]->x == snake[1]->tail[i].x &&
        snake[0]->y == snake[1]->tail[i].y)
      return SNAKE_TWO_WIN;  // Если врезалась - выиграла вторая
  }
  return 0;
}

GAME_STATE game_loop() {
  GAME_STATE state = GAME_OVER;
  // Инициализация глобальных переменных
  score_snake_one = 0;
  score_snake_two = 0;
  winner = RESULT_NONE;

  clear();  // Очистить экран перед перерисовкой
  snake_t* snake[PLAYERS] = {0};
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
        winner = i == 0 ? RESULT_SNAKE_2 : RESULT_SNAKE_1;
        printf("Oops snake %d eat yourself!\n", i);
        break;
      }
      switch (isSnakeCollision(snake)) {
        case SNAKE_COLLISION_KAMIKADZE:
          isGameOver = true;
          winner = RESULT_DRAW;
          break;
        case SNAKE_ONE_WIN:
          isGameOver = true;
          winner = RESULT_SNAKE_1;
          break;
        case SNAKE_TWO_WIN:
          isGameOver = true;
          winner = RESULT_SNAKE_2;
          break;
        default:
          break;
      }
      repairSeed(food, SEED_NUMBER, snake[i]);
    }
    if (isGameOver) {
      break;
    }
    score_snake_one = snake[0]->tsize - START_TAIL_SIZE;
    score_snake_two = snake[1]->tsize - START_TAIL_SIZE;
  }
  for (int i = 0; i < PLAYERS; i++) {
    free(snake[i]->tail);
    free(snake[i]);
  }
  return state;
}

int main() {
  init_curses();
  init_colors();

  //   Main program loop
  GAME_STATE state = GAME_MENU;
  while (is_run) {
    switch (state) {
      case GAME_MENU:
        state = start_menu();
        break;
      case GAME_START:
        state = game_loop();
        break;
      case GAME_OVER:
        state = game_over_screen();
        break;
      case GAME_OFF:
        is_run = 0;
        break;

      default:
        break;
    }
  }

  endwin();  // Завершаем cursed mod
  return 0;
}