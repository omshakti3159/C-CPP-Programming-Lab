CFLAGS = -Wall
LIBS = -lm
SRC = 11510415_lab2.c distance.o loadcities.o query.o strfunc.o

all: lab2

lab2 : $(SRC)
	gcc $(CFLAGS) -o lab2 $(SRC) $(LIBS)

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@ $(LIBS)
