#include "function.h"

#ifndef SEND_TO_JAVA_SERVER_H
#define SEND_TO_JAVA_SERVER_H


// fonction pour se connecter ) l'App Java et envoyer les données
void sendToJavaServer( String data){
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

}

#endif