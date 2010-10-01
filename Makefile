CPP=g++
CPPFLAGS= -Wall -pedantic -ansi -Weffc++

all:
	$(CPP) -c $(CPPFLAGS) main.cpp

clean:
	rm -f *.o
