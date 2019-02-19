CC = g++
CFLAGS = -g -Wall
demo1SRCS = demo1.cpp
demo1PROG = demo1.exe
UISRCS = ui.cpp
UIPROG = ui.exe

OPENCV = `pkg-config opencv --cflags --libs`
OPENCVLIBS = $(OPENCV)

LD = -I../FVnew
MYLIBS = ../FVnew/FVlib.a

demo1:$(demo1SRCS)
	$(CC) $(CFLAGS) -o $(demo1PROG) $(demo1SRCS) $(OPENCVLIBS) $(MYLIBS)

ui:$(UISRCS)
	$(CC) $(CFLAGS) -o $(UIPROG) $(UISRCS) $(OPENCVLIBS)

clean:
	rm *.o *.exe


