#ifndef MAIN_HPP
#define MAIN_HPP

// from Arduino framework
#include <Arduino.h>

// 3rd party
#include <Bounce2.h>


// version information
constexpr uint8_t kSoftwareVersionMajor = 0;
constexpr uint8_t kSoftwareVersionMinor = 1;
constexpr uint8_t kSoftwareVersionBuild = 3;

#if defined(TARGET_ESP8266)

  // version information
  constexpr uint32_t kHardwareVersionModuleId = 0x46414E43;     // 'FANC'
  constexpr uint32_t kHardwareVersionVariant = 0;               // OneWire temperature sensors, I²C display
  constexpr uint8_t kHardwareVersionMajor = 0;
  constexpr uint8_t kHardwareVersionMinor = 1;

  // board definitions
  constexpr uint8_t kRunLedPin = D4;
  constexpr uint8_t kErrorLedPin = D0;
  constexpr uint8_t kPushButtonPin = D3;
  constexpr uint8_t kI2cSclPin = D1;
  constexpr uint8_t kI2cSdaPin = D2;
  constexpr uint8_t kOneWirePin = D5;
  constexpr uint8_t kFanRelayPin = D8;

#elif defined(TARGET_NANO_EVERY)

#endif


inline bool isOnRunLed() { return !digitalRead(kRunLedPin); }

inline void SwitchOnRunLed() { digitalWrite(kRunLedPin, LOW); }
inline void SwitchOffRunLed() { digitalWrite(kRunLedPin, HIGH); }

inline void SwitchOnErrorLed() { digitalWrite(kErrorLedPin, LOW); }
inline void SwitchOffErrorLed() { digitalWrite(kErrorLedPin, HIGH); }

inline void InitLEDs() {
  pinMode(kRunLedPin, OUTPUT);
  SwitchOffRunLed();
  pinMode(kErrorLedPin, OUTPUT);
  SwitchOffErrorLed();
}


Bounce push_button;

inline void InitButton() {
  pinMode(kPushButtonPin, INPUT);
  push_button.attach(kPushButtonPin);
  push_button.interval(20);
}


#endif