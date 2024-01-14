// from Arduino framework
#include <Arduino.h>
#include <ESP8266WebServer.h>

// 3rd party
#include <Bounce2.h>
#include <ElegantOTA.h>

// project
#include <display.hpp>
#include <fan_Control.hpp>
#include <main.hpp>
#include <sensors.hpp>
#include <wifi_connect.hpp>

// web server interface
ESP8266WebServer server(80);

// time cycle
uint32_t timecycle_start;
uint32_t timecycle_current;

// peripherals
Display display;
FanControl fan_control(kFanRelayPin);
Sensors sensors(kOneWirePin);


void setup() {
  sprintf(display.sw_version_, "SW: %u.%u.%u", kSoftwareVersionMajor, kSoftwareVersionMinor, kSoftwareVersionBuild);
  sprintf(display.ip_ap_, "IP: %u.%u.%u.%u", apIPv4[0], apIPv4[1], apIPv4[2], apIPv4[3]);

  // debug only
  Serial.begin(115200);

  // wifi
  Wifi_connect();

  // web server
  server.on("/", []() {
    char __idn[100];
    sprintf(__idn, "HW: 0x%08X / %u / %u / %u \r\nSW: %u.%u.%u\r\n",
            kHardwareVersionModuleId, kHardwareVersionVariant,
            kHardwareVersionMajor, kHardwareVersionMinor,
            kSoftwareVersionMajor, kSoftwareVersionMinor, kSoftwareVersionBuild);
    
    server.send(200, "text/plain", __idn);
  });

  ElegantOTA.begin(&server);            // implements update over web browser 'http://ip/update'

  server.begin();
  Serial.println("HTTP server started");

  InitLEDs();
  InitButton();

  // time cycle
  timecycle_start = millis();
}


void loop() {
  timecycle_current = millis();

  ElegantOTA.loop();

  server.handleClient();

  // buttons
  if (push_button.update()) {
    if (push_button.fell()) {
      display.ResetDisplayTimer();
    }
  }

  // every second
  if ((timecycle_current - timecycle_start) >= 1000) {
    timecycle_start = timecycle_current;

    // LED handling
    isOnRunLed() ? SwitchOffRunLed() : SwitchOnRunLed();

    // sensor handling
    sensors.Loop();

    // fan handling
    if (fan_control.Control(sensors.inside_temperature_, sensors.outside_temperature_)) {
      SwitchOffErrorLed();
    }
    else {
      SwitchOnErrorLed();
    }

    // display handling
    if (DEVICE_DISCONNECTED_C != sensors.inside_temperature_) {
      sprintf(display.inside_temperature_, "Ti: %.2f \xb0""C", sensors.inside_temperature_);
    }
    else {
      sprintf(display.inside_temperature_, "Ti: /");
    }

    if (DEVICE_DISCONNECTED_C != sensors.outside_temperature_) {
      sprintf(display.outside_temperature_, "Ta: %.2f \xb0""C", sensors.outside_temperature_);
    }
    else {
      sprintf(display.outside_temperature_, "Ta: /");
    }

    display.Loop();

    // debug
    // if (sensors.getDS18Count() == 1) {
    //   uint8_t __tempDeviceAddress[16];
    //   if (sensors.getAddress(__tempDeviceAddress, 0)) {
    //     Serial.println((char*)__tempDeviceAddress);
    //   }
    // }
  }
}
