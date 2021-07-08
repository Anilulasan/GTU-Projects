all: main

main: 171044004_main.o source.o
	g++ 171044004_main.o source.o -o main

171044004_main.o: 171044004_main.cpp
		g++ -c 171044004_main.cpp

source.o: source.cpp
	g++ -c source.cpp

clean:
	rm *.o main