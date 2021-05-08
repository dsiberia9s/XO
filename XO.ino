#include <TFT_eSPI.h> // https://github.com/Bodmer/TFT_eSPI
#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>

#include "img_1.c"
#include "player_1.h"

#define BLK_PWM_CHANNEL 7

TFT_eSPI tft = TFT_eSPI();

TFT_eSprite s = TFT_eSprite(&tft);
TFT_eSprite transp_sprite = TFT_eSprite(&tft);

void draw(int x, int y, int w, int h, uint16_t* image, TFT_eSprite &sprite) {
  int padding_left = (sprite.width() - w) / 2;
  int padding_top = (sprite.height() - h) / 2;
  
  sprite.pushImage(-x, -y, 320, 240, (uint16_t*)img_1);

  transp_sprite.setSwapBytes(true);
  transp_sprite.pushImage(padding_left, padding_top, w, h, image);
  transp_sprite.setSwapBytes(false);
  transp_sprite.pushToSprite(&sprite, 0, 0, TFT_BLACK);
  
  sprite.pushSprite(x, y);
}

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
    draw(x, 0, 64, 64, (uint16_t*)player_1, s);
  
    s.pushImage(-x, 0, 320, 240, (uint16_t*)img_1);
    s.pushSprite(x, 0, TFT_BLACK);
  }
  
}
