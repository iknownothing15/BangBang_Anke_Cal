CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -O2 -DLOCAL

all: BangBang_cal

BangBang_cal: BangBang_cal.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f BangBang_cal