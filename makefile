CC = gcc
CFLAGS = -ansi -Wall -pedantic
OBJS = front.o prepro.o firstpass.o secondpass.o backend.o \
       data_strct.o handle_text.o util.o Errors.o lexer.o \
       code_conversion.o table.o assembler.o

EXEC = assembler

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Compile each .c file into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f *.o $(EXEC)

# Clean all generated output files
clean_outputs:
	rm -f *.am *.ob *.ent *.ext *.t01
  
 