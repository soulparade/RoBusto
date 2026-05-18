#include <Servo.h>
#define DIM 10
#define DIMMOVIMENTI 16
#define DIMCENTRALE 4

#define PolsoRiposo 90
#define MotoreTestaRiposo 135
#define ColloCentraleRiposo 100  // da contorllare effettivamente
#define ColloDxRiposo 100        // da contorllare effettivamente
#define ColloSxRiposo 100        // da contorllare effettivamente

Servo Pollice;
Servo Indice;
Servo Medio;
Servo Anulare;
Servo Mignolo;
Servo Polso;
Servo Bicipite;
Servo SpallaDxSx;
Servo SpallaSuGiu;
Servo Clavicola;
Servo ColloDx;
Servo ColloSX;
Servo ColloCentrale;
Servo MotoreTesta;

String movimenti[DIMMOVIMENTI] = { /*0*/ "apri\n", /*1*/ "chiudi\n", /*2*/ "vittoria\n", /*3*/ "ok\n", /*4*/ "saluto\n", /*5*/ "apribicipite\n", /*6*/ "chiudibicipite\n", /*7*/ "spallaadx\n", /*8*/ "spallaasx\n", /*9*/ "spallasu\n", /*10*/ "spallagiu\n", /*11*/ "apribraccio\n", /*12*/ "chiudibraccio\n", /*13*/ "assenso\n", /*14*/ "diniego\n", /*15*/ "salutobraccio\n" };
String Pos;

int VetMinDX[DIM] = { 0 /*0 pollice*/, 0 /*1 indice*/, 150 /*2 medio*/, 130 /*3 anulare*/, 110 /*4 mignolo*/, 160 /*5 polso*/, 175 /*6 bicipite*/, 30 /*7 spallaDXSX*/, 20 /*8 spallaSuGiu */, 9999 /*9 Clavicola*/ };  //chiudi  // manca spalla su giu destra
int VetMaxDX[DIM] = { 45 /*0 pollice*/, 70 /*1 indice*/, 85 /*2 medio*/, 75 /*3 anulare*/, 55 /*4 mignolo*/, 70 /*5 polso*/, 15 /*6 bicipite*/, 150 /*7 spallaDXSX*/, 160 /*8 spallaSuGiu */, 9999 /*9 Clavicola*/ };   //apri

int VetMinSX[DIM] = { 135, 125, 160, 145, 110, 180, 270, 270, 270, 9999 };
int VetMaxSX[DIM] = { 90, 70, 65, 70, 35, 0, 0, 0, 0, 9999 };

int VetMaxCentrale[DIMCENTRALE] = { 9999 /*0 ColloDx*/, 9999 /*1 ColloSx*/, 9999 /*2 ColloCentrale*/, 270 /*3 MotoreTesta*/ };
int VetMinCentrale[DIMCENTRALE] = { 9999 /*0 ColloDx*/, 9999 /*1 ColloSx*/, 9999 /*2 ColloCentrale*/, 0 /*3 MotoreTesta*/ };

int VetMax[DIM];
int VetMin[DIM];

bool caricato = false;

int angToMicros(int ang) {
  return map(ang, 0, 180, 500, 2500);
}

int angToMicros270(int ang) {
  return map(ang, 0, 270, 500, 2500);
}

void setup() {
  Serial.begin(9600);

  Pollice.attach(2, 500, 2500);
  Indice.attach(3, 500, 2500);
  Medio.attach(4, 500, 2500);
  Anulare.attach(5, 500, 2500);
  Mignolo.attach(6, 500, 2500);
  Polso.attach(7, 500, 2500);
  Bicipite.attach(8, 500, 2500);
  SpallaDxSx.attach(9, 500, 2500);
  SpallaSuGiu.attach(10, 500, 2500);
  Clavicola.attach(11, 500, 2500);
  ColloDx.attach(12, 500, 2500);
  ColloSX.attach(13, 500, 2500);
  ColloCentrale.attach(14, 500, 2500);
  MotoreTesta.attach(15, 500, 2500);

  Pollice.writeMicroseconds(angToMicros(VetMaxDX[0]));
  Indice.writeMicroseconds(angToMicros(VetMaxDX[1]));
  Medio.writeMicroseconds(angToMicros(VetMaxDX[2]));
  Anulare.writeMicroseconds(angToMicros(VetMaxDX[3]));
  Mignolo.writeMicroseconds(angToMicros(VetMaxDX[4]));
  Polso.writeMicroseconds(angToMicros(PolsoRiposo));
  Bicipite.writeMicroseconds(angToMicros(VetMaxDX[6]));
  SpallaDxSx.writeMicroseconds(angToMicros(VetMaxDX[7]));
  SpallaSuGiu.writeMicroseconds(angToMicros(VetMaxDX[8]));
  Clavicola.writeMicroseconds(angToMicros(VetMaxDX[9]));

  ColloDx.writeMicroseconds(angToMicros(ColloDxRiposo));
  ColloSX.writeMicroseconds(angToMicros(ColloSxRiposo));
  ColloCentrale.writeMicroseconds(angToMicros(ColloCentraleRiposo));
  MotoreTesta.writeMicroseconds(angToMicros(MotoreTestaRiposo));
}

