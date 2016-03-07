CC=gcc
FLAGS=-Wall -lGL -lGLU -lglut 
OBJ= main.o menu.o modif.o 
SRC=(OBJ:.o=.c)

exe:	$(OBJ)
	$(CC) $^ -o $@ $(FLAGS)

%.o:	%.c
	$(CC) $^ -c 
clean:	
	rm *.o *~ *# 
