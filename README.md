#### RG31-klikerche

## Klikerče :globe_with_meridians:
Projekat na kursu Računarska grafika. Korisnik upravlja klikerom koji može da se proizvoljno pomera po generisanom terenu odnosno podlozi, sa ciljem ispunjenja još nedefinisanog kriterijuma.

## Makefile :memo:
Podrazumevana upotreba mejkfajla je iz konzole, nakon pozicioniranja u koreni direktorijum projekta.

Prevođenje programa: `make`.

Pokretanje prevedenog programa: `make run`.

Istovremeno prevođenje i pokretanje: `make makerun`.

Čišćenje direktorijuma: `make clean`.

Pakovanje direktorijuma: `make dist`.

Za komande sa prevođenjem neophodno je imati kompajler gcc, dok se u include putu moraju nalaziti zaglavlje GL/glut.h i ostali relevantni činioci biblioteke Glut aplikativnog korisničkog interfejsa OpenGL.

Za slučaj da to u trenutku nije dostupno, u direktorijumu projekta nalazi se i izvršiva verzija programa, prevedena na 32-bitnoj verziji operativnog sistema Ubuntu 12.04.5 LTS (Precise Pangolin), pa je moguće probati direktno pokretanje komandom `make run` ili nekom drugom koja odgovara radnom sistemu (na Ubuntuu `./klikerche`).

## Komande :video_game:
Zasad su sve komande neosetljive na veličinu slova.

Tipka | Događaj
----- | ------
<kbd>W</kbd> | kamera gore
<kbd>A</kbd> | kamera levo
<kbd>S</kbd> | kamera dole
<kbd>D</kbd> | kamera desno
<kbd>R</kbd> | kamera reset