void loop() {

  Pos = Serial.readString();

  if (Pos.equals("handDx\n") && !caricato) {

    for (int i = 0; i < DIM; i++) {
      VetMax[i] = VetMaxDX[i];
      VetMin[i] = VetMinDX[i];
    }

    Pollice.writeMicroseconds(angToMicros(VetMax[0]));
    Indice.writeMicroseconds(angToMicros(VetMax[1]));
    Medio.writeMicroseconds(angToMicros(VetMax[2]));
    Anulare.writeMicroseconds(angToMicros(VetMax[3]));
    Mignolo.writeMicroseconds(angToMicros(VetMax[4]));
    Polso.writeMicroseconds(angToMicros(90));
    Bicipite.writeMicroseconds(angToMicros270(VetMax[6]));
    SpallaDxSx.writeMicroseconds(angToMicros270(VetMax[7]));
    SpallaSuGiu.writeMicroseconds(angToMicros270(VetMax[8]));
    Clavicola.writeMicroseconds(angToMicros(VetMax[9]));

    caricato = true;
    delay(930);
  }

  if (Pos.equals(movimenti[0]) && caricato) {  // APRI
    /*Pollice.writeMicroseconds(angToMicros(VetMax[0]));
    Indice.writeMicroseconds(angToMicros(VetMax[1]));
    Medio.writeMicroseconds(angToMicros(VetMax[2]));
    Anulare.writeMicroseconds(angToMicros(VetMax[3]));
    Mignolo.writeMicroseconds(angToMicros(VetMax[4]));*/
    apriMano();
  }

  else if (Pos.equals(movimenti[1]) && caricato) {  // CHIUDI
    /*Pollice.writeMicroseconds(angToMicros(VetMin[0]));
    Indice.writeMicroseconds(angToMicros(VetMin[1]));
    Medio.writeMicroseconds(angToMicros(VetMin[2]));
    Anulare.writeMicroseconds(angToMicros(VetMin[3]));
    Mignolo.writeMicroseconds(angToMicros(VetMin[4]));*/
    chiudiMano();
  }

  else if (Pos.equals(movimenti[2]) && caricato) {  // VITTORIA
    Pollice.writeMicroseconds(angToMicros(VetMin[0]));
    Indice.writeMicroseconds(angToMicros(VetMax[1]));
    Medio.writeMicroseconds(angToMicros(VetMax[2]));
    Anulare.writeMicroseconds(angToMicros(VetMin[3]));
    Mignolo.writeMicroseconds(angToMicros(VetMin[4]));
  }

  else if (Pos.equals(movimenti[3]) && caricato) {  // OK
    Pollice.writeMicroseconds(angToMicros(VetMax[0]));
    Indice.writeMicroseconds(angToMicros(VetMin[1]));
    Medio.writeMicroseconds(angToMicros(VetMin[2]));
    Anulare.writeMicroseconds(angToMicros(VetMin[3]));
    Mignolo.writeMicroseconds(angToMicros(VetMin[4]));
  }

  else if (Pos.equals(movimenti[4]) && caricato) {  // SALUTO

    /*Pollice.writeMicroseconds(angToMicros(VetMax[0]));
    Indice.writeMicroseconds(angToMicros(VetMax[1]));
    Medio.writeMicroseconds(angToMicros(VetMax[2]));
    Anulare.writeMicroseconds(angToMicros(VetMax[3]));
    Mignolo.writeMicroseconds(angToMicros(VetMax[4]));*/
    apriMano();
    Bicipite.writeMicroseconds(angToMicros270(VetMin[6]));
    SpallaSuGiu.writeMicroseconds(angToMicros270(VetMax[8]));

    for (int i = 0; i < DIM; i++) {
      Polso.writeMicroseconds(angToMicros(VetMax[5]));
      delay(700);
      Polso.writeMicroseconds(angToMicros(VetMin[5]));
      delay(700);
    }

    SpallaSuGiu.writeMicroseconds(angToMicros270(VetMin[8]));
    Bicipite.writeMicroseconds(angToMicros270(VetMax[6]));
    Polso.writeMicroseconds(angToMicros(PolsoRiposo));
  }

  else if (Pos.equals(movimenti[5]) && caricato) {  // APRI BICIPITE
    Bicipite.writeMicroseconds(angToMicros270(VetMax[6]));
  }

  else if (Pos.equals(movimenti[6]) && caricato) {  // CHIUDI BICIPITE
    Bicipite.writeMicroseconds(angToMicros270(VetMin[6]));
  }

  else if (Pos.equals(movimenti[7]) && caricato) {  // MOVIMENTO A DX DELLA SPALLA
    SpallaDxSx.writeMicroseconds(angToMicros270(VetMax[7]));
  }

  else if (Pos.equals(movimenti[8]) && caricato) {  // MOVIMENTO A SX DELLA SPALLA
    SpallaDxSx.writeMicroseconds(angToMicros270(VetMin[7]));
  }

  else if (Pos.equals(movimenti[9]) && caricato) {  // MOVIMENTO IN SU DELLA SPALLA
    SpallaSuGiu.writeMicroseconds(angToMicros270(VetMax[8]));
  }

  else if (Pos.equals(movimenti[10]) && caricato) {  // MOVIMENTO IN GIU' DELLA SPALLA
    SpallaSuGiu.writeMicroseconds(angToMicros270(VetMin[8]));
  }

  else if (Pos.equals(movimenti[11]) && caricato) {  // APRI BRACCIO
    /*Pollice.writeMicroseconds(angToMicros(VetMax[0]));
    Indice.writeMicroseconds(angToMicros(VetMax[1]));
    Medio.writeMicroseconds(angToMicros(VetMax[2]));
    Anulare.writeMicroseconds(angToMicros(VetMax[3]));
    Mignolo.writeMicroseconds(angToMicros(VetMax[4]));*/
    apriMano();
    Bicipite.writeMicroseconds(angToMicros270(VetMax[6]));
    SpallaDxSx.writeMicroseconds(angToMicros270(VetMax[7]));
    SpallaSuGiu.writeMicroseconds(angToMicros270(VetMax[8]));
  }

  else if (Pos.equals(movimenti[12]) && caricato) {  // CHIUDI BRACCIO
    /*Pollice.writeMicroseconds(angToMicros(VetMin[0]));
    Indice.writeMicroseconds(angToMicros(VetMin[1]));
    Medio.writeMicroseconds(angToMicros(VetMin[2]));
    Anulare.writeMicroseconds(angToMicros(VetMin[3]));
    Mignolo.writeMicroseconds(angToMicros(VetMin[4]));*/
    chiudiMano();
    Bicipite.writeMicroseconds(angToMicros270(VetMin[6]));
    SpallaDxSx.writeMicroseconds(angToMicros270(VetMin[7]));
    SpallaSuGiu.writeMicroseconds(angToMicros270(VetMin[8]));
  }

  else if (Pos.equals(movimenti[13]) && caricato) {  // ASSENSO
    ColloCentrale.writeMicroseconds(angToMicros(VetMinCentrale[3]));
    delay(100);
    ColloCentrale.writeMicroseconds(angToMicros(VetMaxCentrale[3]));
    delay(100);
    ColloCentrale.writeMicroseconds(angToMicros(ColloCentraleRiposo));
  }

  else if (Pos.equals(movimenti[14]) && caricato) {  // DINIEGO
    MotoreTesta.writeMicroseconds(angToMicros270(VetMaxCentrale[4]));
    delay(100);
    MotoreTesta.writeMicroseconds(angToM        icros270(VetMinCentrale[4]));
    delay(100);
    MotoreTesta.writeMicroseconds(angToMicros270(MotoreTestaRiposo));
  }

  else if (Pos.equals(movimenti[15]) && caricato) {  // SALUTO BRACCIO
    Bicipite.writeMicroseconds(angToMicros270(VetMin[6]));
  }
}

void apriMano() {
  Pollice.writeMicroseconds(angToMicros(VetMax[0]));
  Indice.writeMicroseconds(angToMicros(VetMax[1]));
  Medio.writeMicroseconds(angToMicros(VetMax[2]));
  Anulare.writeMicroseconds(angToMicros(VetMax[3]));
  Mignolo.writeMicroseconds(angToMicros(VetMax[4]));
}

void chiudiMano() {
  Pollice.writeMicroseconds(angToMicros(VetMin[0]));
  Indice.writeMicroseconds(angToMicros(VetMin[1]));
  Medio.writeMicroseconds(angToMicros(VetMin[2]));
  Anulare.writeMicroseconds(angToMicros(VetMin[3]));
  Mignolo.writeMicroseconds(angToMicros(VetMin[4]));
}