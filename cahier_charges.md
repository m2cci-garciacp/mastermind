# MasterMind

## Contexte et définition du problème:
On a étudié les different couches réseau, où on a travaillé sur les protocoles ARP, IP, TCP et UDP. Dans ce projet, on veut faire un jeu pour jouer a distance grâce une programme serveur (en remote) et un programme client (en local).


## Objectif:
Le jeu de MasterMind peut être joué à distance grâce à un programme client. Ce programme compte avec une console qui permet l'interaction avec l'utilisateur grâce à la connexion automatique avec un serveur remote. Ceci fera tourner le jeu en distanciel.

## Spécificités techniques de l’application:
### 1. Régles du jeu: MasterMind
**1.1 Objectif**: Le jeu consiste en diviner la combination secrète de 4 couleurs. 

**1.2 Dinamique du jeu**: Au début de la partie, l'ordinateur crée une combination secréte de 4 couleurs. A chaque tour, le joueur donne une combination de 4 couleurs, après laquelle l'ordinateur va repondre :
- Combien couleurs sont dans la bonne place. 
- Combien couleurs sont présents dans la combination secrète mais sont mal placés.
Le joueur compte avec un nombre infinit d'essais mais la puntuation final depend inversement du nombre de tours utilisés.

### 2. Application au niveau réseau
L'application est implement pour pouvoir jouer à distance. Pour cela, l'application compte avec un server TCP et un client TCP. Ce protocole permet d'etablir une connexion avec le client  et s'assure de l'integrité et le transfer de tous les paquets.

**2.1 Serveur** : ce logiciel permet de jouer à distance le jeu. Il compte avec toutes les fonctions du jeu, toutes les fonctions necessaires pour traite l'information du jeu vers la connexion TCP et viceversa et toutes les fonctions necessaires pour la connexion TCP. En particulier, ce programme suit la structure d'un serveur pour protocole TCP:
- Configuration d'un port pour créer un socket d'écoute.
- Dès la connexion d'un client, il crée un socket parallele pour accepter la connexion et continue a attendre des autres connexions.
- Dans le nouveau socket, il demarre le jeu. Ce execution en parallele permet de jouer plusieurs joueurs au même temps, sans devoir attendre que les clients précedents finissent.
- Un foi le jeu fini, il ferme la connexion et le socket correspondant.

**2.2 Client** : ce logiciel permet au joueur d'interagir avec le jeu depuis son ordinateur. Ce programme est l'intermediaire entre le joueur et le jeu, executé dans le serveur. Pour cela, il compte avec des fonctions de gestion d'information entre le serveur et l'interface joueur. Cette interface est une simple console qui lit les couleurs du joeur et imprime la réponse du serveur. Ce logiciel suit la strcuture d'un client TCP:
- Dès initié, il connecte le serveur pour demarrer la partie.
- Il echange avec le serveur les actions du joeur et les réponses de l'ordinateur.
- Un foi le jeu fini, la connexion est fermé.

## Budget du projet:
Malheuresement c'est projet est gratuit.

## Délais de réalisation de l’app:
Livraison le 24/11/2023.

