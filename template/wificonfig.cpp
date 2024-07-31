#include <ESP8266WiFi.h>
//#include <WiFi.h> // ESP32 WROOM
#include "wificonfig.h"
#include "config.h"
#include "state.h"
#include "utils.h"

const char* ssid = "";
const char* pass = "";

String header;
String lastclient;
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

WiFiServer server(80);

void setupWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    Serial.print("Conectando-se a rede wifi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.print("\nConectado a rede ");
    Serial.print(ssid);
    Serial.print(" com endereço IP: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void printClientInfo(WiFiClient cli) {
  Serial.print("> Nova requisição: ");
  Serial.println(cli.remoteIP());
}

void sendErrorNotFound(WiFiClient cli) {
  cli.println("HTTP/1.1 404 Not Found\r\nContent-type:text/html\r\nConnection: close\r\n\r\n");
}

void sendRequisitionError(WiFiClient cli) {
  cli.println("HTTP/1.1 501 Not Implemented\r\nContent-type:text/html\r\nConnection: close\r\n\r\n");
}

void sendJson(WiFiClient cli, String json) {
  cli.println("HTTP/1.1 200 OK\r\nContent-type:application/json\r\nAccess-Control-Allow-Origin: *\r\nConnection: close\r\n\r\n");
  cli.println(json);
  cli.println();
}

void sendResponseHome(WiFiClient client) {
  // Header
  client.println("HTTP/1.1 200 OK\r\nContent-type:text/html\r\nConnection: close\r\n\r\n");
  // Mostra uma página
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
  client.println("<body><h1>ESP32 Web Server</h1>");
  client.println("</body></html>");            
  // A resposta HTTP termina com uma linha linha em branco
  client.println();
}

void handleClient(State& state, bool isDev) {

  WiFiClient client = server.available();
  header = "";

  if (client) {
    // Previne imprimir alertas de novo IP quando é o mesmo IP da requisição anterior.
    String ip = (client.remoteIP()).toString();
    if( ip != lastclient ) {
      printClientInfo(client);
      lastclient = ip;
    }

    currentTime = millis();
    previousTime = currentTime;
    String currentLine = "";
    String json = "{}";

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            if (header.indexOf("GET /home") >= 0) {
              Serial.println("GET /home");
              sendResponseHome(client);
            } else if (header.indexOf("GET /info") >= 0) {
              Serial.println("GET /info");
              json = "{\"version\": \"";
              json += 1;
              json += "\"}";
              sendJson(client, json);
            } else {
              int pos = header.indexOf("GET /");
              if (pos >= 0) {
                int endPos = header.indexOf(' ', pos + 4);
                if (endPos >= 0) {
                  String pageRequested = header.substring(pos + 4, endPos);
                  Serial.print("[Erro 404]: ");
                  Serial.println(pageRequested);
                  sendErrorNotFound(client);
                } else {
                  Serial.println("[Erro 501]: Requisição mal formatada].");
                  sendRequisitionError(client);
                }
              } else {
                Serial.println("[Erro 501]: Requisição HTTP não encontrada.");
                sendRequisitionError(client);
              }
            }
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
}
