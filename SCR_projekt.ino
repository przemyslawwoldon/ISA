#include <ISALiquidCrystal.h>

#include <ISATemplates.h>
#include <DueTimer.h>
#include <ISAOLED.h>
#include<ISADefinitions.h>
ISAOLED lc;

void beforeStrt();

/*draw map, object*/
void drawMapStart(); 
void draw1Map();
void draw2Map();
void draw3Map();
void drawStopMap();
void drawObj();

/*function for timer*/
void handler(void); // game
void gameStop(); // game over
void timeDisp();

/*set value y from map*/
void setValueForMaps();
void setValueForMapStart();
void setValueFor1Map();
void setValueFor2Map();
void setValueFor3Map();
void setValueForMapStop();

LiquidCrystal lcd(26, 28, 29, 30, 31, 32);
int mapa = 0;
float tabForSin[75];
int tabYForMapStart[128];
int tabYFor1Map[128];
int tabYFor2Map[128];
int tabYFor3Map[128];
int tabYForMapStop[128];
int xObj = 0;
int yObj = 0;
int czas = 0;
bool flag = true;

void setup() {
  Serial.begin(9600);
  lc.begin();
  xObj = 32;
  yObj = 32;
  Timer5.attachInterrupt(handler).setFrequency(6);
  Timer6.attachInterrupt(timeDisp).setFrequency(1);
  int j = 0;
  for(j = 0; j < 75; j++) {
    tabForSin[j] = j * 0.01745329252;
  }
  beforeStart();
  Timer4.attachInterrupt(gameStop).setFrequency(10);
  Timer5.start();
  Timer4.start();
  Timer6.start();
  
}
//10234
void loop() {
  int joy = analogRead(JOY2Y);
  int yJoy = -3 * map(joy, 1, 1023, -1, 2);
  if(yJoy < 0) {
    yObj -= 1;
  }else if(yJoy > 0) {
    yObj += 1;
  }
  /*if(a == 0) {
   * Do nothing
   * }
   */

  int poten = analogRead(POT);
  int p = map(poten, 0, 1023, 6, 12);
  if(flag == true) {
    Timer5.stop();
    Timer5.setFrequency(p);
    Timer5.start();
  }
  
  Serial.print(p);
  Serial.print("\n");
  delay(150);
}

void timeDisp(){
  czas += 1;
  lcd.begin(1,2);
  lcd.print(czas); 
}

void beforeStart() {
  setValueForMaps();
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

void gameStop() {
  if(mapa == 0) {
    if((yObj + 5 ==  tabYForMapStart[xObj]) || (yObj - 5 ==  tabYForMapStart[xObj])) {
      pinMode(24, OUTPUT);
      digitalWrite(24, HIGH);
      lc.clear(true);
      lc.gotoXY(40, 4);
      lc.print(":(");
      lc.renderAll();
      flag = false;
      Timer5.stop(); 
      Timer4.stop();
      Timer6.stop();
    }
  }else if(mapa == 1) {
    if((yObj + 5 ==  tabYFor1Map[xObj]) || (yObj - 5 ==  tabYFor1Map[xObj])) {
      pinMode(24, OUTPUT);
      digitalWrite(24, HIGH); 
      lc.clear(true);
      lc.gotoXY(40, 4);
      lc.print(":(");
      lc.renderAll();
      
      flag = false;
      Timer5.stop(); 
      Timer6.stop();
      Timer4.stop();
    }
  }else if(mapa == 2) {
    if((yObj + 5 ==  tabYFor2Map[xObj]) || (yObj - 5 ==  tabYFor2Map[xObj])) {
      pinMode(24, OUTPUT);
      digitalWrite(24, HIGH);
      lc.clear(true);
      lc.gotoXY(40, 4);
      lc.print(":(");
      lc.renderAll();
      flag = false;
      Timer5.stop(); 
      Timer4.stop();
      Timer6.stop(); 
    } 
  }else if(mapa == 3) {
    if((yObj + 5 ==  tabYFor3Map[xObj]) || (yObj - 5 ==  tabYFor3Map[xObj])) {
      pinMode(24, OUTPUT);
      digitalWrite(24, HIGH); 
      lc.clear(true);
      lc.gotoXY(40, 4);
      lc.print(":(");
      lc.renderAll();
      flag = false;
      Timer5.stop(); 
      Timer4.stop();
      Timer6.stop();
    }
  }else if(mapa == 4) {
    if((yObj + 5 ==  tabYForMapStop[xObj]) || (yObj - 5 ==  tabYForMapStop[xObj])) {
      pinMode(24, OUTPUT);
      digitalWrite(24, HIGH); 
      lc.clear(true);
      lc.gotoXY(40, 4);
      lc.print(":(");
      lc.renderAll();
      flag = false;
      Timer5.stop(); 
      Timer4.stop();
      Timer6.stop();
    }
  }digitalWrite(24, LOW);
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
  }else if(mapa == 1) {
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
      flag = false;
      Timer5.stop();
      Timer4.stop();
      Timer6.stop();
    }
  }
}

