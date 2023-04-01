all: alloc-1gb

alloc-1gb: alloc-1gb.c mem_util.c mem_util.h
	gcc -Wall alloc-1gb.c mem_util.c -o bin/alloc-1gb
