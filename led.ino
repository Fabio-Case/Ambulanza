#include <Adafruit_NeoPixel.h>
#include "DFRobotDFPlayerMini.h"
 
static unsigned long timer = 0;
DFRobotDFPlayerMini myDFPlayer;

//define per neoPixel RGB
#define PFreno 2
#define PLuciDietroSx 3
#define PLuciDietroDx 4
#define PFrecceSx 5
#define PFrecceDx 6
#define PLampeggiantiDietroSx 7
#define PLampeggiantiDietroDx 8
#define PLuciDavantiSx 9
#define PLuciDavantiDx 10
#define PFendinebbia 11
#define PLampeggiantiDavantiSX 22
#define PLampeggiantiDavantiDX 23
#define PLampeggiantiSopraSX 24
#define PLampeggiantiSopraDx 25

//define pin Motori
#define motoreFSX A1
#define motoreDDX A3
#define motoreBSX A2
#define motoreBDX A4

//inizializzazione neopixel
Adafruit_NeoPixel stripFreno = Adafruit_NeoPixel(3, PFreno, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLuciDietroDX = Adafruit_NeoPixel(8, PLuciDietroDx, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLuciDietroSX = Adafruit_NeoPixel(8, PLuciDietroSx, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripFrecceSX = Adafruit_NeoPixel(3, PFrecceSx, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripFrecceDX = Adafruit_NeoPixel(3, PFrecceDx, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLampeggiantiDietroSX = Adafruit_NeoPixel(13, PLampeggiantiDietroSx, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLampeggiantiDietroDX = Adafruit_NeoPixel(13, PLampeggiantiDietroDx, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLuciDavantiSX = Adafruit_NeoPixel(5, PLuciDavantiSx, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLuciDavantiDX = Adafruit_NeoPixel(3, PLuciDavantiDx, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripFendinebbia = Adafruit_NeoPixel(2, PFendinebbia, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLampeggiantiDavantiSx = Adafruit_NeoPixel(6, PLampeggiantiDavantiSX, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLampeggiantiDavantiDx = Adafruit_NeoPixel(6, PLampeggiantiDavantiDX, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLampeggiantiSopraSx = Adafruit_NeoPixel(19, PLampeggiantiSopraSX, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLampeggiantiSopraDx = Adafruit_NeoPixel(19, PLampeggiantiSopraDx, NEO_GRB + NEO_KHZ800);

uint32_t FRENO = 11141120L;   //(170<<16)|(0<<8)|(0)
uint32_t RETRONEBBIA = 13107200L; //(200<<16)|(0<<8)|(0)
uint32_t LUCIDIETRO = 6553600L; //(100<<16)|(0<<8)|(0)
uint32_t FRECCE = 15738880L;    //(240<<16)|(40<<0)|(0)
uint32_t RETRO = 11178310L;   //(170<<16)|(145<<0)|(70)
uint32_t ABBAGLIANTI = 13806185L; //(210<<16)|(170<<8)|(105)
uint32_t ANABBAGLIANTI = 9529404L;  //(145<<16)|(105<<8)|(60)
uint32_t POSIZIONI = 6831126L;    //(105<<16)|(60<<8)|(22)
uint32_t FENDINEBBIA = 8542760; //(130<<16)|(90<<8)|(40)
uint32_t LAMPEGGIANTI = 393983L;  //(6<<16)|(2<<8)|(255)


//funzioni
//get colori
byte getColorR(uint32_t color);
byte getColorG(uint32_t color);
byte getColorB(uint32_t color);
//setters
void setLuci(bool stato);
void setLampeggianti(bool stato);
void setFreno(bool stato);
void setFendinebbia(bool stato);
void setFrecce(bool stato, String lato);
void set4Frecce(bool stato);
void setRetronebbia(bool stato);
void setRetro(bool stato);
void setPosizioni(bool stato);
void setAbbaglianti(bool stato);


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(38400);

  //Bluetooth
  Serial2.begin(9600);

  //lettore mp3
  Serial3.begin(9600);
   
  if (!myDFPlayer.begin(Serial3)) 
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }

  //inizializzazione e spengo tutti i led
  stripFreno.begin();
  stripLuciDietroDX.begin();
  stripLuciDietroSX.begin();
  stripFrecceDX.begin();
  stripFrecceSX.begin();
  stripLampeggiantiDietroSX.begin();
  stripLampeggiantiDietroDX.begin();
  stripLuciDavantiDX.begin();
  stripLuciDavantiSX.begin();
  stripFendinebbia.begin();
  stripLampeggiantiSopraDx.begin();
  stripLampeggiantiSopraSx.begin();
  stripLampeggiantiDavantiDx.begin();
  stripLampeggiantiDavantiSx.begin();
  stripFreno.show();
  stripLuciDietroDX.show();
  stripLuciDietroSX.show();
  stripFrecceDX.show();
  stripFrecceSX.show();
  stripLampeggiantiDietroSX.show();
  stripLampeggiantiDietroDX.show();
  stripLuciDavantiDX.show();
  stripLuciDavantiSX.show();
  stripFendinebbia.show();
  stripLampeggiantiSopraDx.show();
  stripLampeggiantiSopraSx.show();
  stripLampeggiantiDavantiDx.show();
  stripLampeggiantiDavantiSx.show();
}

// the loop function runs over and over again until power down or reset
void loop() {

}

//get colori
byte getColorR(uint32_t color){
  return color >> 16 & 255;
}
byte getColorG(uint32_t color){
  return color >> 8 & 255;
}
byte getColorB(uint32_t color){
  return color & 255;
}

void setLuci(bool stato){
  if(stato){
    stripLuciDietroDX.setPixelColor(5, getColorR(LUCIDIETRO), getColorG(LUCIDIETRO), getColorB(LUCIDIETRO));
    stripLuciDietroDX.setPixelColor(6, getColorR(LUCIDIETRO), getColorG(LUCIDIETRO), getColorB(LUCIDIETRO));
    stripLuciDietroDX.setPixelColor(7, getColorR(LUCIDIETRO), getColorG(LUCIDIETRO), getColorB(LUCIDIETRO));
    stripLuciDavantiDX.setPixelColor(1, getColorR(ANABBAGLIANTI), getColorG(ANABBAGLIANTI), getColorB(ANABBAGLIANTI));
    stripLuciDavantiDX.setPixelColor(2, getColorR(ANABBAGLIANTI), getColorG(ANABBAGLIANTI), getColorB(ANABBAGLIANTI));
    stripLuciDavantiDX.setPixelColor(3, getColorR(ANABBAGLIANTI), getColorG(ANABBAGLIANTI), getColorB(ANABBAGLIANTI));
    stripLuciDietroSX.setPixelColor(5, getColorR(LUCIDIETRO), getColorG(LUCIDIETRO), getColorB(LUCIDIETRO));
    stripLuciDietroSX.setPixelColor(6, getColorR(LUCIDIETRO), getColorG(LUCIDIETRO), getColorB(LUCIDIETRO));
    stripLuciDietroSX.setPixelColor(7, getColorR(LUCIDIETRO), getColorG(LUCIDIETRO), getColorB(LUCIDIETRO));
    stripLuciDavantiSX.setPixelColor(1, getColorR(ANABBAGLIANTI), getColorG(ANABBAGLIANTI), getColorB(ANABBAGLIANTI));
    stripLuciDavantiSX.setPixelColor(2, getColorR(ANABBAGLIANTI), getColorG(ANABBAGLIANTI), getColorB(ANABBAGLIANTI));
    stripLuciDavantiSX.setPixelColor(3, getColorR(ANABBAGLIANTI), getColorG(ANABBAGLIANTI), getColorB(ANABBAGLIANTI));
  }
  else{
    stripLuciDietroDX.setPixelColor(5, 0, 0, 0);
    stripLuciDietroDX.setPixelColor(6, 0, 0, 0);
    stripLuciDietroDX.setPixelColor(7, 0, 0, 0);
    stripLuciDavantiDX.setPixelColor(1, 0, 0, 0);
    stripLuciDavantiDX.setPixelColor(2, 0, 0, 0);
    stripLuciDavantiDX.setPixelColor(3, 0, 0, 0);
    stripLuciDietroSX.setPixelColor(5,  0, 0, 0));
    stripLuciDietroSX.setPixelColor(6,  0, 0, 0);
    stripLuciDietroSX.setPixelColor(7,  0, 0, 0);
    stripLuciDavantiSX.setPixelColor(1, 0, 0, 0);
    stripLuciDavantiSX.setPixelColor(2, 0, 0, 0);
    stripLuciDavantiSX.setPixelColor(3, 0, 0, 0);
  }
}
void setLampeggianti(bool stato){
  if(stato){
    for (int i = 0; i < 13; i++){
      stripLampeggiantiDietroSX.setPixelColor(i, getColorR(LAMPEGGIANTI), getColorG(LAMPEGGIANTI), getColorB(LAMPEGGIANTI));
      stripLampeggiantiDietroDX.setPixelColor(i, getColorR(LAMPEGGIANTI), getColorG(LAMPEGGIANTI), getColorB(LAMPEGGIANTI));
    }
    for (int i = 0; i < 6; i++){
      stripLampeggiantiDavantiSx.setPixelColor(i, getColorR(LAMPEGGIANTI), getColorG(LAMPEGGIANTI), getColorB(LAMPEGGIANTI));
      stripLampeggiantiDavantiDx.setPixelColor(i, getColorR(LAMPEGGIANTI), getColorG(LAMPEGGIANTI), getColorB(LAMPEGGIANTI));
    }
    for (int i = 0; i < 19; i++){
      stripLampeggiantiDavantiSx.setPixelColor(i, getColorR(LAMPEGGIANTI), getColorG(LAMPEGGIANTI), getColorB(LAMPEGGIANTI));
      stripLampeggiantiDavantiDx.setPixelColor(i, getColorR(LAMPEGGIANTI), getColorG(LAMPEGGIANTI), getColorB(LAMPEGGIANTI));
    }
  }
}
void setFreno(bool stato);
void setFendinebbia(bool stato);
void setFrecce(bool stato, String lato);
void set4Frecce(bool stato);
void setRetronebbia(bool stato);
void setRetro(bool stato);
void setPosizioni(bool stato);
void setAbbaglianti(bool stato);