CFLAGS = -Wall
LIBS = 
SRC = main.c readfile.c scripts.c

all: lab3

lab3 : $(SRC)
	gcc $(CFLAGS) -o lab3 $(SRC) $(LIBS)

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@ $(LIBS)
