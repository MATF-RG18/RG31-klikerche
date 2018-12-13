# Ime programa i izvrsive datoteke je klikerche
PROGRAM = klikerche
# Koristi se prevodilac gcc, jezik je C
CC      = gcc
# Zastavice za prevodjenje; ukljucuju se
# debag rezim, ANSI standard, sva upozorenja,
# a biblioteke se traze i na posebnim putevima
ZAST    = -g -ansi -Wall -Wextra -L/usr/X11R6/lib -L/usr/pkg/lib
# Spisak datoteka sa glavnim kodom
PROG    = izvor/main.c izvor/osnov.c izvor/kolpom.c izvor/kolbek.c izvor/tajmer.c izvor/dogadjaji.c izvor/oko.c izvor/kliker.c
# Spisak korisnicki definisanih zaglavlja
ZAV     = include/main.h include/osnov.h include/kolpom.h include/kolbek.h include/tajmer.h include/dogadjaji.h include/oko.h include/kliker.h
# Spisak biblioteka koje treba povezati
BIBL    = -lglut -lGLU -lGL -lm -L/usr/X11R6/lib -L/usr/pkg/lib

# Pravilo za prevodjenje programa
$(PROGRAM): $(PROG) $(ZAV)
	$(CC) $(ZAST) -o $(PROGRAM) $(PROG) $(BIBL)

# Spisak pomocnih pravila
.PHONY: run makerun clean

# Pravilo za pokretanje prevedenog programa
run:
	./$(PROGRAM) &

# Pravilo za istovremeno prevodjenje i pokretanje
makerun:
	make
	make run

# Pravilo za ciscenje direktorijuma projekta
clean:
	rm -f *~ izvor/*~ include/*~ slike/*~
