CFLAGS = -Wall
LIBS =
SRC = main.c readfile.o scripts.o

all: lab3

lab3 : $(SRC)
	gcc $(CFLAGS) -o lab3 $(SRC) $(LIBS)

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm *.o lab3 -f