void drawObj() {
  //lc.writeLine((xObj + 1), (yObj - 5), (xObj + 1), (yObj + 5));
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

void setValueForMaps() {
  setValueForMapStart();
  setValueFor1Map();
  setValueFor2Map();
  setValueFor3Map();
  setValueForMapStop();
}

void setValueForMapStart() {
  int i = 0;
  for(i = 0; i < 64; i++) {
    tabYForMapStart[i] = 32;
  }
  for(i = 0; i < 25; i++) {
    tabYForMapStart[64 + i] = (32 - i);
  }
  for(i = 88; i < 94; i++) {
    tabYForMapStart[i] = 8;
  }
  for(i = 0; i < 25; i++) {
    tabYForMapStart[94 + i] = (8 + i);
  }
  for(i = 118; i < 128; i++) {
    tabYForMapStart[i] = 32;
  }
}

void setValueFor1Map() {
  int i = 0;
  for(i = 0; i < 75; i++) {
    double sTemp = sin(tabForSin[i]) *10;
    int sOk = (int)sTemp; 
    tabYFor1Map[i] = 32 + sOk;
  }
  /*
  for(i = 72; i < 128; i++) {
    double sTemp = sin(tabForSin[i]) * 10;
    int sOk = (int)sTemp; 
    tabYFor1Map[i] = 32 + sOk;
  }*/
  int j = 0;
  for(i = 72; (72 + j) < 128; i--) {
    double sTemp = sin(tabForSin[i]) * 10;
    int sOk = (int)sTemp; 
    tabYFor1Map[72 + j] = 32 + sOk;
    j++;
  }  
}

void setValueFor2Map() {
  int i = 0;
  for(i = 0; i < 75; i++) {
    double sTemp = sin(tabForSin[i]) *10;
    int sOk = (int)sTemp; 
    tabYFor2Map[i] = 32 - sOk;
  }
  int j = 0;
  for(i = 72; (72 + j) < 128; i--) {
    double sTemp = sin(tabForSin[i]) * 10;
    int sOk = (int)sTemp; 
    tabYFor2Map[72 + j] = 32 - sOk;
    j++;
  }
  
}

void setValueFor3Map() {
  int i = 0;
  for(i = 0; i < 8; i++) {
    tabYFor3Map[i] = 32;
  }
  for(i = 0; i < 25; i++) {
    tabYFor3Map[8 + i] = 32 + i;
  }
  for(i = 0; i < 50; i++) {
    tabYFor3Map[33 + i] = 57 - i;
  }
  for(i = 0; i < 25; i++) {
    tabYFor3Map[83 + i] = 7 + i;
  }
  for(i = 0; i < 7; i++) {
    tabYFor3Map[108 + i] = 32 - i;
  }
  for(i = 0; i < 7; i++) {
    tabYFor3Map[115 + i] = 25 + i;
  }
  for(i = 122; i < 128; i++) {
    tabYFor3Map[i] = 32;
  } 
}

void setValueForMapStop() {
  int i = 0;
  for(i = 0; i < 6; i++) {
    tabYForMapStop[i] = 32;
  }
  for(i = 0; i < 25; i++) {
    tabYForMapStop[6 + i] = 32 - i;
  }
  for(i = 31; i < 36; i++) {
    tabYForMapStop[i] = 7;
  }
  for(i = 0; i < 25; i++) {
    tabYForMapStop[36 + i] = 7 + i;
  }
  for(i = 61; i < 66; i++) {
    tabYForMapStop[i] = 32;
  }
  for(i = 0; i < 15; i++) {
    tabYForMapStop[66 + i] = 32 + i;
  }
  for(i = 81; i < 86; i++) {
    tabYForMapStop[i] = 47;
  }
  for(i = 0; i < 25; i++) {
    tabYForMapStop[86 + i] = 47 - i;
  }
  for(i = 111; i < 115; i++) {
    tabYForMapStop[i] = 22;
  }
  for(i = 0; i < 5; i++) {
    tabYForMapStop[115 + i] = 22 - i;
  }
  for(i = 120; i < 125; i++) {
    tabYForMapStop[i] = 17;
  } 
}


