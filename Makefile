all: main.exe

clean:
	rm -f *.o all
	rm -f *.exe all

main.exe: longnum.o picalculation.o main.o	
	g++ main.o longnum.o picalculation.o -o main.exe

CC := g++

%.o : %.cpp 
	$(CC) -c $< -o $@


