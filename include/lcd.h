#include "DFRobot_RGBLCD1602.h"

// instance de l'objet DFRobot_RGBLCD1602
DFRobot_RGBLCD1602 lcd(/*lcdCols*/16,/*lcdRows*/2);  //16 characters and 2 lines of show

void afficheReset(){

// lcd writing
  lcd.setCursor(0,0);
  lcd.print("device in ");
  lcd.setCursor(0,1);
  lcd.print("configuration mode");
  lcd.autoscroll();
}

//si l'objet est connecter à un wifi
void afficheConnected(String WiFiSsid){

  lcd.setCursor(0,0);
  lcd.print("connected to ");
  lcd.setCursor(0,1);
  lcd.print("WiFi:");
  lcd.print(WiFiSsid);

}

//si la connexion WiFi est perdu
void afficheLostConnection(){
  lcd.setCursor(0,0);
  lcd.print("lost connection");
  lcd.setCursor(0,1);
  lcd.print("WiFi");
    
}

// si la connexion au server est perdu
void afficheLostServerConnection(){
  lcd.setCursor(0,0);
  lcd.print("lost Java server");
  lcd.setCursor(0,1);
  lcd.print("connection");

}