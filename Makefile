UNIXCC=cc
WINCC=x86_64-w64-mingw32-gcc
CFLAGS=-Wall -Wextra -Wshadow -pedantic -O2 --std=c99
UNIXEXEC=hangman
WINEXEC=hangman.exe
SRC=hangman.c

all: $(UNIXEXEC) $(WINEXEC)

$(UNIXEXEC): $(SRC)
	$(UNIXCC) $(CFLAGS) -o $@ $^ -DUNIX

$(WINEXEC): $(SRC)
	$(WINCC) $(CFLAGS) -o $@ $^ -DWIN32

clean:
	rm -f $(UNIXCC) $(WINEXEC)

.PHONY: all clean
