  #include <iostream>
    #include <conio.h>
    #include <stdio.h>

    #include <WinSock2.h>
    #include <Windows.h>
    #include <sstream>
    #include <string>


    #include <fstream>


    #define SCK_VERSION 0x0202

    using namespace std;



    // bonus, nous avons pense a etablir une connexio entre PC_Client_Cours et le serveur,
    // mais par manque de temps nous l'avons juste implemente et compile
    char * rechercher_cours(char * jour){
        cout<<"fonction recherche cours"<<endl;
        char resultat[10];
        string ligne = "initial";
        bool compare = false;

        ifstream flux_fichier("emploi_du_temps.txt");

        if(flux_fichier){

            while(getline(flux_fichier,ligne) && compare==false){


                if(strcmp(jour,ligne.c_str())==0){

                    compare = true;
                    strcpy(resultat,ligne.c_str());
                }


            }//while

        }//if (flux_fichier)

    return resultat;
    }



    bool rechercher_base_donnees(char * tag_recherche){
    bool resultat = false;



    // permettra de stocker la ligne etudiee, en cours,
    string ligne = "initial";

// on ouvre un flux en lecture (input) qu'on appelle flux_fichier
    ifstream flux_fichier("base_de_donnees.txt");

//on verifie que l'ouverture du flux s'est bien passee


    if (flux_fichier){
            while( getline(flux_fichier, ligne) && resultat== false ){



                if(strcmp(tag_recherche,ligne.c_str())==0){
                    resultat= true;

                }


            }
    }
    else{
        cout<<"error : failed to open the file base_de_donnees.txt"<<endl;
    }
    cout<<endl<<endl;

    return resultat;

}





    // serveur
    int main(){
    SOCKET ConSock;
    SOCKET ListenSock;
    SOCKADDR_IN address;
    int addrsize = sizeof(address) ;

    long ok;
    char msg_recu[10];




    WSAData WSD;
    WORD DllVersion;
    DllVersion = MAKEWORD(2,1);
    ok = WSAStartup(DllVersion, &WSD);



    ConSock = socket(AF_INET,SOCK_STREAM,NULL);

    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_family = AF_INET;
    address.sin_port = htons(10103);

    ListenSock = socket(AF_INET,SOCK_STREAM,NULL);

    // non bloquante --> logique
    if (bind(ListenSock,(SOCKADDR *) &address, sizeof(address)) <0){
        perror("bind()");
        fprintf(stderr,"%s\n",strerror(errno));
            }


    // non bloquante --> logique
    if (listen(ListenSock,SOMAXCONN) <0){
       perror("listen()");
        fprintf(stderr,"%s\n",strerror(errno));
    }

    cout<<"Server waiting for connection \n\n"<<flush;




    while(true){


        // bloquante / attend jusqu'a qu'une demande de connexion soit demandee
        ConSock = accept(ListenSock,(SOCKADDR *) &address, &addrsize);
        if(ConSock <0)
        {
                perror("accept()");
                fprintf(stderr,"%s\n",strerror(errno));
        }
        else
            {


                char *ptr_recu = msg_recu;
                int size_recu = sizeof(msg_recu);
                while(size_recu>0)
                {

                    // recv and send sont bloquantes, tant qu'on  a pas comble l'espace indique par size, on reste dans recv
                int bytes_writed = recv(ConSock,ptr_recu,size_recu,0);
                if(bytes_writed <0)
                {
                    perror("recv()");
                    fprintf(stderr,"%s\n",strerror(errno));
                }
                size_recu -= bytes_writed;
                ptr_recu += bytes_writed;

                }

                if(strcmp(msg_recu,"lundi") == 0 || strcmp(msg_recu,"mardi")==0 || strcmp(msg_recu,"mercredi")==0){


                            char reply_cours[10] ;
                            int size_envoi_cours = sizeof(reply_cours);
                            cout<<"Recherche du cours pour le jour "<<msg_recu<<endl;
                            char * ptr_reply_cours = rechercher_cours(msg_recu);
                            strcpy(reply_cours,ptr_reply_cours);

                            while(size_envoi_cours>0)
                            {

                                //size = bloquante aussi, il faut combler tout l'espace indique par size
                                int bytes_sent_cours =  send(ConSock,ptr_reply_cours,size_envoi_cours,0);
                                if(bytes_sent_cours <0)
                                {
                                    perror("send()");
                                    fprintf(stderr,"%s\n",strerror(errno));
                                }
                                size_envoi_cours -= bytes_sent_cours;
                                ptr_reply_cours+= bytes_sent_cours;
                            }


                    }

                else{


                        bool tag_Rfid_exist ;
                        cout<<"Recherche du tag.. "<<msg_recu<<endl;
                        tag_Rfid_exist = rechercher_base_donnees(msg_recu);


                        char reply [10];

                        char * ptr_reply = reply;
                        if(tag_Rfid_exist){
                                strcpy(ptr_reply,"true");
                                cout<<"ce tag existe"<<endl;
                        }
                        else{
                                strcpy(ptr_reply,"false");
                                cout<<"ce tag n'existe pas"<<endl;
                        }
                        int size_envoi = sizeof(reply);

                        while(size_envoi>0)
                        {

                            //size = bloquante aussi, il faut combler tout l'espace indique par size
                            int bytes_sent =  send(ConSock,ptr_reply,size_envoi,0);

                            if(bytes_sent <0)
                            {
                                perror("send()");
                                fprintf(stderr,"%s\n",strerror(errno));
                            }

                            size_envoi -= bytes_sent;
                            ptr_reply+= bytes_sent;
                        }

                    } // else on cherche tag et non cours

                    cout<<endl;




        }// else connect a marche
    }// while


} // end main
