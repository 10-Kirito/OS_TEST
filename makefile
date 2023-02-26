# Test1: Process_schedule
objects_1 = Process_schedule.o Process.o Cpu.o
# macro define :
# PRIORITY
# ROUND
DEFS_1 = -D PRIORITY
DEFS_2 = -D ROUND


Priority_schedule : $(objects_1)
	g++ -o Priority_schedule Process_schedule.cpp Process.cpp Cpu.cpp $(DEFS_1)

Round_schedule : $(objects_1)
	g++ -o Round_schedule Process_schedule.cpp Process.cpp Cpu.cpp $(DEFS_2)

Process_schedule.o: Process.h Cpu.h
Process.o: Process.h
Cpu.o: Cpu.h tools.h 

clean_test1: 
	rm Priority_schedule Round_schedule $(objects_1)

# test2:

object_2 = Banker_main.o Banker.o

Banker: $(object_2)
	g++ -o Banker $(object_2)

Banker_main : Banker.h

clean_test2:
	rm Banker $(object_2)


# test3:

objects_3 = OPT_LRU.o 

OPT_LRU : $(objects_3)
	g++ -o OPT_LRU $(objects_3)

clean_test3:
	rm OPT_LRU $(objects_3)



# test4
objects_4 = Thread_inter.o UFD.o ThreadExec.o 

File_system : $(objects_4)
	g++ -g -o File_system $(objects_4)

Thread_inter.o : ThreadExec.h UFD.h
UFD.o: UFD.h
ThreadExec.o : ThreadExec.h



clean_test4:
	rm File_system $(objects_4)




help:
	@echo 'Typical usage is:'
	@echo '	> make                          # build all programs'
	@echo '	> make Priority_schedule        # build Priority_schedule and use ./Priority_schedule to run'
	@echo '	> make Round_schedule           # build Round_schedule and use ./Round_schedule to run'
	@echo '	> make Banker                   # build Banker_main and use ./Banker to run'
	@echo '	> make OPT_LRU                  # build OPT_LRU and use ./OPT_LRU to run'
	@echo '	> make File_system              # build File_system and use ./File_system to run'


