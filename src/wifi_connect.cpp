// from Arduino framework
#include <Arduino.h>
#include <ESP8266WiFi.h>

// project
#include <wifi_connect.hpp>
#include <wifi_user.hpp>


#ifdef WIFI_ENABLED
  #define WIFI_MODE_STA   WIFI_STA

  #define STA_CONFIG                                    // Einkommentieren wenn der ESP im STA Modus dem Router die IP mitteilen soll.

  #ifdef STA_CONFIG
    IPAddress staticIP(192, 168, 178, 201);             // Statische IP des NodeMCU ESP8266
    IPAddress gateway(192, 168, 178, 1);                // IP-Adresse des Router
    IPAddress subnet(255, 255, 255, 0);                 // Subnetzmaske des Netzwerkes
    IPAddress dns(192, 168, 178, 1);                    // DNS Server
  #endif
#else
  #define WIFI_MODE_STA  WIFI_OFF
#endif

#ifdef AP_ENABLED
  #define WIFI_MODE_AP   WIFI_AP

  #define AP_CONFIG                                     // Auskommentieren falls die Standard Konfiguration des Esp8266 AP verwendet werden soll.

  #ifdef AP_CONFIG
    IPAddress apIPv4(10, 0, 0, 1);                      // Eigene IP des Esp8266 Access Point
    IPAddress apsubnet(255, 0, 0, 0);                   // Subnetzmaske des Netzwerkes
  #endif
#else
  #define WIFI_MODE_AP  WIFI_OFF
#endif

void Wifi_connect() {                                   // Funktionsaufruf "connectWifi();" muss im Setup eingebunden werden.
  WiFi.persistent(false);                               // Auskommentieren wenn Netzwerkname und Passwort in den Flash geschrieben werden sollen.
  WiFi.mode((WiFiMode_t)(WIFI_MODE_STA | WIFI_MODE_AP));
  yield();                                              // Erforderlich, wenn die WiFi Settings" nicht aus dem Flash gelesen werden können.

  #ifdef AP_ENABLED
    #ifdef AP_CONFIG
      WiFi.softAPConfig(apIPv4, apIPv4, apsubnet);
    #endif

    if (WiFi.softAP(kApSsid, kApPassword)) {
      Serial.printf(PSTR("Der Esp stellt einen Access Point zur Verfügung SSID:\"%s\" PW:\"%s\"\nGib die IP %s im Browser ein.\n\n"),
                    WiFi.softAPSSID().c_str(), WiFi.softAPPSK().c_str(), WiFi.softAPIP().toString().c_str());
    } else {
      Serial.println(PSTR("Fehler beim erstellen des AP."));
    }
  #endif

  #ifdef WIFI_ENABLED
    #ifdef STA_CONFIG
      WiFi.config(staticIP, gateway, subnet, dns);
    #endif

    WiFi.begin(kWifiSsid, kWifiPassword);
    while (WiFi.status() != WL_CONNECTED && millis() < 8000) yield();
    Serial.println(millis());
    if (WiFi.isConnected()) {
      Serial.printf(PSTR("Verbunden mit Station: %s\nEsp8266 IP: %s\n\n"), WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
    }
    else {
      WiFi.disconnect();
    }
  #endif
}