PROGS = makemain
makemain:
	gcc -o makemain makemain.c
clean:
	rm -f makemain
all:	clean $(PROGS)
