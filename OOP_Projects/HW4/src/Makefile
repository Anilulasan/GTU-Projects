all: main

main: 171044004_main.o source.o
	g++ 171044004_main.o source.o -o main -std=gnu++11

171044004_main.o: 171044004_main.cpp
		g++ -c 171044004_main.cpp -std=gnu++11

source.o: source.cpp
	g++ -c source.cpp -std=gnu++11

clean:
	rm *.o main
