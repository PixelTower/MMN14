CC = gcc
CFLAGS = -Wall -ansi -pedantic

OBJS = front.o prepro.o firstpass.o secondpass.o

assembler: $(OBJS)
	$(CC) $(CFLAGS) -o assembler $(OBJS)

front.o: front.c front.h prepro.h firstpass.h secondpass.h
	$(CC) $(CFLAGS) -c front.c

prepro.o: prepro.c prepro.h
	$(CC) $(CFLAGS) -c prepro.c

firstpass.o: firstpass.c firstpass.h
	$(CC) $(CFLAGS) -c firstpass.c

secondpass.o: secondpass.c secondpass.h
	$(CC) $(CFLAGS) -c secondpass.c

clean:
	rm -f *.o assembler

# End of makefile
# This Makefile is used to compile the assembler program.