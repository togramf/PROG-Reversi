
CC=g++
CFLAGS=-Wall 

reversi.exe: main.o jeu.o liste.o jeton.o
	$(CC) -o $@ $^
	

jeu.o: jeu.cpp jeu.h liste.h jeton.h
	$(CC) -o $@ -c $< $(CFLAGS)

liste.o: liste.cpp liste.h jeton.h 
	$(CC) -o $@ -c $< $(CFLAGS)

jeton.o: jeton.cpp jeton.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
