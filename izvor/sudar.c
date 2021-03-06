#include "../include/sudar.h"

void kliker_skok(void)
{
    /* Odbaceno cuvanje povratne vrednosti;
     * podrazumevano nije bio kraj skoka */
    /*int vracam = SKOK_NIJE;*/
    
    /* Odbaceno kotrljanje prilikom skoka */
    /*if (!(tipke & KRENI) && !(tipke & VRATI)){
        kotrljaj(sudar.smer);
    }*/
    
    /* Povecavanje parametra skoka */
    klik.s += UGAO_PAR * vreme.pom;
    
    /* Ako je parametar dostigao maksimum,
     * resetuje se, sto oznacava kraj skoka */
    if (klik.s >= UGAO_EXT){
        klik.s = UGAO_POC;
        /*vracam = SKOK_KRAJ;*/
    }
    
    /* Skok se modeluje sinusoidnom funkcijom;
     * kao argument se forsira vrednost od nula
     * do pi, tako da sinus vraca vrednosti koje
     * rastu od nule do jedinice, a zatim opet
     * opadaju do nule; mnozenje sa ocekivanom
     * visinom skoka daje z koordinatu klikera */
    klik.z = klik.sz + SKOK_VIS * sin(klik.s * M_PI / UGAO_EXT);
    
    /* Racunanje trenutne visine staze; ukoliko
     * je iskoceno van dimenzija, uzima se nula */
    double visina;
    int provalija = NEAKTIVNO;
    if (klik.sx < 0 || klik.sy < 0 ||
        klik.sx > STAZA_DIM-1 || klik.sy > STAZA_DIM-1){
        visina = 0;
    } else {
        switch (staza.mat[klik.sx][klik.sy]){
            case PROVALIJA:
                provalija = AKTIVNO;
            case PLOCICA:
                visina = 0;
                break;
            
            case PREPREKA1:
                visina = PREP1_VIS;
                break;
            
            case PREPREKA2:
                visina = PREP2_VIS;
                break;
        }
    }
    
    /* Zaustavljanje skoka ukoliko je dostigao
     * visinu koja odgovara tekucem polju staze;
     * ovo obradjuje slucaj naskakanja; zanemaruje
     * se ukoliko se kliker nalazi previse blizu
     * tj. ako je priljubljen uz prepreku, posto u
     * suprotnom dolazi do nepredvidjenog ponasanja */
    if (klik.z <= visina && !sudar.preblizu){
        klik.z = visina;
        klik.sz = visina;
        klik.s = UGAO_POC;
        
        /* Ukoliko se kliker sada nalazi iznad
         * provalije, igra je neuspesno zavrsena */
        if (provalija == AKTIVNO){
            game_over();
        }
        
        /* Ukoliko se kliker sada nalazi na
         * cilju, igra je uspesno zavrsena */
        if (klik.sx == staza.cilj.x &&
            klik.sy == staza.cilj.y &&
            dovoljno_blizu_cilja()){
            stanje = CESTITKE;
        }
    }
    
    /* 0 ako nije kraj, 1 ako jeste */
    /*return vracam;*/
}

void kliker_pad(void)
{
    /* Odbaceno kotrljanje prilikom pada */
    /*if (!(tipke & KRENI) && !(tipke & VRATI)){
        kotrljaj(sudar.smer);
    }*/
    
    /* Smanjivanje visine brzinom
     * koja zavisi od izvora pada */
    double brzina = (stanje == GAME_OVER) ?
                    KLIK_PADB * KLIK_PAD : KLIK_PAD;
    klik.z -= brzina * vreme.pom;
    
    /* Odredjivanje skale odbacaja */
    int odbacaj = (stanje == GAME_OVER) ?
                  KLIK_PADB : KLIK_PADB / M_PI;
    
    /* Azuriranje koordinata klikera nekoliko
     * puta, kako bi pad bio realniji, vise
     * kosi hitac nego slobodan pad */
    if (klik.kret <= AKTIVNO){
        klik.x += odbacaj * klik.px;
        klik.y += odbacaj * klik.py;
    }
    
    /* Dodatno pomeranje u slucaju kraja igre */
    if (stanje == GAME_OVER && klik.kret < KLIK_PREC){
        klik.x += klik.px;
        klik.y += klik.py;
    }
        
    /* Azuriranje brojaca */
    klik.kret++;
    
    /* Prestanak pada ukoliko je
     * dostignuta potrebna visina */
    if (klik.z <= klik.padv){
        klik.pad = NEAKTIVNO;
        klik.kret = NEAKTIVNO;
        klik.z = klik.padv;
        klik.sz = klik.padv;
    }
}

