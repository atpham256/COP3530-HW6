all:
	${MAKE}  hw6prob4 hw6prob5
hw6prob4: hw6prob4.o
	g++ -g -Wall -o hw6prob4 hw6prob4.o
hw6prob4.o: hw6prob4.cpp
	g++ -g -Wall -c hw6prob4.cpp
hw6prob5: hw6prob5.o
	g++ -g -Wall -o hw6prob5 hw6prob5.o
hw6prob5.o: hw6prob5.cpp
	g++ -c -Wall -c hw6prob5.cpp
clean:
	rm *.o hw6prob4 hw6prob5