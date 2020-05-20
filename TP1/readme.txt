Equipe :
ENSUQUE Elie ENSE21059700
PARDIEU Arthur PARA28019709

Les images sont dans le dossier "images".
Le code source se trouve dans le dossier "source".
L'exécutable compilé se trouve dans le dossier "executable"

Ajouts :

3.1) Diagramme Etat-Transition modifié de Bob
3.2) Diagramme Etat-Transition de l'Alcoolique
3.3) Implémentation de l'Alcoolique
	- Nouvel Etat "FightAlcoholic" pour le mineur
	- Nouvelles classes "Alcoholic" et "AlcoholicOwnedStates" pour représenter l'alcoolique
	- Le texte de l'Alcoolique est en bleu.
	- Le combat se fait par messages. Quand Bob arrive dans le saloon, si l'Alcoholic est soûl il envoit un message à Bob pour lui dire qu'il l'attaque, qui lui renvoie ensuite un message pour lui dire qu'il riposte.
	
3.4) Captures d'écrans du programme.

3.5) QUESTIONS FACULTATIVES ------

3.5.1) 
Spécifier l'état de départ d'un agent : Au début de l'exécution ils nous ai demandé dans la console de choisir l'état de départ de chaque agent en entrant le nombre approprié.
Visualiser les messages échangées : Pas fait.

3.5.2) Implémentation Multi-threading :
	- Ajout d'une classe MultithreadManager qui crée un thread pour chaque entité  enregistré, sur laquelle les Update() de chaque agent vont être bouclés jusqu'au nombre d'itérations voulus. La classe s'occupe aussi de synchroniser les threads pour ne pas qu'ils aient des Update() d'avance sur les autres.
	- Ajout d'une classe Singleton ConsoleUtilsThreadSafe, avec des fonctions Thread-safe pour écrire dans la console et changer les couleurs de textes. (Sinon les couleurs et textes se mélangent.)
	- Modifications de tout les agents pour utiliser le printThreadSafe afin d'écrire dans la console au lieu de cout. (c'était long)	
	- Modification de MessageDispatcher pour aussi utiliser le print thread-safe.
	- On remarquera que lorsque le multithreading est utilisé, l'ordre d'exécution des Updates de chaque agent peut changer à chaque Update(), mais que personne n'a d'avance sur les autres pour autant.
	  
----- MODIFICATIONS SUPPLEMENTAIRE DE QUALITE DE VIE -----

- Au sommet de main.cpp, il y a différentes constantes modifiables pour activer/désactiver des fonctionnalités et certaines paramètres de l'exécution :
	- USE_MULTITHREADING (Activer ou non le multithreading)
	- ASK_STARTING_STATE (Demander ou non l'état de départ)
	- NB_ITERATIONS (Nombre d'itérations total de l'exécution)
	- UPDATE_SLEEP_TIME (Sleep time entre chaque Update. Peut-être mis à 0)

- Des pointeurs intelligents (unique_ptr) sont utilisé dans le main pour les agents au lieu de pointeur nues. (Pas besoin de delete les pointeurs, plus clean pour la gestion de mémoire).

