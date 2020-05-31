
    #include "connexion_cote_client.h"




    Erreur_Adresse_IP :: Erreur_Adresse_IP(string adresse){
            adresse_IP = adresse;
        }
        string Erreur_Adresse_IP :: getAdresse(){
            return adresse_IP;
        }


         // ------------------------------------------------ Classe PC_Client -------------------------------------

    Connexion_Device :: Connexion_Device():Device(),addr_IP_Server("127.0.0.1"),port_Serveur(10103){}


    void Connexion_Device :: construire_Adresse_Serveur(){

        // une adresse IP est codee sur 4 octets, chacun represente par  un nombre decimal
        // il y a donc au moins 4 chiffres dans une adresse IP + les trois points separant ces chiffres
        // exemple "127.0.01" contient bien 3 points + 6 nombres = 7"
        if(strlen(addr_IP_Server) >= 7){

                    address.sin_addr.s_addr = inet_addr(addr_IP_Server);
                    address.sin_family = AF_INET;
                    address.sin_port = htons(port_Serveur);
        }
        else{
            throw Erreur_Adresse_IP(string(addr_IP_Server));

        }
    }


    PC_Client :: PC_Client() : Connexion_Device(){}

    bool PC_Client :: ask_Serveur(char * tag){
                    bool resultat = false;
                    // si on est rentre dans cette fonction, tag est forcement non NULL
                    // On stocke la sequence du tag en cours dans un tableau, pour ne pas modifier le ptr tag
                    char * msg_send = NULL;
                    msg_send = strcpy(Buf_Client_Send,tag);
                    sock = socket(AF_INET,SOCK_STREAM,NULL);
                    try{
                        construire_Adresse_Serveur();
                    }
                    catch(Erreur_Adresse_IP  &erreur){

                        cout<<"Erreur addresse IP Serveur : "<<erreur.getAdresse()<<" n'est pas une adresse IP"<<endl;
                    }

                // le PC Client se connecte au serveur distant, il faut donc au prealable avoir lance
                // le programme du serveur qui doit etre en attente de demande de connexion
                if(connect(sock, (SOCKADDR *) &address, sizeof(address))<0){

                    perror("connect()");
                    fprintf(stderr,"%s\n",strerror(errno));
                }

                int size_envoi = sizeof(Buf_Client_Send);

                while(size_envoi>0){

                    int bytes_sent = send(sock,msg_send,size_envoi,0);

                    if(bytes_sent < 0){
                        perror("send()");
                        fprintf(stderr,"%s\n",strerror(errno));
                    }
                    size_envoi -= bytes_sent;
                    msg_send +=bytes_sent;

                }


                // apres avoir envoye la requete d'identification du tag_RFID au serveur, on se met en mode
                // " on attend la reponse du serveur


                char * ptr_recv = Buf_Client_Receive;
                int size_reception = sizeof(Buf_Client_Receive);

                while(size_reception > 0){

                    int  bytes_received = recv(sock,ptr_recv,size_reception,0);

                      if(bytes_received < 0){
                        perror("recv()");
                        fprintf(stderr,"%s\n",strerror(errno));
                      }
                      size_reception -= bytes_received;
                      ptr_recv += bytes_received;

                }

                // si msg_recu = true, cela veut dire que le tag_RFID envoye au serveur fait parti
                // des tags autorises
                if( strcmp(Buf_Client_Receive,"true") == 0 ){
                    resultat = true;

                }
                return resultat;

    }



    char * PC_Client :: analyser_Tag(char * message){

        char * resultat = message;

    if (message != NULL){

        while ((*resultat) != ' '){
            resultat++;
        }
        resultat++;

    }

    return resultat;

    }


    Interrupteur& PC_Client :: getInterrupteur(){
        return (*this).interrupteur;
    }




    void PC_Client :: run(){

        long ok;

        // Cette manip est necessaire pour prevenir le systeme qu'on va utiliser un socket
        WSAData  WSD;
        WORD DllVersion;
        DllVersion = MAKEWORD(2,1);
        ok = WSAStartup(DllVersion, &WSD);

        while(true){
            interrupteur.setState(0);
            i2cbus->requestFrom(i2caddr,Buf_Client_Board,100);


            if (strstr(Buf_Client_Board,"Server")!=NULL) // On regarde si la chaine "Server" est contenue dans le message envoye
                                                        // par l'arduino, dans quel cas, cela signifie que l'arduino
                                                        // cherche a faire analyser un tag, detecte par le lecteur RFID
                {

                char * tag = analyser_Tag(Buf_Client_Board); // on extrait le tag du message envoye par l'arduino, en effet
                                                           // on rappelle que lorsque l'arduino veut faire analyser un
                                                            // tag RFID, l'arduino doit preciser le message "Serveur sequence"

                if (tag!=NULL){


                   if( ask_Serveur(tag) == true)//on se connecte au serveur depuis l'instance
                                                //client appartenant  a la classe PC_Client
                                                // si le tag analyse appartient a la base de donnees
                                                // on valide le passage de l'employeur
                   {
                       interrupteur.setState(1);
                       cout<<"terminal PC_Client : serveur says tag " <<tag<<" exists"<<endl;
                       cout<<endl;

                   }


                }// TAG != NULL


            }// demande pour le serveur recu

        sleep(3);
        }

    }




    // ------------------------------------------------ Classe PC_Client_Cours -------------------------------------

    PC_Client_Cours :: PC_Client_Cours(): Connexion_Device(){

        emploi_du_temps.push_back("lundi");
        emploi_du_temps.push_back("mardi");
        emploi_du_temps.push_back("mercredi");

    }

