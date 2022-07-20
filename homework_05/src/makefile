target:	hw5

boardgame2d:	boardgame2d.h boardgame2d.cpp
			g++ -std=c++11 -c boardgame2d.cpp

pegsolitaire:	pegsolitaire.h pegsolitaire.cpp
			g++ -std=c++11 -c pegsolitaire.cpp

eightpuzzle:	eightpuzzle.h eightpuzzle.cpp
			g++ -std=c++11 -c eightpuzzle.cpp

klotski:		klotski.h klotski.cpp
			g++ -std=c++11 -c klotski.cpp

hw5_main:	boardgame2d.h pegsolitaire.h eightpuzzle.h klotski.h hw5_main.cpp
			g++ -std=c++11 -c hw5_main.cpp

hw5:	hw5_main boardgame2d pegsolitaire eightpuzzle klotski
		g++ -std=c++11 boardgame2d.o pegsolitaire.o eightpuzzle.o klotski.o hw5_main.o -o hw5

clean:
		rm hw5