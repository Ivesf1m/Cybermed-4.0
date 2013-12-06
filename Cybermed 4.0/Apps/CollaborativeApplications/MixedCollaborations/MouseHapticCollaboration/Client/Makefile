CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lglut -lGLU -lpthread -lcybcore -lcybutil -lcybview -lcybnetwork -lcybcollaboration -lrt -lcybhaptics
INCLUDES = -I/usr/include/cybermed/of

TARGET=SimpleCollaborationClient
HDRS=
SRCS=SimpleCollaborationClient.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

