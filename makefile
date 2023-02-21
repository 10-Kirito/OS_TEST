objects_1 = Process_schedule.o Process.o Cpu.o

objects_2 = OPT.o LRU.o

# test1:

test1 : $(objects_1)
	g++ -o test1 $(objects_1)

Process_schedule.o: Process.h Cpu.h
Process.o: Process.h
Cpu.o: Cpu.h tools.h

# test2:

OPT_LRU : $(objects_2)
	g++ -o OPT_LRU $(objects_2)



clean:
	rm test1 $(objects_1)
	rm OPT_LRU $(objects_2)
