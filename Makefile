# To run, enter
# make all

all: program2

program2: main.o _fcfs_single.o _fcfs_percore.o _rr_percore.o _rr_load.o
	gcc -o program2 main.o _fcfs_single.o _fcfs_percore.o _rr_percore.o _rr_load.o

main.o: main.c declarations.h
	gcc -c main.c

_fcfs_single.o: _fcfs_single.c declarations.h
	gcc -c _fcfs_single.c

_fcfs_percore.o: _fcfs_percore.c declarations.h
	gcc -c _fcfs_percore.c

_rr_percore.o: _rr_percore.c declarations.h
	gcc -c _rr_percore.c

_rr_load.o: _rr_load.c declarations.h
	gcc -c _rr_load.c