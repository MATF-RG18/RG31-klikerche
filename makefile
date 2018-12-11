PROGRAM = klikerche
CC      = gcc
ZAST    = -g -ansi -Wall -Wextra -L/usr/X11R6/lib -L/usr/pkg/lib
PROG    = izvor/main.c izvor/osnov.c izvor/kolbek.c izvor/oko.c izvor/kliker.c
ZAV     = izvor/osnov.h izvor/kolbek.h izvor/oko.h izvor/kliker.h
BIBL    = -lglut -lGLU -lGL -lm

$(PROGRAM): $(PROG) $(ZAV)
	$(CC) $(ZAST) -o $(PROGRAM) $(PROG) $(BIBL)

.PHONY: run makerun clean

run:
	./$(PROGRAM) &

makerun:
	make
	make run

clean:
	rm -f *~ izvor/*~ slike/*~
