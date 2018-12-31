#### RG31-klikerche

## Klikerče :globe_with_meridians:
Projekat na kursu Računarska grafika. Korisnik upravlja klikerom koji se na komande tastature kreće po generisanom terenu odnosno stazi sa preprekama, sa namerom uspešnog dolaska do cilja – kraja staze.

Ukratko, projekat uključuje većinu gradiva obuhvaćenog vežbama na već pomenutom kursu, kao što je: crtanje 2D i 3D primitiva, provera dubine (depth tj. z-bafer), tempirana animacija, upravljanje pogledom (interaktivno postavljanje oka i perspektive), upotreba korisnički kreiranih matrica transformacija, osvetljenje, materijali, liste, tastatura, miš, ispis teksta, parametrizovane površi, teksture... Za bolji uvid preporučuje se analiza koda i proba same igre. :smiley:

Finiji detalji u vezi sa tokom razvoja projekta – nedeljni izveštaji, kao i snimci ekrana trenutnog stanja programa, u gif formatu radi boljeg prikaza interaktivnosti, napravljenom pomoću aplikacije [recordMyDesktop](http://recordmydesktop.sourceforge.net/about.php) i [onlajn konvertora](http://www.videotogifs.com/ogv-to-gif.html) – mogu se pronaći na wiki stranicama repozitorijuma, dostupnim na meniju glavne stranice ili neposredno [ovde](https://github.com/MATF-RG18/RG31-klikerche/wiki).

## Podešavanje :memo:
Nakon kloniranja (`git clone https://github.com/MATF-RG18/RG31-klikerche`) ili nekog drugog načina preuzimanja repozitorijuma, program je moguće podesiti (prevesti i/ili pokrenuti) ručno ili uz pomoć mejkfajla.

Podrazumevana upotreba mejkfajla je iz konzole, nakon pozicioniranja u koreni direktorijum projekta.

Prevođenje programa: `make`.

Pokretanje prevedenog programa: `make run`.

Istovremeno prevođenje i pokretanje: `make makerun`.

Čišćenje direktorijuma: `make clean`.

Za prevođenje je neophodno imati kompajler [GCC](https://gcc.gnu.org/), podrazumevano dostupan kao [naredba ljuske](http://man7.org/linux/man-pages/man1/gcc.1.html) na većini distribucija Linuksa, dok se u include putu moraju nalaziti relevantni činioci biblioteke [FreeGLUT](http://freeglut.sourceforge.net/) aplikativnog programskog interfejsa [OpenGL](https://www.opengl.org/). Za učitavanje tekstura korišćena je biblioteka [SOIL](http://www.lonesock.net/soil.html), koju je moguće posebno preuzeti i prevesti, a koja se može i prosto preuzeti i instalirati kao aplikacija. Sve neophodno, kada su bibliteke u pitanju, moguće je podesiti komandom terminala poput `sudo apt-get install binutils-gold freeglut3 freeglut3-dev libsoil-dev` za Ubuntu.

Ukoliko iz bilo kog razloga pomenute biblioteke u trenutku nisu dostupne, u direktorijumu projekta nalazi se i izvršiva verzija programa, prevedena na 32-bitnom izdanju operativnog sistema [Ubuntu 12.04.5 LTS (Precise Pangolin)](http://releases.ubuntu.com/12.04/), pa je moguće probati direktno pokretanje komandom `make run` ili nekom drugom koja odgovara radnom sistemu, kao što je `./klikerche` u slučaju Ubuntua. Ovaj metod provereno radi na nekoliko drugih distribucija Linuksa, samo je neophodno prvo dodeliti sebi pravo izvršavanja komandom poput `chmod u+x klikerche` za većinu distribucija.

## Komande :video_game:
Kako je program interaktivne prirode, ugrađeni su mnogi odgovori na događaje (korisničkog unosa preko) tastature. Sledi tabelarni prikaz implementiranih komandi, uz napomenu da su sve neosetljive na veličinu slova odnosno <kbd>Caps Lock</kbd>.

Tipka | Događaj | Tipka | Događaj
----- | ------ | ----- | ------
<kbd>W</kbd> <kbd>S</kbd> | kretanje klikera | <kbd>Q</kbd> <kbd>E</kbd> | udaljenost oka
<kbd>A</kbd> <kbd>D</kbd> | okretanje oka | <kbd>Z</kbd> <kbd>X</kbd> | visina pogleda
<kbd>R</kbd> | resetovanje oka | <kbd>Space</kbd> | skok
<kbd>F</kbd> | fullscreen | <kbd>G</kbd> | pokretanje i restart
<kbd>K</kbd> | čuvanje igre | <kbd>L</kbd> | čitanje igre
<kbd>P</kbd> | pauza | <kbd>Esc</kbd> | izlaz iz igre

Za ljubitelje miša, ugrađene su mnoge paralelne komande koje omogućuju igru uz minimalnu upotrebu tastature. Naime, preko miša jedino nije moguće ići unazad i skočiti, s tim što, kada se uzme u obzir da se kretanje unazad može izvesti okretanjem za pola kruga, a zatim kretanjem unapred, prvo ograničenje i nije veliki problem. Napomena: pojedini sistemi ne generišu precizno događaje miša, tako da se ipak preporučuje upotreba tastature.

Taster | Događaj
----- | ------
prevlačenje miša | (o)kretanje oka
kotrljanje točka | udaljenost oka
desni klik | meni sa opcijama
