# Ime programa i izvrsive datoteke je klikerche
PROGRAM = klikerche
# Koristi se prevodilac GCC; jezik je C
CC      = gcc
# Zastavice za prevodjenje: ukljucuju se
# debag rezim, ANSI standard, sva upozorenja,
# a biblioteke se traze i na posebnim putevima
ZAST    = -g -ansi -Wall -Wextra -L/usr/X11R6/lib -L/usr/pkg/lib
# Spisak datoteka sa glavnim kodom
PROG    = izvor/main.c izvor/osnov.c izvor/prikaz.c izvor/vreme.c izvor/tipke.c izvor/oko.c izvor/kliker.c izvor/staza.c izvor/cuvanje.c izvor/meni.c
# Spisak korisnicki definisanih zaglavlja
ZAV     = include/main.h include/osnov.h include/prikaz.h include/vreme.h include/tipke.h include/oko.h include/kliker.h include/staza.h include/cuvanje.h include/meni.h
# Spisak biblioteka koje treba povezati
BIBL    = -lglut -lGLU -lGL -lm -L/usr/X11R6/lib -L/usr/pkg/lib

# Pravilo za prevodjenje programa
$(PROGRAM): $(PROG) $(ZAV)
	$(CC) $(ZAST) -o $(PROGRAM) $(PROG) $(BIBL)

# Spisak pomocnih pravila
.PHONY: run makerun clean

# Pravilo za pokretanje prevedenog programa u pozadini
run:
	./$(PROGRAM) &

# Pravilo za istovremeno prevodjenje i pokretanje
makerun:
	make && make run

# Pravilo za ciscenje direktorijuma projekta
clean:
	rm -f *~ izvor/*~ include/*~ slike/*~
