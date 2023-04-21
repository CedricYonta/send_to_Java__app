
#include "RTClib.h"
#include "heartRate.h"
#include "reset.h"
#include "connectToJava.h"

/*// Définition des informations WiFi
const char* ssid = "UNIFI_IDO1";
const char* password = "42Bidules!";*/


int buttonPin = 2;               // Connect button to input pin 2
int pushNumber ;
unsigned long firstTime;
unsigned long secondTime;

// Instantation de l'objet rtc
RTC_DS3231 rtc ;

void setup() {
  // Initialisation de la communication série
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);     // declare pushbutton as input

  // Init du RTC
   if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1)
            delay(10);
    }

    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }


  //demarer l'ecran lcd
  lcd.init();

  // Configurer le WiFi et le serveur
  setupWifiAndServer();


}

void loop() {
  // Gérer les demandes des clients
    server.handleClient();
 
 // reconfigurer l'objet
  reset(buttonPin,pushNumber,firstTime,secondTime);
   
   //capture du temps
   DateTime time = rtc.now();

   // conversion du temps en timestamp
   String date = String(time.timestamp(DateTime::TIMESTAMP_TIME));

   // construction de la chaine data
   //data = "Pulse:"+getHeartRate()+",Name:"+userName+",Date:"+date;
   data = "Pulse:215,Name:"+userName+",Date:"+date;

   if (WiFi.status() == WL_CONNECTED)
   {
      sendToJavaServer(data);
   }
   
   

   //message on lcd
   if( (WiFi.status() != WL_CONNECTED) && (!reset)){
 
      afficheLostConnection();
   }
   
   if ((!client.connect(server_address, server_port)) && (!reset)){

       afficheLostServerConnection();
   }

 
  delay(2000);
}

