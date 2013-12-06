CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lcybcore -lpthread -lcybview -lcybnetwork -lcybcollaboration -lrt -lglut -lGLU -lcybglove -lcybhaptics
INCLUDES = -I/usr/include/cybermed/mf

TARGET=ClientGlove
HDRS=
SRCS=ClientGloveCollaboration.cpp cybHandModel.cpp cybHandModel_Remote.cpp  myViewMono.cpp cybUpdate5dt14Model.cpp cybUpdate5dt5Model.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

