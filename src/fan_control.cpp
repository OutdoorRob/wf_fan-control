// from Arduino framework
#include <Arduino.h>

// project
#include <fan_control.hpp>


FanControl::FanControl(uint8_t fan_pin) {
  fan_pin_ = fan_pin;
  pinMode(fan_pin_, OUTPUT);
  SwitchOffFan();
}

bool FanControl::Control(float inside_temperature, float outside_temperature) {
  if ((-40 <= inside_temperature)
      && (80 >= inside_temperature)
      && (-40 <= outside_temperature)
      && (80 >= outside_temperature)) {

    float __temperature_difference = inside_temperature - outside_temperature;

    if ((outside_temperature >= kSwitchOnOutsideTemperature)
        && (__temperature_difference >= kSwitchOnTemperatureDifference)) {
      SwitchOnFan();
    }
    else if ((outside_temperature <= kSwitchOffOutsideTemperature)
              || (__temperature_difference <= kSwitchOffTemperatureDifference)) {
      SwitchOffFan();
    }

    ResetErrorTimer();

    return true;
  }
  else {                      // for safety switch fan off if there aren't any valid measurements for an extended period
    if (error_timer_ > 0) {
      error_timer_--;
      return true;
    }
    else {
      SwitchOffFan();
      return false;
    }
  }
}
