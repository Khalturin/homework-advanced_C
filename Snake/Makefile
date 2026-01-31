# Makefile
CC = gcc

# Название исполняемого файла
TARGET = snake

# Исходные файлы
SRCS = main.c snake.c

# Диреектории
OBJ_DIR = objects
BIN_DIR = build

#objects = sensor.o temp_api.o main.o
# Объектные файлы теже что и исходные, но в дирректории objects/
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Исполняемый файл в дирректории build/
EXE = $(BIN_DIR)/$(TARGET)

# Путь к библиотеке
LIB_PATH = D:/src/Libraries_C/PDCurses-3.9/wincon
LIB_FILE = $(LIB_PATH)/pdcurses.a

# Путь к заголовкам
INCLUDE_PATH = D:/src/Libraries_C/PDCurses-3.9/

all: $(EXE)

# Сборка исполняемого файла
# $^ - список всех зависимостей .o
# Сборка исполняемого файла
$(EXE): $(OBJS) | $(BIN_DIR)
	$(CC) -mconsole -o $@ $^ $(LIB_FILE)

# Сборка объектных файлов (.c -> .o) в дирректорию objects
# %.o: %.c - шаблон для компиляции .c в .o.
# $@ Имя файла цели правила
# $< Имя первого пререквизита
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) -I$(INCLUDE_PATH) -c $< -o $@

# Создание дирректорий (если их нет)
$(OBJ_DIR) $(BIN_DIR):
	mkdir $@

# Очистка
clean: 
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(EXE)

