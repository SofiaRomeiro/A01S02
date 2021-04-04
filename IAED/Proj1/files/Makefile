NAME= proj
Object= io.o usecases.o
CC= gcc
CFLAGS =-ansi -pedantic -Werror -Wall -Wextra

all: $(Object)
	$(CC) $(CFLAGS) $^ -o $(NAME) main.c $(Object)

io.o: io.c io.h define.h
	$(CC) -c io.c

usecases.o: usecases.c usecases.h define.h
	$(CC) -c usecases.c

clean:
	@echo Cleaning...
	(rm -f *.o;)
	(rm -f $(NAME);)