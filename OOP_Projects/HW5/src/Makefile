all: main
all: driver

main: 171044004_main.o AbstractHex.o HexVector.o HexArray1D.o HexAdapter.o
	g++ 171044004_main.o AbstractHex.o HexVector.o HexArray1D.o HexAdapter.o -o main -std=gnu++11

driver: 171044004_driver.o AbstractHex.o HexVector.o HexArray1D.o HexAdapter.o
	g++ 171044004_driver.o AbstractHex.o HexVector.o HexArray1D.o HexAdapter.o -o driver -std=gnu++11

171044004_main.o: 171044004_main.cpp
		g++ -c 171044004_main.cpp -std=gnu++11

171044004_driver.o: 171044004_driver.cpp
		g++ -c 171044004_driver.cpp -std=gnu++11

AbstractHex.o: AbstractHex.cpp
	g++ -c AbstractHex.cpp -std=gnu++11

HexVector.o: HexVector.cpp
	g++ -c HexVector.cpp -std=gnu++11

HexArray1D.o: HexArray1D.cpp
	g++ -c HexArray1D.cpp -std=gnu++11

HexAdapter.o: HexAdapter.cpp
	g++ -c HexAdapter.cpp -std=gnu++11

clean:
	rm *.o main
