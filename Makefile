all: brute.out backtrack.out

brute.out: brute.c
	gcc brute.c -o brute.out

backtrack.out: backtrack.c
	gcc backtrack.c -o backtrack.out
  
clean:
	rm brute.out backtrack.out
