#include "core_simulation_fusion.h"

#include "devices_fusion.h"

#include "connexion_cote_client.h"


int main(){
  // creation d'une board
    Board esp8266;

    // creation de la porte detecteur de metaux
    Detecteurs_Metaux detecteurs_Metaux;

    // creation du lecteur RFID

    Lecteur_Rfid lecteur;

    // creation du PC Client

    PC_Client client;


    // Creation de l'ecran d'affichage Screen

    Screen screen;
    Buzzer buzz;



    //esp8266.i2c(3,screen);
    esp8266.set_Rfid(lecteur);
    esp8266.pin(2,client.getInterrupteur());
    esp8266.i2c(2,client);
    esp8266.pin(0,detecteurs_Metaux.getCapteur());
    esp8266.pin(1,detecteurs_Metaux.getCapteur2());
    esp8266.i2c(1,detecteurs_Metaux);

    esp8266.pin(4, buzz);

    esp8266.i2c(3,screen);





    esp8266.run();









  // achat des senseurs et actionneurs
  /*AnalogSensorTemperature temperature(DELAY,TEMP);
  DigitalActuatorLED led1(DELAY);
  IntelligentDigitalActuatorLED led2(DELAY);
  I2CActuatorScreen screen;
  AnalogSensorLuminosity luminosite(DELAY);
  ExternalDigitalSensorButton button;*/

  // branchement des capteurs actionneurs
 /* esp8266.pin(1,temperature);
  esp8266.pin(0,led1);
  esp8266.pin(3,led2);
  esp8266.pin(2,luminosite);
esp8266.pin(4,button);
  */


  // allumage de la carte


  return 0;
}