void obradi_sudare(void)
{
    /* Racunanje korektivnog faktora u odnosu
     * na znak pozicije klikera; ovo je neophodno
     * posto kliker krece od sredine pocetne plocice,
     * sto znaci da prvu susednu dostigne nakon sto
     * predje pola duzine, a za naredne predje celu */
    int korx = (klik.x > 0) ? PLOC_DIM/2 : -PLOC_DIM/2;
    int kory = (klik.y > 0) ? PLOC_DIM/2 : -PLOC_DIM/2;
    
    /* Relativne koordinate na stazi dabijaju se
     * tako sto se trenutne apsolutne podele duzinom
     * plocice (skaliranje), cemu se zatim doda
     * polovina dimenzije staze, posto je pocetna
     * aps. koord. (0, 0), a rel. (dim/2, dim/2) */
    int starx = (int)(klik.x + korx)
                / PLOC_DIM + STAZA_DIM/2;
    int stary = (int)(klik.y + kory)
                / PLOC_DIM + STAZA_DIM/2;
    
    /* Racunanje novih koordinata na stazi
     * po istom principu kao za stare */
    int novx = (int)(klik.x + klik.px + korx)
                / PLOC_DIM + STAZA_DIM/2;
    int novy = (int)(klik.y + klik.py + kory)
                / PLOC_DIM + STAZA_DIM/2;
    
    /* Ukoliko se kliker sada nalazi iznad provalije
     * ili je mozda izasao izvan dimenzija terena (to
     * je kao ambis), igra je neuspesno zavrsena */
    if ((novx < 0 || novy < 0 || novx > STAZA_DIM-1
        || novy > STAZA_DIM-1 || staza.mat[novx][novy]
        == PROVALIJA) && klik.z == 0){
        game_over();
        
        /* Azuriranje koordinata klikera */
        klik.x += klik.px;
        klik.y += klik.py;
        return;
    }
    
    /* Racunanje kako prethodne, tako
     * i nove visine polja staze */
    double svis = nadji_visinu(starx, stary);
    double nvis = nadji_visinu(novx, novy);
    
    /* Ukoliko je visina novog polja manja od
     * starog, a kliker se nalazi na vecoj visini,
     * pada dokle je potrebno; ovo doprinosi vernosti
     * simulacije, ali ipak ne uspeva da sasvim resi
     * problem coskova, kao i ivica visih polja uopsteno,
     * tako da je situacija nesavrsena po tom pitanju;
     * desava se da se prilikom pada mali deo klikera
     * presece sa preprekom; ovo ne utice na samu igru,
     * ali stoji da nije vizuelno prijemcivo; pokazalo
     * se, medjutim, kao tesko za potpunu popravku */
    if (nvis < svis && klik.z > nvis){
        klik.pad = AKTIVNO;
        klik.padv = nvis;
    }
    
    /* Dodavanje poluprecnika klikera na stari
     * korektivni faktor; dodatna korekcija je
     * neophodna zarad realnijeg priljubljivanja
     * uz prepreku; bez ovoga se kliker zakuca tek
     * kada mu centar udari u prepreku, a to je
     * prekasno, tako da se mora gledati radijus */
    korx += (klik.px > 0) ? KLIK_RAD : -KLIK_RAD;
    kory += (klik.py > 0) ? KLIK_RAD : -KLIK_RAD;
    
    /* Racunanje korigovanih novih koordinata
     * na stazi po istom principu kao dosad */
    klik.sx = (int)(klik.x + klik.px + korx)
                / PLOC_DIM + STAZA_DIM/2;
    klik.sy = (int)(klik.y + klik.py + kory)
                / PLOC_DIM + STAZA_DIM/2;
    
    /* Racunanje korigovane nove visine staze */
    nvis = nadji_visinu(klik.sx, klik.sy);
    
    /* Ukoliko je visina novog polja veca od
     * starog, a kliker se nalazi na manjoj
     * visini, odustaje se od pokreta, ali se
     * pamti da je priljubljen uz prepreku; isto
     * se radi ukoliko trenutne stare visinske
     * koordinate ne odgovaraju novim, posto bi
     * u suprotnom greska u racunu prilikom
     * korekcije dovela do pogresnog ponasanja */
    if ((nvis > svis || sudar.svis != nvis)
        && klik.z < nvis){
        sudar.preblizu = AKTIVNO;
        return;
    } else {
        sudar.preblizu = NEAKTIVNO;
    }
    
    /* Ukoliko se kliker sada nalazi na
     * cilju, igra je uspesno zavrsena */
    if (klik.sx == staza.cilj.x &&
        klik.sy == staza.cilj.y &&
        klik.z == nvis &&
        dovoljno_blizu_cilja()){
        stanje = CESTITKE;
    }
    
    /* Azuriranje koordinata klikera */
    klik.x += klik.px;
    klik.y += klik.py;
}

