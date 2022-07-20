target:	hw4

dayofyear:	dayofyear.h dayofyear.cpp
			g++ -std=c++11 -c dayofyear.cpp

hw4_main:	dayofyear.h hw4_main.cpp
			g++ -std=c++11 -c hw4_main.cpp


hw4:	hw4_main dayofyear
		g++ -std=c++11 dayofyear.o hw4_main.cpp -o hw4

clean:
		rm hw4