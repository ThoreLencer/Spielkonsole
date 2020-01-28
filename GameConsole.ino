#include <TFT.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Wire.h>
#include "Adafruit_LIS3DH.h"
#include "Adafruit_Sensor.h"
#define cs   4
#define dc   3
#define rst  2
#define t1 11
#define r1 0
#define b1 1
#define l1 12
#define l2 18
#define t2 13
#define b2 15
#define r2 14
TFT TFTscreen = TFT(cs, dc, rst);
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
int16_t Modus, Auswahl, GameSpeed, Page, RandomSeedTimer;
int SnakeHighScore;
void setup() {
  pinMode(t1, INPUT_PULLUP);
  pinMode(r1, INPUT_PULLUP);
  pinMode(b1, INPUT_PULLUP);
  pinMode(l1, INPUT_PULLUP);
  pinMode(l2, INPUT_PULLUP);
  pinMode(r2, INPUT_PULLUP);
  pinMode(t2, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  if(!lis.begin(0x18)){
    TFTscreen.setTextSize(2);
      setColor(0, 0, 255);
      TFTscreen.text("Sensorfehler", 15, 50);
      TFTscreen.setTextSize(1);
      setColor(255, 0, 0);
      TFTscreen.text("Druecken sie L1!", 10, 100);
    while(true){
      if(digitalRead(l1) == LOW)
        break;
      delay(200);
    }
    TFTscreen.background(0, 0, 0);
  } else {
    lis.setRange(LIS3DH_RANGE_4_G);
  }
  GameSpeed = 100;
  Modus = 1;
  Auswahl = 1;
  RandomSeedTimer = 0;
  Page = 1;
  
  EEPROM.get(0, SnakeHighScore);
}
void DrawMenu() {
  setColor(0, 255, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Menu", 56, 6);
  setColor(0, 0, 255);
  if (Page == 1) {
    TFTscreen.text("Pong", 30, 28);
    TFTscreen.text("Snake", 30, 50);
    TFTscreen.text("TicTacToe", 30, 72);
    TFTscreen.text("Asteroids", 30, 94);
  } else if (Page == 2) {
    TFTscreen.text("2048", 30, 28);
    TFTscreen.text("Jump", 30, 50);
    TFTscreen.text("Memory", 30, 72);
    TFTscreen.text("Sensor", 30, 94);
  }
  setColor(255, 0, 0);
  TFTscreen.rect(10, 32 + ((Auswahl - 1) * 22), 5, 5);
}
void HandleKeyInputMenu() {
  setColor(0, 0, 0);
  //OK KEY
  if (digitalRead(l2) == LOW) {
    if (RandomSeedTimer != -1) {
      randomSeed(RandomSeedTimer);
      RandomSeedTimer = -1;
    }
    if (Page == 1) {
      switch (Auswahl) {
        case 1:
          PongInit();
          Modus = 2;
          break;
        case 2:
          SnakeInit();
          Modus = 3;
          break;
        case 3:
          TicTacToeInit();
          Modus = 4;
          break;
        case 4:
          AsteroidsInit();
          Modus = 5;
          break;
      }
    } else if (Page == 2) {
      switch (Auswahl) {
        case 1:
          Init2048();
          Modus = 6;
          break;
        case 2:
          InitJump();
          Modus = 7;
          break;
        case 3:
          InitMemory();
          Modus = 8;
          break;
        case 4:
          InitAccelerometer();
          Modus = 9;
          break;
      }
    }
  }
  //UP
  if (digitalRead(t1) == LOW) {
    if (Auswahl == 1) {
      Auswahl = 4;
    } else {
      Auswahl --;
    }
    TFTscreen.rect(0, 0, 30, 128);
  }
  //DOWN
  if (digitalRead(b1) == LOW) {
    if (Auswahl == 4) {
      Auswahl = 1;
    } else {
      Auswahl ++;
    }
    TFTscreen.rect(0, 0, 30, 128);
  }
  if (digitalRead(l1) == LOW) { //LEFT
    TFTscreen.background(0, 0, 0);
    if (Page > 1)
      Page --;
    else
      Page = 2;
  }
  if (digitalRead(r1) == LOW) { //RIGHT
    TFTscreen.background(0, 0, 0);
    if (Page < 2)
      Page ++;
    else
      Page = 1;
  }
}
void loop() {
  if (Modus == 1) {
    DrawMenu();
    HandleKeyInputMenu();
  } else if (Modus == 2) {
    PongLoop();
  } else if (Modus == 3) {
    SnakeLoop();
  } else if (Modus == 4) {
    TicTacToeLoop();
  } else if (Modus == 5) {
    AsteroidsLoop();
  } else if (Modus == 6) {
    Loop2048();
  } else if (Modus == 7){
    LoopJump();
  } else if (Modus == 8){
    LoopMemory();
  } else if (Modus == 9){
    LoopAccelerometer();
  }
  if (RandomSeedTimer != -1)
    RandomSeedTimer ++;
  if (RandomSeedTimer == 300)
    RandomSeedTimer = 0;

  delay(GameSpeed);
}
