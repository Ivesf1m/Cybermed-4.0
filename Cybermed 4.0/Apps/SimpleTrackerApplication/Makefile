CC=g++
CFLAGS+= -DNDEBUG -Dlinux -DCYBTRACKER_H
LIBS = -lglut -lpthread -lcybview -lcybdeformation -lrt -lglut -lcybtrackers #-lfob-1.0
INCLUDES = -I/usr/include/cybermed/of

TARGET=SimpleTrackerApplication
HDRS=
SRCS=SimpleTrackerApplication.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

