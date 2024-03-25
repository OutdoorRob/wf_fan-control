#ifndef FAN_CONTROL_HPP
#define FAN_CONTROL_HPP

// from Arduino framework
#include <Arduino.h>


class FanControl {
 public:
  FanControl(uint8_t fan_pin);

  bool Control(float inside_temperature, float outside_temperature);

  inline void ResetErrorTimer() { error_timer_ = kErrorDelayTime; }

  inline void SwitchOnFan() { digitalWrite(fan_pin_, HIGH); }
  inline void SwitchOffFan() { digitalWrite(fan_pin_, LOW); }

 private:
  const int8_t kSwitchOnOutsideTemperature = -1;
  const int8_t kSwitchOffOutsideTemperature = -2;
  const uint8_t kSwitchOnTemperatureDifference = 2;
  const uint8_t kSwitchOffTemperatureDifference = 1;

  const uint8_t kErrorDelayTime = 30;

  uint8_t fan_pin_;
  uint8_t error_timer_;
};


#endif