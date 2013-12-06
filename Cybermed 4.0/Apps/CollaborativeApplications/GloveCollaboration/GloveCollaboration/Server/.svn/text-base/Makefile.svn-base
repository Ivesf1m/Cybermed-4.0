CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lcybcore -lpthread -lcybview -lcybnetwork -lcybcollaboration -lrt -lglut -lGLU -lcybglove -lcybhaptics
INCLUDES = -I/usr/include/cybermed/mf

TARGET=ServerGlove
HDRS=
SRCS=cybHandModel.cpp cybHandModel_Remote.cpp cybUpdate5dt14Model.cpp cybUpdate5dt5Model.cpp ServerGloveCollaboration.cpp myViewMono.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

