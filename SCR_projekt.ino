#include <DueTimer.h>
#include <ISAOLED.h>
#include <ISAButtons.h>
#include<ISADefinitions.h>
ISAButtons buttons;
ISAOLED lc;

void beforeStrt();
void drawObject();
void drawMapStart(); 
void draw1Map();
void draw2Map();
void draw3Map();
void drawStopMap();
void drawObj();
void handler(void);
void handlerButton();
int mapa = 0;
float tabForSin[75];

int xObj = 0;
int yObj = 0;

void setup() {
  Serial.begin(9600);
  lc.begin();
  xObj = 32;
  yObj = 32;
  //Timer5.attachInterrupt(handlerButton).setFrequency(10);
  int j = 0;
  for(j = 0; j < 75; j++) {
    tabForSin[j] = j * 0.01745329252;
  }
  beforeStart();
  //Timer5.start();
  buttons.init();
}

void loop() {

  if (!buttons.buttonPressed(1)) {
    //Do nothing
  }else {
    yObj -= 1;   
    digitalWrite(3, true); 
  }
  
  
  
  if(!buttons.buttonPressed(6)) {
    //Do nothing
  }else {
    yObj += 1;
    digitalWrite(3, false); 
  }


  
  Serial.print(yObj);
  Serial.print("\n");


  if(mapa == 0) {
    drawMapStart() ;
    drawObj();
    xObj += 1;
    lc.renderAll();
    if((xObj) == 125) {
      mapa = 1;
      xObj = 0;
      yObj = 32;
    }
  }/*else if(mapa == 1) {
    draw1Map() ;
    drawObj();
    xObj += 1;
    lc.renderAll(); 
    if((xObj) == 125) {
      mapa = 2;
      xObj = 0;
      yObj = 32;
    }
  }else if(mapa == 2) {
    draw2Map() ;
    drawObj();
    xObj += 1;
    lc.renderAll(); 
    if((xObj) == 125) {
      mapa = 3;
      xObj = 0;
      yObj = 32;
    }
  }else if(mapa == 3) {
    draw3Map() ;
    drawObj();
    xObj += 1;
    lc.renderAll(); 
    if((xObj) == 125) {
      mapa = 4;
      xObj = 0;
      yObj = 32;
    }
  }else if(mapa == 4) {
    drawStopMap() ;
    drawObj();
    xObj += 1;
    lc.renderAll(); 
    if((xObj) == 125) {
      lc.clear(true);
      lc.gotoXY(40, 4);
      lc.print("ZWYCIESTWO");
      lc.renderAll();
      while(1){}
    }
  }
*/
delay(500);












}



void beforeStart() {
  lc.gotoXY(64, 4);
  lc.print("3");
  lc.renderAll(); 
  delay(1000);
  lc.clear(true);
  lc.gotoXY(64, 4);
  lc.print("2");
  lc.renderAll(); 
  delay(1000);
  lc.clear(true);
  lc.gotoXY(64, 4);
  lc.print("1");
  lc.renderAll(); 
  delay(1000);
  lc.clear(true);
  lc.gotoXY(54, 4);
  lc.print("START");
  lc.renderAll(); 
  delay(1000);
  lc.clear(true);
  lc.renderAll(); 
}

void handler(void) {
  if(mapa == 0) {
    drawMapStart() ;
    drawObj();
    xObj += 1;
    lc.renderAll();
    if((xObj) == 125) {
      mapa = 1;
      xObj = 0;
      yObj = 32;
    }
  }
  
  
  
  else if(mapa == 1) {
    draw1Map() ;
    drawObj();
    xObj += 1;
    lc.renderAll(); 
    if((xObj) == 125) {
      mapa = 2;
      xObj = 0;
      yObj = 32;
    }
  }else if(mapa == 2) {
    draw2Map() ;
    drawObj();
    xObj += 1;
    lc.renderAll(); 
    if((xObj) == 125) {
      mapa = 3;
      xObj = 0;
      yObj = 32;
    }
  }else if(mapa == 3) {
    draw3Map() ;
    drawObj();
    xObj += 1;
    lc.renderAll(); 
    if((xObj) == 125) {
      mapa = 4;
      xObj = 0;
      yObj = 32;
    }
  }else if(mapa == 4) {
    drawStopMap() ;
    drawObj();
    xObj += 1;
    lc.renderAll(); 
    if((xObj) == 125) {
      lc.clear(true);
      lc.gotoXY(40, 4);
      lc.print("ZWYCIESTWO");
      lc.renderAll();
      Timer0.stop();
    }
  }
}

