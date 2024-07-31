#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <ESP8266WiFi.h>
//#include <WiFi.h> // ESP32 WROOM
#include "state.h"
extern WiFiServer server;

void setupWifi();
void handleClient(State& state, bool isDev);

#endif
