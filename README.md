#### RG31-klikerche

## Klikerče :globe_with_meridians:
Projekat na kursu Računarska grafika. Korisnik upravlja klikerom koji se na komande korisnika kreće po generisanom terenu odnosno stazi sa preprekama, sa namerom uspešnog dolaska do cilja – kraja staze.

Ukratko, projekat uključuje većinu gradiva obuhvaćenog vežbama na već pomenutom kursu, kao što je: crtanje 2D i 3D primitiva, provera dubine (depth tj. z-bafer), tempirana animacija, upravljanje pogledom (interaktivno postavljanje tačke i vektora pogleda), osvetljenje, materijali, liste. Do završetka projekta, što se očekuje do Nove godine ili Božića, planirano je uključivanje ostatka gradiva: površi određene trouglovima i normalama, providnost, ispis teksta, teksture.

Finiji detalji u vezi sa tokom razvoja projekta – nedeljni izveštaji, kao i snimci ekrana trenutnog stanja programa, u gif formatu radi boljeg prikaza interaktivnosti, napravljenom pomoću aplikacije [recordMyDesktop](http://recordmydesktop.sourceforge.net/about.php) i [onlajn konvertora](http://www.videotogifs.com/ogv-to-gif.html) – mogu se pronaći na wiki stranicama repozitorijuma, dostupnim na meniju glavne stranice ili neposredno [ovde](https://github.com/MATF-RG18/RG31-klikerche/wiki).

## Podešavanje :memo:
Nakon kloniranja (`git clone https://github.com/MATF-RG18/RG31-klikerche`) ili nekog drugog načina preuzimanja repozitorijuma, program je moguće podesiti (prevesti i/ili pokrenuti) ručno ili uz pomoć mejkfajla.

Podrazumevana upotreba mejkfajla je iz konzole, nakon pozicioniranja u koreni direktorijum projekta.

Prevođenje programa: `make`.

Pokretanje prevedenog programa: `make run`.

Istovremeno prevođenje i pokretanje: `make makerun`.

Čišćenje direktorijuma: `make clean`.

Za komande sa prevođenjem neophodno je imati kompajler [GCC](https://gcc.gnu.org/), podrazumevano dostupan kao [naredba ljuske](http://man7.org/linux/man-pages/man1/gcc.1.html) na većini distribucija Linuksa, dok se u include putu moraju nalaziti zaglavlje GL/glut.h i ostali relevantni činioci biblioteke [FreeGLUT](http://freeglut.sourceforge.net/) aplikativnog korisničkog interfejsa [OpenGL](https://www.opengl.org/). Sve neophodno moguće je podesiti komandom poput `sudo apt-get install binutils-gold freeglut3 freeglut3-dev` za Ubuntu.

Ukoliko iz bilo kog razloga bitne biblioteke u trenutku nisu dostupne, u direktorijumu projekta nalazi se i izvršiva verzija programa, prevedena na 32-bitnom izdanju operativnog sistema [Ubuntu 12.04.5 LTS (Precise Pangolin)](http://releases.ubuntu.com/12.04/), pa je moguće probati direktno pokretanje komandom `make run` ili nekom drugom koja odgovara radnom sistemu, kao što je `./klikerche` u slučaju Ubuntua. Ovaj metod provereno radi na nekoliko drugih distribucija Linuksa, samo je neophodno prvo dodeliti sebi pravo izvršavanja komandom poput `chmod u+x klikerche` za većinu distribucija.

## Komande :video_game:
Kako je program interaktivne prirode, ugrađeni su mnogi odgovori na događaje (korisničkog unosa preko) tastature. Sledi tabelarni prikaz implementiranih komandi, uz napomenu da su sve neosetljive na veličinu slova odnosno <kbd>Caps Lock</kbd>.

Tipka | Događaj | Tipka | Događaj
----- | ------ | ----- | ------
<kbd>W</kbd> <kbd>S</kbd> | kretanje klikera | <kbd>Q</kbd> <kbd>E</kbd> | udaljenost oka
<kbd>A</kbd> <kbd>D</kbd> | okretanje oka | <kbd>Z</kbd> <kbd>X</kbd> | visina pogleda
<kbd>R</kbd> | resetovanje oka | <kbd>Space</kbd> | skok
<kbd>F</kbd> | fullscreen | <kbd>G</kbd> | debag režim
<kbd>K</kbd> | čuvanje igre | <kbd>L</kbd> | čitanje igre
<kbd>P</kbd> | pauza | <kbd>Esc</kbd> | izlaz iz igre
