# silent
MAKEFLAGS += -s

all:pid_fork pid_sleep pid_pthread puts
exec=pid_fork pid_sleep pid_pthread puts

pid_fork:pid_fork.c
	gcc pid_fork.c -o pid_fork
pid_sleep:pid_sleep.c
	gcc pid_sleep.c -o pid_sleep
pid_pthread:pid_pthread.c
	gcc pid_pthread.c -o pid_pthread 
puts:puts.c
	gcc puts.c -o puts
clean:
	rm -f  $(exec)
