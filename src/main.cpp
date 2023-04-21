#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

// Définition des informations WiFi
const char* ssid = "UNIFI_IDO1";
const char* password = "42Bidules!";

// Adresse IP et port du serveur
const char* server_address = "192.168.1.159";
int server_port = 8000;



//objet client
WiFiClient client;

void setup() {
  // Initialisation de la communication série
  Serial.begin(9600);

 // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");


}

void loop() {
   
  // Connect to server
  client.connect(server_address, server_port);
  
  // Send data to server
  String data = "Pulse:214,Name:jeans";
  if (client.connected()) {
     // Envoi des données au serveur si la connexion est active
    client.println(data);
    Serial.println(data);
    Serial.println("Data sent to server");
  } else {
    Serial.println("Lost connection to server");
    // Try to reconnect
    if (!client.connect(server_address, server_port)) {
      Serial.println("Could not reconnect to server");
      return;
    }
  }

  delay(2000);
}

