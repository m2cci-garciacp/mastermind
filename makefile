
OBJ1 = fon.o client.o 
OBJ2 = fon.o serveur.o 
OBJ3 = fon.o serveur_dummy.o 
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

EXEC = ${OBJ1} client ${OBJ3} serveur_dummy
all: ${EXEC} 	


fon.o :  fon.h fon.c
	echo "Build fon.o"
	gcc -DDEBUG -c fon.c
	#gcc -c fon.c

client.o : fon.h	client.c 
	echo "Build client.o"
	gcc  $(CFLAGS) -c  client.c	

mastermind.o : mastermind.c	mastermind.h
	echo "Build mastermind.o"
	gcc  $(CFLAGS) -c  mastermind.c	

serveur_dummy.o : fon.h	serveur_dummy.c
	echo "Build serveur_dummy.o"
	gcc  $(CFLAGS) -c  serveur_dummy.c	

#serveur.o : fon.h	serveur.c	mastermind.h
#	echo "Build serveur.o"
#	gcc  $(CFLAGS) -c  serveur.c	

client : ${OBJ1}
	echo "Build client"	
	gcc $(LFLAGS) ${OBJ1} -o client -lcurses   $(OPTIONS)

serveur_dummy : ${OBJ3}	
	echo "Build serveur_dummy"	
	gcc $(LFLAGS) ${OBJ3} -o serveur_dummy -lcurses   $(OPTIONS)

#serveur : ${OBJ2}	
#	echo "Build serveur"	
#	gcc $(LFLAGS) ${OBJ2} -o serveur -lcurses   $(OPTIONS)



clean : 
	rm -f ${EXEC} core

