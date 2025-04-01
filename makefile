CC = gcc
CFLAGS = -ansi -Wall -pedantic -Icommon -IFront -IBackend -IMiddle -IPrepro
EXEC = assembler

SRC = \
    Front/front.c \
    Prepro/prepro.c \
    Middle/firstpass.c \
    Middle/secondpass.c \
    Backend/backend.c \
    common/handle_text.c \
    common/util.c \
    common/Errors.c \
    common/lexer.c \
    common/code_conversion.c \
    common/table.c

OBJS = $(SRC:.c=.o)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

clean_outputs:
	rm -f *.ob *.ent *.ext *.am *.t01
