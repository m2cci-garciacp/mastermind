
OBJ1 = fon.o client.o  mastermind.o  fonctions_aux.o
OBJ2 = fon.o serveur.o  mastermind.o  fonctions_aux.o
OBJ3 = mastermind_test.o   mastermind.o
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

EXEC = ${OBJ1} client ${OBJ2} serveur ${OBJ3} mastermind_test
all: ${EXEC} 	

# Programme principal
fon.o :  fon.h fon.c
	echo "Build fon.o"
	gcc -DDEBUG -c fon.c
	#gcc -c fon.c

client.o : fon.h	client.c	mastermind.h	fonctions_aux.h
	echo "Build client.o"
	gcc  $(CFLAGS) -c  client.c	

mastermind.o : mastermind.c	mastermind.h
	echo "Build mastermind.o"
	gcc  $(CFLAGS) -c  mastermind.c		

fonctions_aux.o : fon.h   fonctions_aux.c	fonctions_aux.h
	echo "Build fonctions_aux.o"
	gcc  $(CFLAGS) -c  fonctions_aux.c		

serveur.o : fon.h	serveur.c	mastermind.h	fonctions_aux.h
	echo "Build serveur.o"
	gcc  $(CFLAGS) -c  serveur.c	

client : ${OBJ1}
	echo "Build client"	
	gcc $(LFLAGS) ${OBJ1} -o client -lcurses   $(OPTIONS)

serveur : ${OBJ2}	
	echo "Build serveur"	
	gcc $(LFLAGS) ${OBJ2} -o serveur -lcurses   $(OPTIONS)

# test du jeu
mastermind_test : ${OBJ3}	
	echo "Build mastermind_test"	
	gcc $(LFLAGS) ${OBJ3} -o mastermind_test -lcurses   $(OPTIONS)



clean : 
	rm -f ${EXEC} core

