16bitc : main.o memory.o cpu.o \
				cc -o 16bitc main.o memory.o cpu.o

main.o : main.c memory.h
        cc -c main.c

cpu.o : cpu.c cpu.h
        cc -c cpu.c

memory.o : memory.c memory.h
        cc -c memory.c

clean :
        rm 16bitc main.o cpu.o memory.o