CPP=g++
CPPFLAGS= -Wall -pedantic -ansi

all:
	$(CPP) -c $(CPPFLAGS) main.cpp

clean:
	rm -f *.o
