#!/bin/bash

#Build objects
cc -c cpu.c
cc -c memory.c
cc -c main.c

cc -o 16bitc main.o memory.o cpu.o

#Cleanup
rm *.o