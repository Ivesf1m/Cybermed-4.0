CC=g++
CFLAGS+= -DNDEBUG -Dlinux -O
LIBS = -lGLU -lglut -lpthread  -lcybutil -lcybcore -lcybview -lcybcollision -lrt 
INCLUDES = -I/usr/include/cybermed/of

TARGET=BroadCollisionCheck
HDRS=
SRCS=AABBCollisionCheck.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

