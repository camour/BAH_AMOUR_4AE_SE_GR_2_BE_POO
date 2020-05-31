#include "devices_fusion.h"

using namespace std;



    Detecteurs :: Detecteurs(): Device(){}


// ------------------------------------------------ classe Interrupteur -------------------------------------


    Interrupteur :: Interrupteur() : state(0){}

    int Interrupteur :: getState() {return state;}
    void Interrupteur :: setState(int i){state = i;}
    void Interrupteur :: run(){
        while(1){

                    *ptrmem = state;

            sleep(3);
        }
    }



//-------------------------------------------------- Capteur_presence----------------------------------------------

    Capteur_presence :: Capteur_presence(): Detecteurs(){strcpy(boutton,"OFF");}

    bool Capteur_presence :: detecter(){
    bool resultat;

    // on ouvre un flux en lecture vers le fichier "on.txt" qui materialise la presence de personne
    // a l'entree de la porte detecteur de metaux, on ne s'interesse a ce qu'il y a dedans
    // on veut seulement savoir si l'ouverture du flux s'est bien passee
    if(ifstream("C:\\Users\\chadi\\Desktop\\BE_C++\\BE_Cpp_Test_Fusion\\bin\\Debug\\on.txt")){


            strcpy(boutton,"ON");
            resultat = true;
        }
        else{

            strcpy(boutton,"OFF");

            resultat = false;
        }
    return resultat;
}

char * Capteur_presence :: getBoutton(){return boutton;}

void Capteur_presence :: run(){


    while(1){
            // si le fichier on.txt est detectee,on place l'entree du pin a 1(qui est place en mode INPUT)
     if (detecter()){
        *ptrmem=1;
     }
     else{
        *ptrmem=0;
     }
     //3
    sleep(3);
    }
}

// pour s'assurer que lorsqu'un capteur detecte une personne, l'autre aussi, ce qui signifiera
// alors que la personne est bien entrain de passer dans la porte et non a cote
    bool operator==(Capteur_presence &capteur_1, Capteur_presence  &capteur_2){
                bool resultat = false;
                char * boutton_1 = capteur_1.getBoutton();
                char * boutton_2 = capteur_2.getBoutton();

                if (strcmp(boutton_1,boutton_2)==0){
                    resultat = true;

                }
                return resultat;
                }

// ------------------------------------------------ Detecteurs_Metaux -------------------------------------

    Detecteurs_Metaux :: Detecteurs_Metaux() : Detecteurs(){}

    Capteur_presence & Detecteurs_Metaux :: getCapteur(){

        return (*this).capteur_presence;
    }

    Capteur_presence & Detecteurs_Metaux :: getCapteur2(){

                return (*this).capteur_presence2;

    }

    void Detecteurs_Metaux :: sonner(){


        // materialise la sonnerie
        cout<<"ALERTE ALERTE  , OBJETS METALLIQUES DETECTES  "<<endl<<endl;

    }



    bool Detecteurs_Metaux :: detecter(){

        bool resultat = false;
        int i = 0;

        while ( resultat==false && (i<4)){
            if (liste_metaux[i] == objet_porte){
                resultat = true;
            }
            i++;
        }

        return resultat;

    }

    void Detecteurs_Metaux :: run(){
        char buf[100];
        int i =0;

        while(1){

            objet_porte = (char) (97+i);
            i++;
        // ce if represente la relation physique des capteurs integres au detecteur. La detection
        //d'un metal implique en effet qu'il faut qu'il y ait une personne devant la porte detecteur de metaux
            if(capteur_presence.detecter() && capteur_presence==capteur_presence2 ){

                if(detecter()){
                    sprintf(buf,"Boutton %s , objet metallique porte : %c ",capteur_presence.getBoutton(),objet_porte);

                    i2cbus->write(i2caddr,buf,100);

                    }
                else{
                    sprintf(buf,"Boutton %s , aucun objet metallique, veuillez avancer",capteur_presence.getBoutton());
                    i2cbus->write(i2caddr,buf,100);


                    }

            }

            else{
                sprintf(buf,"aucun employe detecte");
                i2cbus->write(i2caddr,buf,100);
            }
    // une fois qu'on a parcours la liste des caracteres, on recommence
        if(i==11){
            i=0;
    }

        sleep(3);
    }
}


// ------------------------------------------------ BUZZER -------------------------------------

    Buzzer :: Buzzer():Device(){
        double tempsMin = 0;
        double tempsMax = 5; // Le temps que va sonner le buzzer (5 s)
        int n; // Le nombre de demi-période
        }

    // construit un vecteur de tensions dont chaque case vaut 0 ou 1,
    //  apres quelques recherches, nous avons vu que le signal d'un buzzer est une suite de tensions haut-bas
    // le signal renvoye par buzzer est donc une suite de tensions 0V - 5V se faisant a une certaine frequence
    vector<double> Buzzer :: linspace(double tempsMin, double tempsMax, int n){
        vector<double> result;
        // vector iterator
        int iterator = 0;

        for (int i = 0; i <= n-2; i++)
        {
            double temp = tempsMin + i*(tempsMax-tempsMin)/(floor((double)n) - 1);
            result.insert(result.begin() + iterator, temp);
            iterator += 1;
        }

	//iterator += 1;

        result.insert(result.begin() + iterator, tempsMax);
        return result;
  }


    void Buzzer:: tone() {

    int const periode(10); // On fixe la frequence de vibration du buzzer à 1Hz par souci de lisibilité à l'affichage sinon, elle est de l'odre du kHz
    vector <double> vecteur;//vecteur de tensions, chaque case vaut 0 ou 5v
        vecteur = linspace(tempsMin, tempsMax, periode); // On étale le temps, ici on considère une frequence de 1Hz donc on aura 2 demi-periode dans chaque période

    short int ton[periode];
    cout<< "BUZZER TONALITE ALERTE"<< endl;
    cout<<endl;
    for (int i=0; i<periode; i++){
        if (i%2) {
            ton[i]=5;
        }
        else ton[i]=0;
        cout<< ton[i];
    }
    }

    void Buzzer:: run() {
        while(1){
            if(ptrmem!=NULL)
        {
            if (*ptrmem==1)   /// on regarde si l'arduino nous autorise a sonner
            {
            tone();
            }
        }
        sleep(3);
        }
        }




// ------------------------------------------------ SCREEN -------------------------------------

    Screen::Screen ():Device(){}


    void Screen::run(){
        while(1){
            if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
            // on vient lire sur le bus I2C, la valeur que l'on doit afficher a l'ecran
            Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
            cout << "---screen : "<< buf << endl;
                cout<<endl;
                cout<<endl;
            }

            sleep(3);
            }
        }






