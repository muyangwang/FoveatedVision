
CC = g++
CFLAGS = -g -c -O2 -Wall -Werror -std=c++11
SRCS = receptiveField.cpp tools.cpp
OBJS = receptiveField.o tools.o
LIBS = FVlib.a


ifeq ($(OS),Windows_NT)
    # not adding windows yet
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        OPENCV = `pkg-config opencv --cflags --libs`
    endif
    ifeq ($(UNAME_S),Darwin)
        OPENCV = `pkg-config opencv --cflags --libs`
    endif
endif

OPENCVLIBS = $(OPENCV)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(OPENCVLIBS)

$(LIBS): $(OBJS)
	ar rcs $(LIBS) $(OBJS)

libs: $(LIBS)

clean:
	rm *.o *.a
