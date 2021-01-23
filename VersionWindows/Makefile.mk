
CC=g++
CFLAGS=-Wall 

Reversi.exe: Main.o Jeu.o Liste.o Jeton.o
	$(CC) -o $@ $^
	

Jeu.o: Jeu.cpp Jeu.h Liste.h Jeton.h
	$(CC) -o $@ -c $< $(CFLAGS)

Liste.o: Liste.cpp Liste.h Jeton.h 
	$(CC) -o $@ -c $< $(CFLAGS)

Jeton.o: Jeton.cpp Jeton.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
