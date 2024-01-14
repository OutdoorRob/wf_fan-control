#ifndef SENSORS_HPP
#define SENSORS_HPP

// from Arduino framework
#include <Arduino.h>

// 3rd party
#include <DallasTemperature.h>


class Sensors {
 public:
  Sensors(uint8_t one_wire_pin);

  void Loop();

  float inside_temperature_;
  float outside_temperature_;

 private:
  const uint8_t kInsideSensorAddress[8] = {0x28, 0xBB, 0x91, 0x57, 0x04, 0xB5, 0x3C, 0xBB};
  const uint8_t kOutsideSensorAddress[8] = {0x28, 0xB2, 0x7B, 0x57, 0x04, 0xC0, 0x3C, 0x03};

  const uint8_t kSensorResolutionBit = 10;   // 10 Bit allowed a much more stable communication

  OneWire one_wire_;
  DallasTemperature sensors_;

};


#endif