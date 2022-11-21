#Dumistracel Eduard-Costin <eduard.dumistracel@stud.acs.upb.ro>
CC = g++
source = tema1.cpp process.cpp utils.cpp

build_debug: tema1.cpp process.cpp utils.h
	$(CC) $(source) -o tema1 -lpthread -Wall -Wextra -DDEBUG -g3 -O0

build: tema1.o

tema1.o: tema1.cpp process.cpp utils.h
	$(CC) $(source) -o tema1 -lpthread -Wall -Wextra
.PHONY: clean

clean:
	rm -rf *.o tema1 *.txt
