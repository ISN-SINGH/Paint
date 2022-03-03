paint.out : main.o paint.o edit.o fileuse.o input.o template.o
	gcc -g -Wall -Werror main.o paint.o edit.o fileuse.o input.o template.o -o paint.out

main.o : main.c template.h paint.h input.h
	gcc -g -Wall -Werror -c main.c

paint.o : paint.c paint.h edit.c edit.h fileuse.c fileuse.h input.c input.h template.c template.h
	gcc -g -Wall -Werror -c paint.c edit.c fileuse.c input.c template.c

edit.o : edit.c edit.h template.h
	gcc -g -Wall -Werror -c edit.c

fileuse.o : fileuse.c fileuse.h template.h
	gcc -g -Wall -Werror -c fileuse.c

input.o : input.c input.h
	gcc -g -Wall -Werror -c input.c

template.o : template.c template.h
	gcc -g -Wall -Werror -c template.c

clean:
	rm -fr *.o *.out
