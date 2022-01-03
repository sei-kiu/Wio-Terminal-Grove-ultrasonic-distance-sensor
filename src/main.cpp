#include <Arduino.h>

#include "../include/Free_Fonts.h" //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h
#include "TFT_eSPI.h"

#include "Ultrasonic.h"

TFT_eSPI tft;

Ultrasonic ultrasonic(0);

void setup()
{
  // put your setup code here, to run once:

  // set up screen
  tft.begin();
  tft.setRotation(2);
}

void loop()
{
  // put your main code here, to run repeatedly:

  long RangeInCentimeters;

  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  delay(250);

  //Initializing buffer
  TFT_eSprite spr = TFT_eSprite(&tft);

  // Create buffer (portrait)
  spr.createSprite(TFT_WIDTH, TFT_HEIGHT);

  // Fill background
  spr.fillSprite(TFT_YELLOW);

  // Header section
  spr.fillRect(0, 0, 240, 30, TFT_WHITE);
  spr.setFreeFont(FMB12);
  spr.setTextColor(TFT_BLACK);
  spr.drawString("Grove Ultrasonic", 5, 6);

  // Body section
  spr.setFreeFont(FMB18);
  spr.setTextDatum(MC_DATUM);
  spr.drawString("Distance", 120, 60);
  spr.drawString("to obstacle", 120, 90);
  spr.drawString("in front", 120, 120);
  spr.setFreeFont(FMB24);
  spr.setTextDatum(MC_DATUM);
  spr.drawNumber(RangeInCentimeters, 120, 180);
  spr.setTextDatum(MC_DATUM);
  spr.drawString("cm", 120, 210);

  //Push to LCD
  spr.pushSprite(0, 0);

  // Delete buffer
  spr.deleteSprite();
}