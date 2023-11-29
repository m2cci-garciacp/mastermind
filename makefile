
OBJ1 = ./connexion/fon.o ./client/client.o  ./client/mastermindClient.o  ./connexion/fonctions_aux.o  ./outils/verificationInput.o  ./outils/outils.o
OBJ2 = ./connexion/fon.o ./serveur/serveur.o  ./serveur/mastermindServeur.o  ./connexion/fonctions_aux.o  ./outils/outils.o
#OBJ3 = mastermind_test.o   mastermind.o  verificationInput.o
OPTIONS	=
# Adaptation a Darwin / MacOS X avec fink
# Du fait de l'absence de libtermcap on se fait pas mal
# cracher dessus mais ca marche...
ifeq ($(shell uname), Darwin)
LFLAGS	+= -L/opt/local/lib
CFLAGS	+= -I /opt/local/include
endif
#Changer si necessaire le chemin d'acces aux librairies

# Adaptation a Linux
ifeq ($(shell uname), Linux)
OPTIONS	+= -ltermcap
endif

# Adaptation a FreeBSD
# Attention : il faut utiliser gmake...
ifeq ($(shell uname),FreeBSD)
OPTIONS	+= -ltermcap
endif

# Adaptation a Solaris

ifeq ($(shell uname),SunOS)
OPTIONS	+= -ltermcap  -lsocket -lnsl
CFLAGS	+= -I..
endif

EXEC = ${OBJ1} clientMasterMind ${OBJ2} serveurMasterMind
all: ${EXEC} 	

# Programme principal
./connexion/fon.o :  ./connexion/fon.h ./connexion/fon.c
	echo "Build fon.o"
	#gcc -DDEBUG -c ./connexion/fon.c
	gcc -c ./connexion/fon.c -o ./connexion/fon.o

./client/client.o : ./connexion/fon.h	./client/client.c	./client/mastermindClient.h	./connexion/fonctions_aux.h  ./outils/verificationInput.h  ./outils/outils.h
	echo "Build client.o"
	gcc  $(CFLAGS) -c  ./client/client.c	-o  ./client/client.o

./client/mastermindClient.o : ./client/mastermindClient.c	./client/mastermindClient.h  ./outils/verificationInput.h  ./outils/outils.h
	echo "Build mastermindClient.o"
	gcc  $(CFLAGS) -c  ./client/mastermindClient.c	-o  ./client/mastermindClient.o

./serveur/mastermindServeur.o : ./serveur/mastermindServeur.c	./serveur/mastermindServeur.h
	echo "Build mastermindServeur.o"
	gcc  $(CFLAGS) -c  ./serveur/mastermindServeur.c	-o  ./serveur/mastermindServeur.o		

./outils/verificationInput.o : ./outils/verificationInput.c	./outils/verificationInput.h	 ./client/mastermindClient.h 
	echo "Build verificationInput.o"
	gcc  $(CFLAGS) -c  ./outils/verificationInput.c		-o  ./outils/verificationInput.o	

./outils/outils.o : ./outils/outils.c	./outils/outils.h 
	echo "Build outils.o"
	gcc  $(CFLAGS) -c  ./outils/outils.c	-o  ./outils/outils.o		

./connexion/fonctions_aux.o : ./connexion/fon.h   ./connexion/fonctions_aux.c	./connexion/fonctions_aux.h
	echo "Build fonctions_aux.o"
	gcc  $(CFLAGS) -c  ./connexion/fonctions_aux.c	-o  ./connexion/fonctions_aux.o

./serveur/serveur.o : ./connexion/fon.h	./serveur/serveur.c	./serveur/mastermindServeur.h	./connexion/fonctions_aux.h  ./outils/outils.h
	echo "Build serveur.o"
	gcc  $(CFLAGS) -c  ./serveur/serveur.c -o  ./serveur/serveur.o

client : ${OBJ1}
	echo "Build client"	
	gcc $(LFLAGS) ${OBJ1} -o clientMasterMind -lcurses   $(OPTIONS)

serveur : ${OBJ2}	
	echo "Build serveur"	
	gcc $(LFLAGS) ${OBJ2} -o serveurMasterMind -lcurses   $(OPTIONS)

# test du jeu
mastermind_test : ${OBJ3}	
	echo "Build mastermind_test"	
	gcc $(LFLAGS) ${OBJ3} -o mastermind_test -lcurses   $(OPTIONS)



clean : 
	rm -f ${EXEC} core