void drawObj() {
  lc.writeLine((xObj + 1), (yObj - 5), (xObj + 1), (yObj + 5));
  lc.writeLine((xObj), (yObj - 5), (xObj), (yObj + 5));
}

void drawMapStart() {
  lc.clear(true);
  lc.gotoXY(0,0);
  lc.writeLine(0, 0, 0, 64);
  lc.writeLine(1, 0, 1, 64);
  lc.writeLine(2, 0, 2, 64);
  lc.writeLine(0, 32, 64, 32);
  int i = 0;
  for(i = 0; i < 25; i++) {
    lc.setPixel((64 + i), (32 - i), true);
  }
  lc.writeLine(88, 8, 94, 8);

  for(i = 0; i < 25; i++) {
    lc.setPixel((94 + i), (8 + i), true);
  }
  lc.writeLine(118, 32, 128, 32);
}

void draw1Map() {
  lc.clear(true);
  lc.gotoXY(0,0);
  int i = 0;
  for(i = 0; i < 75; i++) {
    double sTemp = sin(tabForSin[i]) *10;
    int sOk = (int)sTemp; 
    lc.setPixel((0 + i), (32 + sOk), true);
  }

  int j = 0;
  for(i = 72; j < 128; i--) {
    double sTemp = sin(tabForSin[i]) * 10;
    int sOk = (int)sTemp; 
    lc.setPixel((72 + j), (32 + sOk), true);
    j++;
  }  
}

void draw2Map() {
  lc.clear(true);
  lc.gotoXY(0,0);
  int i = 0;
  for(i = 0; i < 75; i++) {
    double sTemp = sin(tabForSin[i]) *10;
    int sOk = (int)sTemp; 
    lc.setPixel((0 + i), (32 - sOk), true);
  }

  int j = 0;
  for(i = 72; j < 128; i--) {
    double sTemp = sin(tabForSin[i]) * 10;
    int sOk = (int)sTemp; 
    lc.setPixel((72 + j), (32 - sOk), true);
    j++;
  }
}

void draw3Map() {
  lc.clear(true);
  lc.gotoXY(0,0);
  lc.writeLine(0, 32, 8, 32);
  int i = 0;
  for(i = 0; i < 25; i++) {
    lc.setPixel((8 + i), (32 + i), true);
  }
  for(i = 0; i < 50; i++) {
    lc.setPixel((33 + i), (57 - i), true);
  }
  for(i = 0; i < 25; i++) {
    lc.setPixel((83 + i), (7 + i), true);
  }
  for(i = 0; i < 7; i++) {
    lc.setPixel((108 + i), (32 - i), true);
  }
  for(i = 0; i < 7; i++) {
    lc.setPixel((115 + i), (25 + i), true);
  }
  lc.writeLine(122, 32, 128, 32);
}

void drawStopMap() {
  lc.clear(true);
  lc.gotoXY(0,0);
  lc.writeLine(0, 32, 6, 32);
  int i = 0;
  for(i = 0; i < 25; i++) {
    lc.setPixel((6 + i), (32 - i), true);
  }
  lc.writeLine(31, 7, 36, 7);
  for(i = 0; i < 25; i++) {
    lc.setPixel((36 + i), (7 + i), true);
  }
  lc.writeLine(61, 32, 66, 32);
  for(i = 0; i < 15; i++) {
    lc.setPixel((66 + i), (32 + i), true);
  }
  lc.writeLine(81, 47, 86, 47);

  for(i = 0; i < 25; i++) {
    lc.setPixel((86 + i), (47 - i), true);
  }
  lc.writeLine(111, 22, 115, 22);
  for(i = 0; i < 5; i++) {
    lc.setPixel((115 + i), (22 - i), true);
  }
  lc.writeLine(120, 17, 125, 17);
  
  lc.writeLine(127, 0, 127, 64);
  lc.writeLine(126, 0, 126, 64);
  lc.writeLine(125, 0, 125, 64);
}

