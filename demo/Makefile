CC = g++
CFLAGS = -g -O2 -Wall -std=c++11
demo1SRCS = demo1.cpp
demo1PROG = demo1.exe
demo2SRCS = demo2.cpp
demo2PROG = demo2.exe
demo3SRCS = demo3.cpp
demo3PROG = demo3.exe
UISRCS = ui.cpp
UIPROG = ui.exe
TESTSRCS = test.cpp
TESTPROG = test.exe

ifeq ($(OS),Windows_NT)
    # not adding windows yet
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
    	CFLAGS += -Werror
        OPENCV = `pkg-config opencv --cflags --libs`
    endif
    ifeq ($(UNAME_S),Darwin)
        OPENCV = `pkg-config --cflags --libs /usr/local/Cellar/opencv/4.0.1/lib/pkgconfig/opencv4.pc`
    endif
endif

OPENCVLIBS = $(OPENCV)

LD = -I../FVlibs
MYLIBS = ../FVlibs/FVlib.a

demo1:$(demo1SRCS)
	$(CC) $(CFLAGS) -o $(demo1PROG) $(demo1SRCS) $(OPENCVLIBS) $(LD) $(MYLIBS)

demo2:$(demo2SRCS)
	$(CC) $(CFLAGS) -o $(demo2PROG) $(demo2SRCS) $(OPENCVLIBS) $(LD) $(MYLIBS)

demo3:$(demo3SRCS)
	$(CC) $(CFLAGS) -o $(demo3PROG) $(demo3SRCS) $(OPENCVLIBS) $(LD) $(MYLIBS)


ui:$(UISRCS)
	$(CC) $(CFLAGS) -o $(UIPROG) $(UISRCS) $(OPENCVLIBS)

test: $(TESTSRCS)
	$(CC) $(CFLAGS) -o $(TESTPROG) $(TESTSRCS) $(OPENCVLIBS)

clean:
	rm -f *.o *.exe


