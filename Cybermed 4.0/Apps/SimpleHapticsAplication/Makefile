CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lcybcore -lcybutil -lcybcollision -lglut -lGLU -lpthread -lcybview -lcybhaptics -lcybdeformation -lrt
INCLUDES = -I/usr/include/cybermed/mf

TARGET=SimpleHaptics
HDRS=
SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

