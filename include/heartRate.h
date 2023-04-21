//#define heartratePin A1
#include "DFRobot_Heartrate.h"

int heartratePin;

// instaciation de l'objet DFRobot_Heartrate
DFRobot_Heartrate heartrate(DIGITAL_MODE); ///< ANALOG_MODE or DIGITAL_MODE

String getHeartRate(){

  uint8_t rateValue;
  heartrate.getValue(heartratePin); ///<  foot sampled values
  rateValue = heartrate.getRate(); ///< Get heart rate value 
  String rateValueString = String(rateValue);// valeur converis en String

  return rateValueString;
}