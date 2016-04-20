CFLAGS=-O3 -g
# list .c and .cu source files here
SRCFILES=matgen.cpp

ifeq ($(ALLINTS),1)
CFLAGS += -DALLINTS
endif

all:	matgen

matgen: $(SRCFILES) 
	g++ $(CFLAGS) -o matgen $^ 

clean: 
	rm -f *.o matgen

