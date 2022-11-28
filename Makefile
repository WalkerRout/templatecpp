CC = g++
OBJS = src/main_4.cpp
OBJ = bin/template
CFLAGS = -std=gnu++20
LIBS = -lpthread

all: run

build:
	@$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(OBJ)

run: build
	@./$(OBJ)

clean:
	@rm ./$(OBJ)
	@echo "Cleaned!"
