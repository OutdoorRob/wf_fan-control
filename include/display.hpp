#ifndef DISPLAY_HPP
#define DISPLAY_HPP

// from Arduino framework
#include <Arduino.h>

// 3rd party
#include <U8g2lib.h>


class Display {
 public:
  Display();

  void Loop();

  inline void ResetDisplayTimer() { display_timer_ = kDisplayOnTime; }

  char inside_temperature_[16];
  char outside_temperature_[16];
  char ip_ap_[20];
  char ip_wifi_[20];
  char sw_version_[16];

 private:
  const uint8_t kDisplayOnTime = 60;

  U8G2 display_driver_;
  uint8_t display_timer_;
};


#endif