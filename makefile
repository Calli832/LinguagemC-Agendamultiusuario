all: 
	gcc -c usuario.c
	gcc -c agenda.c
	gcc -c main.c
	gcc -o executavel main.o usuario.o agenda.o
	-rm main.o
	-rm usuario.o
	-rm agenda.o
	./executavel

create_file:
	touch usuario.dat
	touch agenda.dat

run:
	./executavel

clear:
	-rm usuario.o
	-rm  agenda.o
	-rm  *.dat