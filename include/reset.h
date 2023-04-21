// activer la configuration de l'objet
#include "function.h"


//faire un reset si l'utilisateur appuis deux fois sur le bouton ou le maintient
 bool reset(int buttonPin, int pushNumber, unsigned long firstTime,unsigned long secondTime){
     unsigned long minTime = 5000;

     if (digitalRead(buttonPin) && pushNumber == 0)
    {
        pushNumber += 1;
       firstTime = millis();
    }
 
    
    if (digitalRead(buttonPin) && pushNumber == 1 )
    {
       pushNumber = 0;
       secondTime = millis();
    }


    if ((secondTime-firstTime) >= minTime )
    {
      // Configurer le WiFi et le serveur
      setupWifiAndServer();
      afficheReset();
      return true;
    }

}