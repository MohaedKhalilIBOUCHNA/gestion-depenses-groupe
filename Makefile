CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g
SRC_DIR = src
OBJ_DIR = build
TARGET  = gestion_depenses

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/depense.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean run

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build OK → ./$(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
