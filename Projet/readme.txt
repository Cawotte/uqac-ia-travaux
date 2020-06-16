Equipe :
ENSUQUE Elie ENSE21059700
PARDIEU Arthur PARA28019709
PETIT Clémence ????
RAHMOUN Medhi ????

Projet sur Raven

Travail effectué :

a) Agrandir les ensembles flous de la désirabilité du lance-roquettes.

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
		

