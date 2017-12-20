#Daniel Sohn & Richard Guo
#dsohn3, rguo7
#dsohn3@jhu.edu, rguo7@jhu.edu
#601.220
#10/16/17
#MIDTERM PROJECT


CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

main: project.o ppmIO.o menuUtil.o imageManip.o
	$(CC) -g -o main project.o ppmIO.o menuUtil.o imageManip.o -lm

project.o: project.c menuUtil.h ppmIO.h imageManip.h structHeader.h
	$(CC) $(CFLAGS) -c project.c

ppmIO.o: ppmIO.c ppmIO.h structHeader.h
	$(CC) $(CFLAGS) -c ppmIO.c

menuUtil.o: menuUtil.c menuUtil.h structHeader.h
	$(CC) $(CFLAGS) -c menuUtil.c

imageManip.o: imageManip.c imageManip.h structHeader.h
	$(CC) $(CFLAGS) -c imageManip.c

clean:
	rm -rf *.o main *.gch
