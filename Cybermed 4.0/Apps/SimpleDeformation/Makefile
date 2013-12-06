CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lglut -lGLU -lpthread -lcybcore  -lcybview -lcybcollision  -lcybdeformation -lrt -lcybglove -lcybcollaboration -lcybhaptics
INCLUDES = -I/usr/include/cybermed/mf

TARGET=SimpleDeformation
HDRS=
SRCS=SimpleDeformation.cpp
OBJS=$(SRCS:.cpp=.o)


.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

