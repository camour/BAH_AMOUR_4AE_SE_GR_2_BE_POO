#ifndef DEVICES_FUSION_H_INCLUDED
#define DEVICES_FUSION_H_INCLUDED



    #include <iostream>
    #include <thread>
    #include <unistd.h>
    #include <string.h>
    #include "core_simulation_fusion.h" // car on a va etendre la classe Device
    #include <vector>
    #include <cmath>


// pour utiliser la programmation de sockets


    #include <conio.h>
    #include <stdio.h>

    #include <WinSock2.h>
    #include <Windows.h>
    #include <sstream>
    #include <string>


    #define SCK_VERSION 0x0202





    #define taille_objet 10



class Detecteurs : public Device {

public :
    Detecteurs();
    virtual bool detecter()=0; // methode abstraite, car la methode depend de la classe fille



};





// ------------------------------------------------ Buzzer -------------------------------------

class Buzzer : public Device{
  private:
    double tempsMin;
    double tempsMax; // Le temps que va sonner le buzzer
    int n; // Le nombre de demi-périodes

  public:
    // Construteur
    Buzzer();
    vector<double> linspace(double min, double max, int n); // Le vecteur du temps pour generer un signal 50% 50% à 5v et 0v
                                                            // chaque case du vecteur correspond a un pas de temps
    void tone(); // simule le fait de sonner
    virtual void run();
};





//-------------------------------------------------- classe Capteur_Presence ----------------------------------------------


class Capteur_presence : public Detecteurs{
private :
    char * boutton; // le boutton peut prendre les etat "ON" et "OFF". Le type choisi (char *)
                    // est un choix de concepteur, nous aurions pu prendre un booleen.

public :

    Capteur_presence();
    bool detecter(); // detecte la presence de personnes. La presence d'une personne est simulee par
                    // par la presence du fichier "on.txt"
    char * getBoutton(); // retourne l'etat du boutton (qui est decrit par une chaine de caractères)
    void run();

};


bool operator==(Capteur_presence const &capteur_1, Capteur_presence const &capteur_2);

//-------------------------------------------------- Detecteur_Metaux ----------------------------------------------


// il est tres important de comprendre physiquement comment nous imaginons le systeme,
// on suppose que le capteur de presence est integre dans la porte detecteur de metaux

class Detecteurs_Metaux : public Detecteurs{
    private:
        char objet_porte ; // represente l'objet porte par la personne se presentant la porte detecteur de metaux
        char  liste_metaux[4] = {'a','d','h','j'}; // pour simplifier chaque objet metallique est
                                                    //represente par un caractere. Ce tableau liste_metaux[] constitue
                                                    // donc la liste des metaux interdits
        Capteur_presence capteur_presence; // pour detecter si une personne arrive devant la porte detecteur de metaux
                                            // ce capteur sera aussi une entree de l'Arduino
        Capteur_presence capteur_presence2;




    public :
        Detecteurs_Metaux(); // Nous asssignons a l'attribut "objet_porte" un caractere
        Capteur_presence & getCapteur();
        Capteur_presence & getCapteur2();

        void sonner(); // la sonnerie (ALERTE) est materialisee  par un affichage sur le terminal
        bool detecter();
        virtual void run();

};


// ------------------------------------------------ interrupteur ------------------------------------------------------


class Interrupteur : public Device{

private :
    int state ; // 0 ou 1
public :
    Interrupteur();
    int getState();
    void setState(int i);
    virtual void run();

};


// ------------------------------------------------ SCREEN -------------------------------------

class Screen : public Device{
private:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];

public:
  // constructeur
 Screen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};



#endif // DEVICES_FUSION_H_INCLUDED
