# Variables ...................................................................:

## Compilateur ................................................................:

CC = gcc
CFLAGS = -g3 -Wall -lncurses
LDFLAGS = -lm -lncurses

## Structure du projet ........................................................:

EXEC = bin/seaofdevs
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = lib/include/

SRC = $(shell find $(SRC_PATH)*.c)
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

## Autres .....................................................................:

ARGS =

## Lancement ..................................................................:

test : compil 
	$(info Lancement de $(EXEC) :)
	./$(EXEC) $(ARGS)

## Compilation ................................................................:

compil : $(EXEC)

$(EXEC) : $(OBJ)
	$(info Édition des liens dans $(EXEC) :)
	$(CC) $^ -o $(EXEC) $(LDFLAGS)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(INC_PATH)%.h
	$(info Compilation de $< :)
	$(CC) -c $< -o $@ $(CFLAGS)

## Nettoyage ..................................................................:

clean :
	$(info Suppression de $(EXEC) et de $(OBJ) :)
	rm -f $(EXEC)
	rm -f $(OBJ)
	rm -f .fuse_hidden*

## Debugger ...................................................................:

gdb : compil
	$(info Debbugage avec $@ :)
	gdb --args ./$(EXEC) $(ARGS)