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
    

Un autre fichier est important pour la programmation socket et qu'il faut ajouter aux options de compilation (build options)
(sous windows), ce qui parait peut-être compliqué mais c'est très facile à réaliser (5 min maximum)
	Nous avons besoin de récupérer un fichier important à indiquer au compilateur, qui est  "libws2_32.a" : 

	1. Nous l'avons place dans le repository, mais ce n'est pas sûr que ça marche (Attention, nous ne pensons pas
	qu'il faut faire un include de ce fichier. Ici il s'agit de dire au compilateur qu'on utilise un tel fichier

	Pour ce faire,

	2. il faut aussi disposer de l'IDE Dev-Cpp (  vraiment très facile à télécharger, en qques minutes) et
	 dans ce cas, ouvrir l'IDE Code::Blocks puis ->clique droit sur le projet (ici les projets sont "Serveur" et "BE_Cpp_Fusion") 
	-> build options (vers le bas de la fenêtre qui est apparue après avoir fait clique droit sur le projet)
	-> se rendre dans l'onglet "linker settings" -> dans l'onglet en bas à gauche, cliquer sur "add"
	-> une petite fenêtre apparaît -> cliquer sur le petit onglet avec le dossier et une flèche. Il faut alors aller chercher
	 le fichier en suivant ce chemin : 
	 C:/programmes(x86)/Dev-Cpp/. Une fois dans ce dossier, taper "libws2_32.a" et alors les fichiers de ce nom apparaitront
	-> cliquer sur celui de la plus petite taille (il fait 233 Ko à peu près)
	


Utilisation et execution du systeme: 
Pour tester le systeme, il faut : 
1. lancer en premier l'exécutable associé à server.cpp (projet "Serveur" inclus dans le dossierServeur), le serveur se mettra en attente de connexion
2. lancer en second l'exécutable associé au projet (projet "BE_Cpp_Test_Fusion" inclus dans le dossier Systeme_Acces_Connecte
lui-même inclus dans BAH_AMOUR_C++_Systeme_Acces_Connecte/)

Il y a donc deux executables, un par terminal.



Concernant les exigences du cahier des charges : 

	-Nous avons redefini l'operateur de comparaison pour la classe 
 	Capteur_presence. Cet operateur est utilise dans le fichier Device_fusion.cpp plus precisement 
	dans la methode run() de la classe detecteur_Metaux.
	
	- Nous avons cree une classe d'exception "Erreur_Adresse_IP" dans le fichier connexion_cote_client.h. Une instance de la classe
	Erreur_Adresse_IP est lance dans le fichier connexion_cote_client.cpp dans la methode construire_Adresse_Serveur.

	- Nous avons utilise la STL à plusieurs endroits notamment pour la classe Buzzer (fichier Devices_fusion.h) 
	ou encore la classe Lecteur_RFID (fichiers core_simulation_fusion.h)


NB : Le mot "fusion" est utilisé pour notre projet car nous avons réuni nos codes




