IDIR=../include/
ODIR=../obj/
BIN= ../bin/
LIBS=-I/usr/local/include/eigen3/

CC=g++
CFLAGS=-I$(IDIR) $(LIBS) -std=c++11 -O3 

_DEPS = particle.h particle_system.h
DEPS = $(patsubst %,$(IDIR)%,$(_DEPS))

_OBJ= particle.o particle_system.o program.o
OBJ = $(patsubst %,$(ODIR)%,$(_OBJ))

PROG=program
LIST=$(addprefix $(BIN), $(PROG))

all: $(LIST)

$(ODIR)%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LIST): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
