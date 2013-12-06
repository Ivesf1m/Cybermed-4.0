CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lcybcore -lpthread -lcybview -lcybnetwork -lcybcollaboration -lrt -lGL -lglut -lGLU -lcybglove 
INCLUDES = -I/usr/include/cybermed/mf -I/usr/include/cybermed

TARGET=ClientGlove
HDRS=
DEBUG=-ggdb
SRCS=ClientGloveCollaboration.cpp cybHandModel.cpp myViewMono.cpp cybUpdate5dt14Model.cpp cybUpdate5dt5Model.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) $(DEBUG) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

