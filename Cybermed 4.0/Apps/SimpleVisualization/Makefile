CC=g++
CFLAGS+= -DNDEBUG -Dlinux -g
LIBS = -lglut -lGLEW -lcybutil -lcybcore -lGLU -lpthread -lcybview -lrt
INCLUDES = -I/usr/include/cybermed/mf

TARGET=MonoscopicVisualization
HDRS=
SRCS=MonoscopicVisualization.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

