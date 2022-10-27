odb: main.o func.o
	gcc -o ../bin/odb ../src/main.c ../src/func.c

main.o:../src/main.c
	gcc -c ../src/main.c

func.o:../src/func.c
	gcc -c ../src/func.c

clean: 
	rm *.o
