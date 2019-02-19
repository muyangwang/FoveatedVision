CC = g++
CFLAGS = -c -Wall
SRCS = receptiveField.cpp tools.cpp
OBJS = receptiveField.o tools.o
LIBS = FVlib.a

OPENCV = `pkg-config opencv --cflags --libs`
OPENCVLIBS = $(OPENCV)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(OPENCVLIBS)

$(LIBS): $(OBJS)
	ar rcs $(LIBS) $(OBJS)

libs: $(LIBS)

clean:
	rm *.o *.a
