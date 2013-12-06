CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lGL -lGLU -lglut -lpthread -lcybcore -lcybview -lrt -lcybglove -lcybcollaboration
INCLUDES = -I/usr/include/cybermed/mf

TARGET=HMDVisualization
HDRS=
SRCS=HMDVisualization.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

