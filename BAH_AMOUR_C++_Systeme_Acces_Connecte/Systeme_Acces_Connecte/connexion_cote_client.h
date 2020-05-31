#ifndef CONNEXION_COTE_CLIENT_H_INCLUDED
#define CONNEXION_COTE_CLIENT_H_INCLUDED



    #include <iostream>
    #include <thread>
    #include <unistd.h>
    #include <string.h>
    #include "core_simulation_fusion.h"
    #include "devices_fusion.h"
    #include <vector>


    // pour utiliser la programmation de sockets


    #include <conio.h>
    #include <stdio.h>

    #include <WinSock2.h>
    #include <Windows.h>
    #include <sstream>
    #include <string>


    #define SCK_VERSION 0x0202

    // ------------------------------------------------ classe Erreur_Adresse_IP -------------------------------------

    // classe d'exception liee au mauvais addresse IP du serveur
    class Erreur_Adresse_IP{
        private :
            string adresse_IP; // contiendra l'adresse recherchee, qui sera erronnee

        public :
            Erreur_Adresse_IP(string adresse);

            string getAdresse();
    };


// ------------------------------------------------ classe Connexion_Device -------------------------------------

    class Connexion_Device : public Device{
    protected :
        char addr_IP_Server[10] ; // contient l'adresse IP du serveur distant
        int port_Serveur ; // numero le port permettant d'acces au programme tournant sur le serveur
        SOCKET sock;
        SOCKADDR_IN address;
        char Buf_Client_Board[100]; // stocke les messages provenant de l'Arduino
        char Buf_Client_Send[10]; // zone memoire qui contient les messages a envoyer au serveur
        char Buf_Client_Receive[10];// zone memoire qui contient les message envoyes PAR le serveur


    public :
        Connexion_Device();
        void construire_Adresse_Serveur();

    };





// ------------------------------------------------ Classe PC_Client -------------------------------------

class PC_Client : public Connexion_Device{

private :

    Interrupteur interrupteur; // permet de signaler a l'arduino si la sequence que l'arduino
                            //a envoye au PC_CLIENT est valide ou non



public :
    PC_Client();

    char * analyser_Tag(char * message); // analyse une sequence RFID contenue dans le badge d'un employe
                                        // bien comprendre que l'Arduino, pour demander au PC Client d'envoyer
                                        // faire analyser le tag RFID, doit envoyer un message au PC Client
                                        // via le bus I2C. Ce message devant etre de la forme :
                                        // "Server sequence_RFID". Avec cette fonction analyser_tag, on vient alors
                                        // extraire le tag RFID contenu dans le mesg envoye par l'Arduino
    bool ask_Serveur(char * tag); // se connecte au serveur distant et demande au serveur si cette sequence existe

    Interrupteur& getInterrupteur();

    virtual void run();

};


// ------------------------------------------------ Classe PC_Client -------------------------------------

// Cette classe represente un PC qui se connecte au serveur distant pour connaitre le cours de la journee
// en fonction du jour actuel. Donc le pc envoit le jour au serveur et le serveur renvoit le cours associe
// ceci pour ensuite afficher le cours de la journee sur le terminal du pc


class PC_Client_Cours : public Connexion_Device{

private :

    vector<char *> emploi_du_temps; // contient les jours de la semaine (seulement les jours lundi, mardi et mercredi)



public :
    PC_Client_Cours();

    char * analyser_Requete(); // analyse si la board demande l'emploi du temps et dans ce cas renvoit un jour aleatoire
    void ask_Serveur(char * jour); // demande au serveur le cours du jour


    virtual void run();

};









#endif // CONNEXION_COTE_CLIENT_H_INCLUDED
