# Variables ...................................................................:

## Compilateur ................................................................:

CC = gcc
CFLAGS = -g3 -Wall -pthread
LDFLAGS = -lm -pthread
LIBS = -L./lib -lnm
INCLUDES =  -I./lib/include

## Structure du projet ........................................................:

EXEC = bin/seaofdevs
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = lib/include/

SRC = $(shell find $(SRC_PATH)*.c)
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

## Autres .....................................................................:

ARGS = file/fichier.sod

## Lancement ..................................................................:

run : compil 
	$(info Lancement de $(EXEC) :)
	./$(EXEC) $(ARGS)

## Compilation ................................................................:

compil : $(EXEC)

$(EXEC) : $(OBJ)
	$(info Édition des liens dans $(EXEC) :)
	$(CC) $^ $(INCLUDES) -o $(EXEC) $(LDFLAGS) $(LIBS)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(INC_PATH)%.h
	$(info Compilation de $< :)
	$(CC) -c $< -o $@ $(CFLAGS)

## Nettoyage ..................................................................:

clean :
	$(info Suppression de $(EXEC) et de $(OBJ) :)
	rm -f $(EXEC)
	rm -f $(OBJ)

## Debugger ...................................................................:

debug : compil
	$(info Debbugage avec $@ :)
	gdb --args ./$(EXEC) $(ARGS)

## Archivage ..................................................................:

tar :
	tar -zcvf ../CHIKAR_Soufiane-LEFEBVRE_Theo.tar.gz *
