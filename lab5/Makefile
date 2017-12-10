CFLAGS = -Wall
LIBS =
SRC = testUTF8string_lab5.cpp utf8.o UTF8string.o

all: lab5

lab5 : $(SRC)
	g++ $(CFLAGS) -o test $(SRC) $(LIBS)

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@ $(LIBS)

%.o : %.cpp
	g++ $(CFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm *.o test -f
