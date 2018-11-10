PROGRAM = klikerche
CC      = gcc
FLAGS   = -Wall
LIBS    = -lglut -lGLU -lGL -lm

$(PROGRAM): main.c
	$(CC) $(FLAGS) -o $(PROGRAM) main.c $(LIBS)

.PHONY: run makerun clean dist

run:
	./$(PROGRAM)

makerun:
	make
	make run

clean:
	rm -f *~

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 RG31-$(PROGRAM)