// retourne un jour de cours
    char * PC_Client_Cours :: analyser_Requete(){

        char * resultat = NULL ;

        if(strlen(Buf_Client_Board)>0){

            if (strstr(Buf_Client_Board,"emploi du temps")!=NULL){
                    random_shuffle(emploi_du_temps.begin(),emploi_du_temps.end());
                    resultat = new char [10];
                    strcpy(resultat,emploi_du_temps[0]);

            }
        }
        return resultat;


    }


    void PC_Client_Cours :: ask_Serveur(char * jour){



                    char * msg_send = NULL;
                    msg_send = strcpy(Buf_Client_Send,jour);

                    sock = socket(AF_INET,SOCK_STREAM,NULL);
                    try{
                        construire_Adresse_Serveur();
                    }
                    catch(Erreur_Adresse_IP  &erreur){

                        cout<<"Erreur addresse IP Serveur : "<<erreur.getAdresse()<<" n'est pas une adresse IP"<<endl;
                    }

                // le PC Client se connecte au serveur distant, il faut donc au prealable avoir lance
                // le programme du serveur qui doit etre en attente de demande de connexion
                if(connect(sock, (SOCKADDR *) &address, sizeof(address))<0){

                    perror("connect()");
                    fprintf(stderr,"%s\n",strerror(errno));
                }

                int size_envoi = sizeof(Buf_Client_Send);

                while(size_envoi>0){

                    int bytes_sent = send(sock,msg_send,size_envoi,0);

                    if(bytes_sent < 0){
                        perror("send()");
                        fprintf(stderr,"%s\n",strerror(errno));
                    }
                    size_envoi -= bytes_sent;
                    msg_send +=bytes_sent;

                }




                char * ptr_recv = Buf_Client_Receive;
                int size_reception = 10;

                while(size_reception > 0){

                    int  bytes_received = recv(sock,ptr_recv,size_reception,0);

                      if(bytes_received < 0){
                        perror("recv()");
                        fprintf(stderr,"%s\n",strerror(errno));
                      }
                      size_reception -= bytes_received;
                      ptr_recv += bytes_received;
                      cout<<"contenu " <<ptr_recv<<endl;

                }





    }



    void PC_Client_Cours :: run(){


        long ok;

        // Cette manip est necessaire pour prevenir le systeme qu'on va utiliser un socket
        WSAData  WSD;
        WORD DllVersion;
        DllVersion = MAKEWORD(2,1);
        ok = WSAStartup(DllVersion, &WSD);

        while(true){

            i2cbus->requestFrom(i2caddr,Buf_Client_Board,100);

            char * jour = NULL;
            jour = analyser_Requete();

            if(jour!=NULL){
                ask_Serveur(jour);
                cout<<"cours ajd : "<<Buf_Client_Receive<<endl;

            }


        sleep(3);
        }

    }