double nadji_visinu(int x, int y)
{
    /* Postavljanje povratne vrednosti;
     * na pocetku se pretpostavlja nula */
    double vracam = 0;
    
    /* Popravka, ukoliko je neophodna */
    switch (staza.mat[x][y]){
        case PREPREKA1:
            vracam = PREP1_VIS;
            break;
        
        case PREPREKA2:
            vracam = PREP2_VIS;
            break;
    }
    
    /* Vracanje izracunate vrednosti */
    return vracam;
}

int dovoljno_blizu_cilja(void)
{
    /* Racunanje realnih koordinata cilja */
    int realx = (staza.cilj.x - STAZA_DIM/2) * PLOC_DIM;
    int realy = (staza.cilj.y - STAZA_DIM/2) * PLOC_DIM;
    
    /* Racunanje udaljenosti klikera od cilja */
    GLdouble udalj = sqrt((klik.x-realx)*(klik.x-realx) +
                          (klik.y-realy)*(klik.y-realy));
    
    /* Ukoliko je kliker dovoljno blizu sredine
     * cilja, proglasava se uspesan kraj igre;
     * prostom proverom matrice dogadja se da se
     * igra zavrsi cim kliker veoma malo, ako uopste,
     * zagazi na cilj, sto je ipak prerano */
    return udalj <= M_PI * KLIK_RAD;
}

void oko_iznad(void)
{
    /* Slicno kao kod resetovanja, oko se
     * translira, samo ovoga puta po Dekartovim
     * koordinatama, u tacku iznad klikera, dakle
     * iz (oko.x, oko.y, oko.z) u, neka bude
     * tolika visina, (klik.x, klik.y, 10) */
    GLdouble t_x = klik.x - oko.x;
    GLdouble t_y = klik.y - oko.y;
    GLdouble t_z = OKO_PAD - oko.z;
    
    /* Normalizacija izracunatog vektora
     * deljenjem sa njegovom duzinom i jos
     * mnozenjem sa parametrom reseta */
    double duz = sqrt(t_x*t_x + t_y*t_y + t_z*t_z)
                 * OKO_PADP / vreme.pom;
    t_x /= duz; t_y /= duz; t_z /= duz;
    
    /* Translacija se proglasava gotovom,
     * a normale se resetuju */
    oko.iznad = NEAKTIVNO;
    norm.x = NORM_X;
    norm.y = NORM_Y;
    norm.z = NORM_Z;
    
    /* Translacija po izracunatom vektoru,
     * ali samo ako je vrednost pomeraja
     * manja od udaljenosti bitnih tacaka */
    if (fabs(t_x) < fabs(klik.x - oko.x)){
        oko.x += t_x;
        oko.iznad = AKTIVNO;
    } else {
        oko.x = klik.x;
    }
    
    if (fabs(t_y) < fabs(klik.y - oko.y)){
        oko.y += t_y;
        oko.iznad = AKTIVNO;
    } else {
        oko.y = klik.y;
    }
    
    if (fabs(t_z) < fabs(OKO_PAD - oko.z)){
        oko.z += t_z;
        oko.iznad = AKTIVNO;
    } else {
        oko.z = OKO_PAD;
    }
    
    /* Postavljanje novih koordinata normale
     * kako bi se resila cinjenica da pravac
     * pogleda neprihvatljivo postaje kolinearan
     * sa normalom, bilo na kraju animacije,
     * bilo u toku (tada nisu istog znaka
     * tekuca i sacuvana vrednost); bez ovoga
     * bi kamera menjala orijentaciju u toku
     * pada ili bi se skroz zacrnela */
    if (!oko.iznad ||
        norm.nx * (klik.x-oko.x) <= 0 ||
        norm.ny * (klik.y-oko.y) <= 0){
        norm.x = norm.nx;
        norm.y = norm.ny;
        norm.z = NEAKTIVNO;
    }
}

void game_over(void)
{
    /* Azuriranje stanja igre */
    stanje = GAME_OVER;
    
    /* Kliker pada u ambis */
    klik.pad = AKTIVNO;
    klik.padv = KLIK_PADV;
    
    /* Oko se posebno krece */
    oko.iznad = AKTIVNO;
    
    /* Pamcenje podataka za
     * nov upravni vektor */
    norm.nx = klik.x - oko.x;
    norm.ny = klik.y - oko.y;
}
