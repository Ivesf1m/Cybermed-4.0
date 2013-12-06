CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lglut -lpthread -lcybview -lrt -lGL -lGLU -lcybutil -lcybcore -lcybglove -lcybcollaboration
INCLUDES = -I/usr/include/cybermed/mf

TARGET=GloveApp
HDRS=
SRCS=main.cpp cybHandModel.cpp cybUpdate5dt14Model.cpp myViewMono.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -w $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

