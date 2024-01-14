// from Arduino framework
#include <Arduino.h>

// 3rd party
#include <U8g2lib.h>

// project
#include <display.hpp>

Display::Display() {

  // Version V1.1
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C display_u8g2(U8G2_R0,             // SSD1306 / 128x64 Pixel / F = full frame buffer in RAM / interface: HW I2C / para1 = ???
                                                   U8X8_PIN_NONE);      // no reset pin for display / default pins for clock & data

  // Version V2.2
  // U8G2_SH1106_128X64_NONAME_F_HW_I2C display_u8g2(U8G2_R0,              // SH1106 / 128x64 Pixel / F = full frame buffer in RAM / interface: HW I2C / para1 = ???
  //                                                 U8X8_PIN_NONE);       // no reset pin for display / default pins for clock & data

  display_driver_ = display_u8g2;
  
  display_driver_.setI2CAddress(0x3C << 1);
  display_driver_.begin();                           // init display
  display_driver_.setFont(u8g2_font_8x13_tf);        // prepare display settings
  display_driver_.setFontRefHeightExtendedText(); 
  display_driver_.setDrawColor(1);
  display_driver_.setFontPosTop();
  display_driver_.setFontDirection(0);

  ResetDisplayTimer();
}

void Display::Loop() {

  if (display_timer_ > 0) {
    display_timer_--;

    display_driver_.clearBuffer();
    display_driver_.setFont(u8g2_font_8x13_tf);
    display_driver_.drawStr(0, 0, inside_temperature_);
    display_driver_.drawStr(0, 16, outside_temperature_);
    //display_driver_.drawStr(0, 32, "fan: on / off");
    //display_driver_.setFont(u8g2_font_iconquadpix_m_all);
    //display_driver_.drawStr(0, 32, "\x71");
    //display_driver_.setFont(u8g2_font_8x13_tf);
    display_driver_.drawStr(0, 32, sw_version_);
    display_driver_.drawStr(0, 48, ip_ap_);
    display_driver_.sendBuffer();
  }
  else {
    display_driver_.clearDisplay();
  }
}
