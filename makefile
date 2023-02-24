objects_1 = Process_schedule.o Process.o Cpu.o

objects_2 = OPT_LRU.o 
objects_3 = LRU.o OPT.o

objects_4 = File_system.o UFD.o MFD.o
# test1:

test1 : $(objects_1)
	g++ -o test1 $(objects_1)

Process_schedule.o: Process.h Cpu.h
Process.o: Process.h
Cpu.o: Cpu.h tools.h

# test2:

OPT_LRU : $(objects_2)
	g++ -o OPT_LRU $(objects_2)

# test4

File_system : $(objects_4)
	g++ -g -o File_system $(objects_4)


help:
	@echo 'Typical usage is:'
	@echo '		> make 							# build all programs'
	@echo '		> make test1 				# build test1 and use ./test1 to run'
	@echo ' 	> make OPT_LRU    	# build test3 and use ./OPT_LRU to run'

clean:
	rm test1 $(objects_1)
	rm OPT_LRU $(objects_2) $(objects_3)
clean4:
	rm File_system $(objects_4)
