#### RG31-klikerche

## Klikerče :globe_with_meridians:
Projekat na kursu Računarska grafika. Korisnik upravlja klikerom koji može da se proizvoljno pomera po generisanom terenu odnosno stazi sa preprekama, sa ciljem ispunjenja još nedefinisanog kriterijuma.

Detalji u vezi sa tokom razvoja projekta – nedeljni izveštaji, kao i snimci ekrana trenutnog stanja programa (gif format radi bolje ilustracije interaktivnosti, napravljen pomoću aplikacije [recordMyDesktop](http://recordmydesktop.sourceforge.net/about.php) i [onlajn konvertora](http://www.videotogifs.com/ogv-to-gif.html)) – mogu se pronaći na wiki stranicama repozitorijuma, dostupnim u meniju repozitorijuma ili direktno [ovde](https://github.com/MATF-RG18/RG31-klikerche/wiki).

## Podešavanje :memo:
Nakon kloniranja (`git clone https://github.com/MATF-RG18/RG31-klikerche`) ili nekog drugog načina preuzimanja repozitorijuma, program je moguće podesiti (prevesti i/ili pokrenuti) ručno ili uz pomoć mejkfajla.

Podrazumevana upotreba mejkfajla je iz konzole, nakon pozicioniranja u koreni direktorijum projekta.

Prevođenje programa: `make`.

Pokretanje prevedenog programa: `make run`.

Istovremeno prevođenje i pokretanje: `make makerun`.

Čišćenje direktorijuma: `make clean`.

Za komande sa prevođenjem neophodno je imati kompajler [gcc](https://gcc.gnu.org/) (podrazumevano dostupan kao [naredba ljuske](http://man7.org/linux/man-pages/man1/gcc.1.html) na većini distribucija Linuksa), dok se u include putu moraju nalaziti zaglavlje GL/glut.h i ostali relevantni činioci biblioteke [FreeGLUT](http://freeglut.sourceforge.net/) aplikativnog korisničkog interfejsa [OpenGL](https://www.opengl.org/). Nju je moguće podesiti komandom poput `sudo apt-get install binutils-gold freeglut3 freeglut3-dev` za Ubuntu.

U slučaju da bitne biblioteke u trenutku nisu dostupne, u direktorijumu projekta nalazi se i izvršiva verzija programa, prevedena na 32-bitnom izdanju operativnog sistema [Ubuntu 12.04.5 LTS (Precise Pangolin)](http://releases.ubuntu.com/12.04/), pa je moguće probati direktno pokretanje komandom `make run` ili nekom drugom koja odgovara radnom sistemu, kao što je `./klikerche` u slučaju Ubuntua.

## Komande :video_game:
Kako je program interaktivne prirode, ugrađeni su mnogi odgovori na događaje (korisničkog unosa preko) tastature. Sledi tabelarni prikaz implementiranih komandi, uz napomenu da su sve neosetljive na veličinu slova odnosno <kbd>Caps Lock</kbd>.

Tipka | Događaj
----- | ------
<kbd>W</kbd> <kbd>S</kbd> | vertikalno oko
<kbd>A</kbd> <kbd>D</kbd> | horizontalno oko
<kbd>Q</kbd> <kbd>E</kbd> | udaljenost oka
<kbd>R</kbd> | resetovanje oka
<kbd>Esc</kbd> | izlaz iz igre
