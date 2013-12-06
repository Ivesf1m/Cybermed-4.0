CC=g++
CFLAGS+= -DNDEBUG -Dlinux -g -ggdb 
LIBS = -lglut -lGLU -lpthread -lcybcore -lcybview -lcybnetwork -lcybcollaboration -lrt -lcybglove
INCLUDES = -I/usr/include/cybermed/mf

TARGET=SimpleCollaborationServer
HDRS=
SRCS=SimpleCollaborationServer.cpp cybHandModel.cpp cybUpdate5dt14Model.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

