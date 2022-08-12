CC=cc
CFLAGS=-Wall -Wextra -Wshadow -pedantic -O2 -ansi
UNIXEXEC=hangman
WINEXEC=hangman.exe
SRC=hangman.c

all: $(UNIXEXEC) $(WINEXEC)

$(UNIXEXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -DUNIX

$(WINEXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -DWIN32
