PROGRAM = klikerche
CC      = gcc
ZAST    = -Wall -Wextra
PROG    = src/main.c src/osnov.c src/oko.c src/kliker.c
BIBL    = -lglut -lGLU -lGL -lm

$(PROGRAM): src/main.c
	$(CC) $(ZAST) -o $(PROGRAM) $(PROG) $(BIBL)

.PHONY: run makerun clean

run:
	./$(PROGRAM) &

makerun:
	make
	make run

clean:
	rm -f *~ src/*~ screenshots/*~
