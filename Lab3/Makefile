
CC = g++
CFLAGS = -Wall -Werror

all: main SJF RR

main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp

SJF: SJF_inital.c
	gcc -Wall -Werror -o SJF SJF_inital.c

RR: RR_inital.c
	gcc -Wall -Werror -o RR RR_inital.c

clean:
	rm -f main SJF RR
