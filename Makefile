
# Variables to control Makefile operation

CC = g++
CFLAGS = -Wall -g

minimum-window-substring: minimum-window-substring.o
	$(CC) $(CFLAGS) -o minimum-window-substring minimum-window-substring.o

minimum-window-substring.o: minimum-window-substring.cpp
	$(CC) $(CFLAGS) -c minimum-window-substring.cpp

clean:
	rm -rf minimum-window-substring minimum-window-substring.o
