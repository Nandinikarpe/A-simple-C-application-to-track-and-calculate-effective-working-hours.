CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: work_hours_tracker

work_hours_tracker: work_hours_tracker.c
	$(CC) $(CFLAGS) -o work_hours_tracker work_hours_tracker.c

clean:
	rm -f work_hours_tracker work_sessions.dat 