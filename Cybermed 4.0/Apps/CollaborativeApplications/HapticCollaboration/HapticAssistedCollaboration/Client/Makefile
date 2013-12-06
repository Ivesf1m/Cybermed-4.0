CC=g++
CFLAGS+= -DNDEBUG -Dlinux -DCYBHAPTICS_H
LIBS = -lglut -lGLU -lpthread -lcybcore -lcybview -lcybhaptics -lcybnetwork -lcybcollaboration -lrt -lcybglove
INCLUDES = -I/usr/include/cybermed/of

TARGET=HapticClient
HDRS=
SRCS=HapticClient.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

