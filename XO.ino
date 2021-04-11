#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>

#include "img_1.c"
#include "player_1.h"

#define BLK_PWM_CHANNEL 7

TFT_eSPI tft = TFT_eSPI();

TFT_eSprite s = TFT_eSprite(&tft);
TFT_eSprite transp_sprite = TFT_eSprite(&tft);

void M5Stack() {
  Serial.begin(115200);
  Serial.flush();

  Wire.begin(21, 22);

  pinMode(15, OUTPUT_OPEN_DRAIN);

  tft.init();
  tft.setRotation(1);
  tft.writecommand(0x21); // fix color inversion
  tft.fillScreen(0);
  
  ledcSetup(BLK_PWM_CHANNEL, 44100, 8);
  ledcAttachPin(TFT_BL, BLK_PWM_CHANNEL);
  ledcWrite(BLK_PWM_CHANNEL, 80);

  delay(50);
}

void setup() {
  M5Stack();
  tft.pushImage(0, 0, 320, 240, (const uint16_t*)img_1);
  s.createSprite(84, 84);
  transp_sprite.createSprite(84, 84);
}

void loop() {
  int x = 50;

  for (; x < 180; x+=2) {
    s.pushImage(-x, 0, 320, 240, (uint16_t*)img_1);

    transp_sprite.setSwapBytes(true);
    transp_sprite.pushImage(10, 10, 64, 64, (uint16_t*)player_1);
    transp_sprite.setSwapBytes(false);
    transp_sprite.pushToSprite(&s, 0, 0, TFT_BLACK);
    
    //s.drawRect(10, 10, 60, 60, TFT_RED);
    s.pushSprite(x, 0);
    delay(40);
  }
  s.pushImage(-x, 0, 320, 240, (uint16_t*)img_1);
  s.pushSprite(x, 0, TFT_BLACK);
  
}

/*
 * 
 *   for (int x = 0; x < 160; x++) {   

    s.drawRect(0, 0, 60, 60, TFT_RED);
    //s.pushImage(0, 0, 60, 60, (uint16_t*)player_1);
    s.pushSprite(x, x, TFT_BLACK);
    delay(500);


    s.pushImage(0, 0, 60, 60, (uint16_t*)img_1);
    s.pushSprite(x, x, TFT_BLACK);
    //s.pushImage(-(320 - x), -(240 - x), 60, 60, (uint16_t*)img_1);
    //s.pushSprite(x, x, TFT_BLACK);
    delay(500);
  }

  s.deleteSprite();
  //s.pushImage(-(320 - i), -10, 320, 240, (uint16_t*)img_1);
  //s.swapBytes(true);
  //tft.pushImage(i, i, 60, 60, (uint16_t*)player_1);
  //s.pushSprite(i, 10, TFT_BLACK);

  m5.Lcd.startWrite();
  m5.Lcd.setWindow(10, 10, 320, 240);
  m5.Lcd.writePixels(b, sizeof(b) / sizeof(uint16_t));
  m5.Lcd.endWrite();

 */
