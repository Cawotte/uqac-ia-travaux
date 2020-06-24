Equipe :
ENSUQUE Elie ENSE21059700
PARDIEU Arthur PARA28019709
PETIT Clémence PETC25629800
RAHMOUN Mehdi RAHM26069704

--------------------
Projet sur Raven
--------------------

Travail effectué :

a) Agrandir les ensembles flous de la désirabilité du lance-roquettes.

	- Agrandissement des ensembles flous utilisés dans la désirabilités du lance-roquettes et ajout de règles :
		- La distance a désormais des créneaux "moyen-près" et "moyen-loin"
		- Les munitions ont désormais des créneaux "pas mal de munitions" et "assez de munitions"
		- La désirabilité a désormais des créneaux "plutôt désirable" et "pas trop désirable".
	- Les règles ont été augmentés au nombre de 25 pour ajouter toutes les possibilités.

	- Toutefois, j'ai mal interprété la consigne quand j'ai commencé à travailler sur la question, et avais d'abord ajouté :
		- Deux nouvelles variables flous "Points de vie restant" et "Temps restant de rechargement" pour calculer la désirabilité
		- J'ai ajouté 9 nouvelles règles les concernants et prenant en compte avec le reste des ensembles flous.

	Après m'être rendu compte de mon erreur j'ai préféré garder la fonctionnalité plutôt que la supprimer, car elle donne
	aussi de bons résultats, et enrichit le calcul de la désirabilité. 

b) Modifier la visée de l'agent pour utiliser un comportement flou.

	- Ajouts d'ensemble flou pour calculer la précision d'une arme. Trois ensemble sont pris en paramètres :
		- La distance entre le tireur et la cible.
		- La vitesse maximale du projectile de l'arme.
		- Le temps que la cible a été visible.
		Une fois les règles calculés, elles sont défuzzifiés pour donner la quantité d'imprécision de l'arme. 
		L'imprécision est ajouté aléatoirement entre la droite et la gauche.
		- Je ne vais pas détailler ici toutes les règles, mais elles suivent ces principes :
			- Plus la cible a été longtemps visible, plus on est précis. Moins la cible a été longtemps visible, moins on est précis.
			- Plus on est proche de la cible, plus on est précis. Plus on est loin de la cible, moins on est précis.
			- Plus le projectile va vite, plus il est précis. Moins il va vite, moins on est précis.

c) Permettre à un joueur humain d'avoir une équipe et les faire coopérer.

	- Quand un bot est possédé par un humain, une équipe est crée et deux bots en faisant partie sont rajoutés, l'humain devient Leader.
	- Les membres d'une même équipe partagent une même couleur et ne se tirent pas dessus.
	- Quand le joueur humain fait un double clic gauche sur un ennemi, il devient la cible de l'équipe qui va chercher
	à l'attaquer. (Il y a un message dans les logs pour l'indiquer)
	- Quand l'équipe est générée, une zone d'équipe est crée à l'endroit où le Leader se trouve.
		- Si possible, les membres de l'équipe respawn dans cette zone.
		- Lorsqu'un un membre de l'équipe meurt, ses armes apparaissent dans le spawn.

d) Création d'un bot apprenant à partir de l'humain.

	- Mise en place de collecte de données concernant le comportement des bots lorsqu'ils sont contrôlés par l'humain.
	- Utilisation du réseau de neurones pour apprendre du comportement de l'humain lorsque suffisamment de données ont été collectées.
	- Application des données et de l'apprentissage sur un nouveau type de bot, qui tire selon le comportement qu'il a appris par l'humain.
		


e) Implémenter un nouveau but
	- Ajout d'un nouveau but "se cacher", le bot va se cacher si les conditions suivantes se présentent
		- son niveau de vie est bas
		- il n'y a pas d'objet de soin disponible
	- Comportement adopté par le bot pour réaliser le but : le bot fuit sa cible jusqu'à ce que celle-ci soit à une distance suffisante, 
	  auquel cas le bot reste immobile en attendant la réapparition d'un objet de soin
	- Implémentation : Evaluateur du but, but et ajout d'un comportement flee au steeringbehavior du bot


