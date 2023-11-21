# MasterMind

## Contexte et définition du problème:
On a étudié les different couches réseau et on a travaillé sur les protocoles ARP, IP, TCP et UDP. Dans ce projet, on va programmer le jeu de MasterMind pour jouer à distance grâce une programme serveur (en remote) et un programme client (en local). Ce jeu est algorithmiquement simple, ce qui nous permets de nous centrer sur la partie réseau.


## Objectif:
Le jeu de MasterMind peut être joué à distance grâce à un programme client, qui tourne chez le joueur, et un programme serveur, qui tourne en remote. La partie client contient une console pour interagir avec l'utilisateur et communique avec le serveur, qui fait tourner le jeu en distanciel.

## Spécificités techniques de l’application:
### 1. Régles du jeu: MasterMind
**1.1 Presentation** : MasterMind est un jeu  de réflexion et de déduction pour deux joueurs dont le but est de trouver la combinaison secréte de 4 couleurs entre les 6 coleurs disponibles. Originalement, il y a un joueur qui crée la combinaison, codeur, et l'autre essaie de la déchiffrer, déchiffreur. Dans cette version, le ordinateur joue le rôle de codeur, et l'utilisateur le rôle de déchiffreur.

**1.2 Objectif**: Le jeu consiste en diviner la combination secrète de 4 couleurs d'entre les 6 couleurs disponibles dans le moindre nombre de tours.

**1.3 Dinamique du jeu**: Au début de la partie, l'ordinateur crée une combination secréte de 4 couleurs. À chaque tour, le joueur donne une combination de 4 couleurs, après laquelle l'ordinateur va repondre :
- Combien couleurs sont dans la bonne place. 
- Combien couleurs sont présents dans la combination secrète mais sont mal placés.
La partie se fini quand le joueur trouve la combination secrète. Le nombre d'essais possible est infinit mais la puntuation finale depend inversement du nombre de tours necesités.

**1.3 Puntuation**: La puntuation finale depend inversement du nombre de tours necesités:
| Tours         | Points     |
|--------------|-----------|
| 1 | 100     |
| 2      | 90  |
| 3      | 80  |
| 4      | 70  |
| 5      | 60  |
| 6      | 50  |
| 7      | 40  |
| 8      | 30  |
| 9      | 20  |
| 10      | 15  |
| 11      | 10  |
| 12      | 5  |
| 13      | 2  |
| 14      | 1  |
| >14      | 0  |

### 2. Application au niveau réseau
L'application est implementée pour pouvoir jouer à distance. Pour cela, l'application compte avec un serveur TCP et un client TCP. Ce protocole permet d'etablir une connexion entre le client le serveur et s'assure de l'integrité et le transfer de tous les paquets.

**2.1 Serveur** : ce logiciel permet de jouer à distance le jeu. Il compte avec toutes les fonctions necessaires pour la connexion TCP, toutes les fonctions du jeu, ainsi que toutes les fonctions necessaires pour traiter l'information du jeu à partir du format reçu par le réseau et viceversa. En particulier, ce programme suit la structure d'un serveur pour protocole TCP:
- Configuration d'un port pour créer un socket d'écoute.
- Dès la connexion d'un client, il crée un processus parallèle pour la nouvelle connexion, tandis que dans le processus principal le logiciel continue à écouter pour des autres connexions.
- Dans le nouveau socket, il demarre le jeu. Ce execution en parallèle permet de jouer plusieurs joueurs au même temps, sans devoir attendre que les clients précedents finissent.
- Un foi le jeu fini, il ferme la connexion et le socket correspondant automatiquement.

**2.2 Client** : ce logiciel permet au joueur d'interagir avec le jeu depuis son ordinateur. Ce programme est l'intermediaire entre le joueur et le jeu, executé dans le serveur. Pour cela, il compte avec des fonctions de gestion d'information entre l'interface joueur et le format du message envoyé par le réseau au serveur. Cette interface est une simple console qui lit les couleurs du joeur et imprime la réponse du serveur. Ce logiciel suit la structure d'un client TCP:
- Dès initié, il connecte le serveur pour demarrer la partie.
- Il echange avec le serveur les actions du joeur et les réponses de l'ordinateur.
- Un foi le jeu fini, la connexion est fermé.

## Budget du projet:
Malheuresement c'est projet est gratuit.

## Délais de réalisation de l’app:
Livraison le 24/11/2023.

