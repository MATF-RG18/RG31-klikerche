#include "../include/cuvanje.h"

/* Odbaceni nacin promene rezima prikaza
 * pomocu indikatora u korist ugradjene
 * FreeGLUT-ove fje i indikatora */
/*void fullscreen(void)
{
    if (fulskrin == AKTIVAN){
        glutReshapeWindow(PROZ_DIM, PROZ_DIM);
    } else {
        glutFullScreen();
    }
    
    fulskrin = !fulskrin;
}*/

void sacuvaj_igru(void)
{
    /* Otvaranje fajla sa sacuvanom
     * igrom u rezimu za pisanje */
    FILE* fajl = fopen(SAVEGAME, "w");
    
    /* U zavisnosti od uspeha otvaranja fajla,
     * aktivira se ispis odgovarajuce poruke */
    por.vreme = vreme.novo;
    if (fajl == NULL){
        por.poruka = NEUSPESNO_CUVANJE;
        return;
    } else {
        por.poruka = USPESNO_CUVANJE;
    }
    
    /* Ne postoji serijalizacija u C-u,
     * ali se cuvanje igre moze simulirati
     * zapisivanjem bitnih promenljivih */
    
    /* Upisivanje parametara oka */
    fprintf(fajl, "%lf %lf %lf\n", oko.r, oko.phi, oko.theta);
    
    /* Upisivanje razlika oka */
    /*fprintf(fajl, "%d %d %d\n", raz.r, raz.phi, raz.theta);*/
    
    /* Upisivanje polozaja klikera */
    fprintf(fajl, "%lf %lf %lf\n", klik.x, klik.y, klik.z);
    
    /* Upisivanje skoka i rotacije */
    /*fprintf(fajl, "%lf %lf\n", klik.s, rot.u);*/
    
    /* Od tipki nista nije bitno */
    /*int skok = tipke & SKOK;*/
    
    /* Upisivanje parametra skoka, stanja
     * indikatora, kao i aktivnog proteklog
     * vremena zarad korektnosti stoperice */
    fprintf(fajl, "%lf %d %d %d\n", klik.s, stanje,
            glutGet(GLUT_FULL_SCREEN),
            vreme.novo - stopw.pocetak - vreme.pauza);
    
    /* Upisivanje matrice rotacije; iako je u pitanju
     * matrica dimenzija 4x4, vredna cuvanja je samo
     * njena gornja leva podmatrica 3x3; naime, u pitanju
     * je matrica u homogenim koordinatama, i to dodatno
     * homogenizovanim, pri cemu ne postoji translatorna
     * komponenta, posto je posredi cista rotacija, tako
     * da su poslednji red i kolona fiksno (0, 0, 0, 1) */
    int i, kor = (int)sqrt(MAT_DIM);
    for (i = 0; i < kor-1; i++){
        int j;
        for (j = 0; j < kor-2; j++){
            fprintf(fajl, "%lf ", rot.mat[i*kor+j]);
        }
        fprintf(fajl, "%lf\n", rot.mat[i*kor+j]);
    }
    
    /* Upisivanje dokumentacionih komentara
     * u fajl pre njegovog zatvaranja */
    fputc('\n', fajl);
    fprintf(fajl, "# Sacuvana igra sadrzi sest redova;\n");
    fprintf(fajl, "# detalji se mogu naci u samom kodu;\n");
    fprintf(fajl, "# prvi: sferni parametri oka/kamere;\n");
    /*fprintf(fajl, "# drugi: razlike oka, za resetovanje;\n");*/
    fprintf(fajl, "# drugi: polozaj igracevog klikera;\n");
    fprintf(fajl, "# treci: parametar skoka, indikator\n");
    fprintf(fajl, "# stanja, rezim prikaza, proteklo vreme;\n");
    fprintf(fajl, "# ostali: matrica rotacije/kotrljanja\n");
    
    /* Zatvaranje fajla */
    fclose(fajl);
}

void ucitaj_igru(void)
{
    /* Otvaranje fajla sa sacuvanom
     * igrom u rezimu za citanje */
    FILE* fajl = fopen(SAVEGAME, "r");
    
    /* U zavisnosti od uspeha otvaranja fajla
     * i provere postojanja neophodnih podataka,
     * aktivira se ispis odgovarajuce poruke;
     * stdio nazalost nije previse precizan
     * kada je u pitanju provera tipova ulaznih
     * podataka, tako da je za test odabran
     * pocetak komentara, posto dolazenje dotle
     * kazuje da su predjeni zahtevani brojevi */
    por.vreme = vreme.novo;
    char test[TEST_MAX];
    if (fajl == NULL || fscanf(fajl, "%*f %*f %*f\n \
                            %*f %*f %*f\n \
                            %*f %*d %*d %*d\n \
                            %*f %*f %*f\n \
                            %*f %*f %*f\n \
                            %*f %*f %*f\n\n \
                            %s", test) == EOF ||
                            strcmp(test, "#")){
        por.poruka = NEUSPESNO_CITANJE;
        return;
    } else {
        por.poruka = USPESNO_CITANJE;
    }
    
    /* Resetovanje offseta, koji je zbog
     * provere pomeren na kraj fajla */
    rewind(fajl);
    
    /* Citanje parametara oka */
    fscanf(fajl, "%lf %lf %lf", &oko.r, &oko.phi, &oko.theta);
    
    /* Citanje razlika oka */
    /*fscanf(fajl, "%d %d %d", &raz.r, &raz.phi, &raz.theta);*/
    
    /* Citanje polozaja klikera */
    fscanf(fajl, "%lf %lf %lf", &klik.x, &klik.y, &klik.z);
    
    /* Citanje skoka i rotacije */
    /*fscanf(fajl, "%lf %lf", &klik.s, &rot.u);*/
    
    /* Citanje parametra skoka, stanja
     * indikatora i proteklog vremena */
    int prikaz, proteklo;
    fscanf(fajl, "%lf %d %d %d", &klik.s,
                 &stanje, &prikaz, &proteklo);
    
    /* Citanje matrice rotacije */
    int i, kor = (int)sqrt(MAT_DIM);
    for (i = 0; i < kor-1; i++){
        int j;
        for (j = 0; j < kor-1; j++){
            fscanf(fajl, "%lf", &rot.mat[i*kor+j]);
        }
    }
    
    /* Zatvaranje fajla */
    fclose(fajl);
    
    /* Promena rezima prikaza u slucaju
     * da se stari i ucitani razlikuju */
    if (prikaz != glutGet(GLUT_FULL_SCREEN)){
        glutFullScreenToggle();
    }
    
    /* Manipulacija parametrima vremena kako
     * bi stoperica ostala korektna; staro vreme
     * i vreme pauze postavljaju se na nulu, dok
     * se pocetak stoperice postavlja na vreme
     * 'proteklo' milisekundi manje od trenutnog;
     * ovime se zarad elegantnijeg koda dobija
     * mogucnost negativnog pocetnog vremena,
     * ali to ne smeta pri izvrsavanju */
    stopw.starov = NEAKTIVNO;
    vreme.pauza = NEAKTIVNO;
    stopw.pocetak = vreme.novo - proteklo;
    
    /* Tekucim tipkama menja se stanje
     * tako sto se zanemaruje resetovanje
     * oka koje je potencijalno u toku */
    tipke &= ~RESET;
}
