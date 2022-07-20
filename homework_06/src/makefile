target:	hw6

hw6_main:	baseiterator.h gtuiterator.h gtuiteratorconst.h iterable.h gtuvector.h gtuset.h gtuarray.h exceptionsgtu.h hw6_main.cpp
			g++ -std=c++11 -c hw6_main.cpp

hw6:	hw6_main
		g++ -std=c++11 hw6_main.o -o hw6

clean:
		rm hw6