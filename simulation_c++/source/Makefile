IDIR=../include/
ODIR=../obj/
BIN= ../bin/
LIBS=-lm -lSDL2main -lSDL2

CC=g++
CFLAGS=-I$(IDIR) -std=c++11

_DEPS= particle.h
DEPS= $(patsubst %,$(IDIR)%,$(_DEPS))

_OBJ= particle.o  main_program.o
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

