# BAH_AMOUR_4AE_SE_GR_2_BE_POO


Ce projet concerne un système d'accès connecté, 
qui utilise notamment une communication en mode connecté entre un client et un serveur. 
Tout le systeme est situe du cote client (board arduino, devices, pc client..)
Seul le programme du serveur est isolé 

Il y a deux dossiers-projets importants appartenant à ce repository (BAH_AMOUR_4AE_SE_GR2) :  
- "Systeme_Acces_Connecte" qui contient toute l'implementation du systeme côté client (board.cpp, core_simulation.cpp, devices.cpp..)
- "Serveur" qui contient le programme faisant tourner le serveur 

Nous avons codé sur l'IDE Codeblocks sous windows, certaines librairies sont requises pour la programmation de socket,
pour cela il faut inclure (ce qui est deja fait dans les fichiers headers) : 
    #include <WinSock2.h>
    #include <Windows.h>
    
Un autre fichier est important pour la programmation socket et qu'il faut ajouter aux options de compilation  : 
"libws2_32.a" (disponible depuis l'IDE Dev-Cpp) ou que nous avons joint dans le repository

Utilisation : 
Pour tester le systeme, il faut : 
1. lancer l'executable associe à server.cpp (projet Serveur.cbp inclus dans le dossierServeur), le serveur se mettra en attente de connexion
2. lancer l'executable associe au projet (projet BE_Cpp_Test_Fusion.cbp inclus dans le dossier Systeme_Acces_Connecte)

Il y a donc deux executables, un par terminal.



