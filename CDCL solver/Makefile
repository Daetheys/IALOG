minimal : sat_solver

all: sat_solver tests

#Solver
sat_solver: utils.o logics.o cdcl.o main.o parser.o printer.o
	gcc -o sat_solver utils.o logics.o cdcl.o main.o parser.o printer.o
utils.o:
	gcc -o utils.o -c utils.c -Wall -O
logics.o: utils.h
	gcc -o logics.o -c logics.c -Wall -O
cdcl.o: cdcl.c logics.h
	gcc -o cdcl.o -c cdcl.c -Wall -O
main.o: main.c parser.h cdcl.h
	gcc -o main.o -c main.c -Wall -O
parser.o: parser.c logics.h
	gcc -o parser.o -c parser.c -Wall -O
printer.o: printer.c parser.h
	gcc -o printer.o -c printer.c -Wall -O

#Tests
test : test_utils test_logics test_cdcl

test_utils: test_utils.c utils.c utils.h
	gcc -o tests/test_utils test_utils.c utils.c -Wno-int-conversion -Wno-int-to-pointer-cast -Wno-format

test_logics: test_logics.c logics.c utils.c utils.h logics.h
	gcc -o tests/test_logics test_logics.c utils.c logics.c -Wno-int-conversion -Wno-int-to-pointer-cast -Wno-format -Wno-pointer-to-int-cast -Wno-format

test_cdcl: test_cdcl.c cdcl.c logics.c utils.c utils.h logics.h cdcl.h
	gcc -o tests/test_cdcl test_cdcl.c utils.c logics.c cdcl.c -Wno-int-conversion -Wno-int-to-pointer-cast -Wno-format -Wno-pointer-to-int-cast -Wno-format

#Usefull
clean:
	rm -f *.o core
mrproper: clean
	rm -f sat_solver
