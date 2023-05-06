all:Mem-Pages.out

exec=$(wildcard *.out)

source=$(wildcard *.c)

clean:
	rm $(exec)

Mem-Pages.out:Mem-Pages.c
	gcc Mem-Pages.c -o Mem-Pages.out -g





