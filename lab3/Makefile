CFLAGS = -Wall
LIBS = -lm
SRC = main.c readfile.c

all: lab3

lab3 : $(SRC)
	gcc $(CFLAGS) -o lab3 $(SRC) $(LIBS)

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@ $(LIBS)
