PROGRAM = klikerche
CC      = gcc
FLAGS   = -Wall -Wextra
LIBS    = -lglut -lGLU -lGL -lm

$(PROGRAM): src/main.c
	$(CC) $(FLAGS) -o $(PROGRAM) src/main.c $(LIBS)

.PHONY: run makerun clean

run:
	./$(PROGRAM) &

makerun:
	make
	make run

clean:
	rm -f *~ src/*~ screenshots/*~
