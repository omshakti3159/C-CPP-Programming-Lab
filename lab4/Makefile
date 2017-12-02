CFLAGS = -Wall
LIBS =
SRC = testUTF8string.cpp utf8.o UTF8string.o

all: lab4

lab4 : $(SRC)
	g++ $(CFLAGS) -o test $(SRC) $(LIBS)

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@ $(LIBS)

%.o : %.cpp
	g++ $(CFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm *.o test -f
