#include <Arduino.h>

#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

USBKeyboard Keyboard;

#define joy_x 28
#define joy_y 27
#define sw1 29
#define sw2 14
#define sw3 13
#define sw4 12
#define sw5 11

int sensval[7];
int offset_x, offset_y;
int count_up, count_down;
// 初期設定 -------------------------------------------------------------------
void setup() {
  Serial.begin(115200);  // USB（シリアルモニタ）初期化

  pinMode(joy_x, INPUT);
  pinMode(joy_y, INPUT);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(sw4, INPUT_PULLUP);
  pinMode(sw5, INPUT_PULLUP);

  offset_x = analogRead(joy_x);
  offset_y = analogRead(joy_y);
}
// メイン処理（繰り返し）-------------------------------------------------------
void loop() {
  sensval[0] = digitalRead(sw1);
  sensval[1] = digitalRead(sw2);
  sensval[2] = digitalRead(sw3);
  sensval[3] = digitalRead(sw4);
  sensval[4] = digitalRead(sw5);
  sensval[5] = analogRead(joy_x) - offset_x;
  sensval[6] = analogRead(joy_y) - offset_x;
  for (int i = 0; i <= 6; i++) {
    Serial.print(sensval[i]);
    Serial.print(",");
  }
  Serial.println();
  if (sensval[1] == 0) {
    Keyboard.printf("U");
  }
  if (sensval[2] == 0) {
    Keyboard.printf("I");
  }
  if (sensval[3] == 0) {
    Keyboard.printf("O");
  }
  if (sensval[4] == 0) {
    Keyboard.printf("P");
  }
  if (sensval[5] > 200) {
    Keyboard.printf("W");
    count_up++;
  } else if (sensval[5] < -200) {
    Keyboard.printf("S");
    count_down++;
  } else {
    count_up = 0;
    count_down = 0;
  }
  if (sensval[6] > 200) {
    Keyboard.printf("A");
  } else if (sensval[6] < -200) {
    Keyboard.printf("D");
  }
  if (count_up >= 5) {
    Keyboard.printf("Q");
    count_up = 0;
    count_down = 0;
  }
  if (count_down >= 5) {
    Keyboard.printf("Z");
    count_up = 0;
    count_down = 0;
  }
  delay(100);
}
