CC = g++
CFLAGS = -g -Wall
SRCS = receptiveField.cpp
PROG = HelloWorld

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
