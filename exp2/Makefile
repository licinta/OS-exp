pref = -w
all: pid_make pid_fork pid_hello pid_ls pid_loop
pid_make:pid_make.c
	gcc pid_make.c -o pid_make $(pref)

pid_fork:pid_fork.c
	gcc pid_fork.c -o pid_fork $(pref)

pid_hello: pid_hello.c
	gcc pid_hello.c -o pid_hello $(pref)

pid_hello: pid_ls.c
	gcc pid_ls.c -o pid_ls $(pref)

pid_loop: pid_loop.c
	gcc pid_loop.c -o pid_loop $(pref)
