sim: main.o tools.o
	g++ -o sim main.o tools.o -lm
	rm *.o

main.o: main.cpp tools.h
	g++ -c main.cpp

tools.o: tools.cpp tools.h
	g++ -c tools.cpp

clean:
	rm -f sim *.o
