#ifndef MAIN_H
#define MAIN_H
// librairies utilisées
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WebServer.h>
#include <EEPROM.h>
#include "lcd.h"
#include "SPI.h"




// Create an instance of the server
WebServer server(80);

//céer l'instance de l'objet WiFiClientSecure
WiFiClient client;

const char* ssid = "ESP32-Access-Point-Cedric";
const char* password = "987654321";

// Adresse IP et port du serveur
const char* server_address = "192.168.1.159";
int server_port = 8000;
String ssid2 ;
String password2 ;
String serverAddressString ;
String serverPort ;

// variable pour le String à envoyer à l'App Java
String data ;
String userName;

 // Define the HTML form
const char* html = "<html>\
<head>\
  <style>\
    body {\
      display: flex;\
      justify-content: center;\
      align-items: center;\
      height: 100vh;\
      font-size: 18px;\
      margin: 0;\
			padding: 0;\
    }\
    form {\
      display: flex;\
      flex-direction: column;\
      align-items: center;\
      max-width: 400px;\
			width: 100%;\
			padding: 20px;\
			background-color: #f7f7f7;\
			box-shadow: 0px 0px 10px rgba(0,0,0,0.3);\
			border-radius: 10px;\
    }\
    label {\
      font-weight: bold;\
      margin-top: 10px;\
    }\
    input[type='text'], input[type='password'] {\
      width: 100%;\
      padding: 5px;\
      margin: 5px 0;\
      border: none;\
      border-bottom: 1px solid gray;\
      outline: none;\
    }\
    input[type='submit'] {\
      width: 100%;\
      margin-top: 20px;\
      padding: 10px;\
      background-color: #4CAF50;\
      color: white;\
      border: none;\
      cursor: pointer;\
      border-radius: 5px;\
    }\
  </style>\
</head>\
<body>\
   <div><h2> CONNECT TO WiFi </h2> \
  <form method='post' action='/form'>\
    <label for='userName'>user name:</label>\
    <input type='text' name='userName'>\
    <label for='ssid'>SSID:</label>\
    <input type='text' name='ssid'>\
    <label for='password'>Password:</label>\
    <input type='password' name='password'>\
    <label for='sever'>server adress:</label>\
    <input type='text' name='server'>\
    <label for='severPort'>server port:</label>\
    <input type='number' name='serverPort'>\
    <input type='submit' value='Submit'>\
  </form></div>\
</body>\
</html>";


//récupérer les données entrer dans le formulaire pour se connecter au wifi pui à l'application Java
void handleForm() {
  ssid2 = server.arg("ssid");
  password2 = server.arg("password");
  serverAddressString = server.arg("server");
  serverPort = server.arg("serverPort");
  userName = server.arg("userName");

  //convertir l'adresse du server Java et le port
  server_address = serverAddressString.c_str();
  server_port = serverPort.toInt();

  //verifier sur le moniteur serie
  Serial.println("nom d'utilisateur:"+ userName);
  Serial.println("server java ip: " + serverAddressString);
  Serial.println("server java ip en char:" + String(server_address));
  Serial.println("server java port: " + serverPort);
  Serial.println("SSID: " + ssid2);
  Serial.println("Password: " + password2);

  // Close the access point when done
  WiFi.softAPdisconnect(true);

  // Connect to Wi-Fi network
  WiFi.begin(ssid2.c_str(), password2.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  //afficher sur l'ecran lcd
  afficheConnected(ssid2);

  // Connect to server Java
  client.connect(server_address, server_port);

   // Print the IP address of the server
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Send a response to the client
  server.send(200, "text/html", "SSID: " + ssid2 + "<br>Password: " + password2);
}

// Set up the server routes
void setupRoutes() {
  // Serve the HTML form on the root path
  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", html);
  });

  // Handle the form submission
  server.on("/form", HTTP_POST, handleForm);
}

// Set up the server routes and start the server
void startServer() {
  setupRoutes();
  server.begin();
  Serial.println("Server started");
}

// Connect to Wi-Fi and start the server
void setupWifiAndServer() {
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);


  // Start the server
  startServer();

 
}

#endif /* MAIN_H */