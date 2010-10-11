CPP=g++
CC=gcc
CPPFLAGS= -Wall -pedantic -ansi -ggdb3 -Weffc++
CCFLAGS= -Wall -pedantic -ansi

VIENNA_INCLUDE=-I/usr/local/include/ViennaRNA
VIENNA_LIBRARY=-L/usr/local/lib -lRNA
BIOPP_LIBRARY=-lbiopp

PROG=vac-o
CPP_SRC=main.cpp DevPlugin.cpp PluginAdmin.cpp CombinatoryEngine.cpp QAEngine.cpp \
SequenceOptimization.cpp SequenceRanker.cpp CombinatoryRegion.cpp SSRegion.cpp \
RNAFold.cpp RNAFoldInverse.cpp RNAForester.cpp Hamming.cpp

CC_SRC=viennaRNA.c

CPP_OBJS=$(CPP_SRC:.cpp=.o)
CC_OBJS=$(CC_SRC:.c=.o)

$(PROG): $(CPP_OBJS) $(CC_OBJS)
	$(CPP)  $(CPPFLAGS) -o $@ $(CPP_OBJS) $(CC_OBJS) $(VIENNA_LIBRARY) $(BIOPP_LIBRARY)

viennaRNA.o : viennaRNA.c
	$(CC)  $(CCFLAGS) -c -o $@ $< $(VIENNA_INCLUDE)

clean:
	rm -f *.o
