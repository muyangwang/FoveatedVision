CC = gcc
LD = gcc

CFLAGS = -g -c -pedantic-errors -Wall -Werror -fno-elide-constructors
LFLAGS = -pedantic-errors -Wall -Werror

OBJS = pyramids.o
PROG = fovearedVision.exe


default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

clean:
	rm -f *.o

real_clean:
	rm -f *.o
	rm -f *exe
