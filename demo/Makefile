CC = g++
CFLAGS = -g -O2 -Wall -Werror -std=c++11
demo1SRCS = demo1.cpp
demo1PROG = demo1.exe
demo2SRCS = demo2.cpp
demo2PROG = demo2.exe
UISRCS = ui.cpp
UIPROG = ui.exe
TESTSRCS = test.cpp
TESTPROG = test.exe

OPENCV = `pkg-config opencv --cflags --libs`
OPENCVLIBS = $(OPENCV)

LD = -I../FVnew
MYLIBS = ../FVnew/FVlib.a

demo1:$(demo1SRCS)
	$(CC) $(CFLAGS) -o $(demo1PROG) $(demo1SRCS) $(OPENCVLIBS) $(MYLIBS)

demo2:$(demo2SRCS)
	$(CC) $(CFLAGS) -o $(demo2PROG) $(demo2SRCS) $(OPENCVLIBS) $(MYLIBS)

ui:$(UISRCS)
	$(CC) $(CFLAGS) -o $(UIPROG) $(UISRCS) $(OPENCVLIBS)

test: $(TESTSRCS)
	$(CC) $(CFLAGS) -o $(TESTPROG) $(TESTSRCS) $(OPENCVLIBS)

clean:
	rm *.o *.exe


