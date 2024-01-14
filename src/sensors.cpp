// from Arduino framework
#include <Arduino.h>

// project
#include <sensors.hpp>


Sensors::Sensors(uint8_t one_wire_pin) {
  one_wire_ = OneWire(one_wire_pin);
  sensors_ = DallasTemperature(&one_wire_);

  sensors_.begin();
  sensors_.setResolution(kSensorResolutionBit);
  sensors_.setWaitForConversion(false);
  sensors_.requestTemperatures();

  inside_temperature_ = DEVICE_DISCONNECTED_C;
  outside_temperature_ = DEVICE_DISCONNECTED_C;
}

void Sensors::Loop() {
  inside_temperature_ = sensors_.getTempC(kInsideSensorAddress);
  outside_temperature_ = sensors_.getTempC(kOutsideSensorAddress);
  sensors_.requestTemperatures();
}
