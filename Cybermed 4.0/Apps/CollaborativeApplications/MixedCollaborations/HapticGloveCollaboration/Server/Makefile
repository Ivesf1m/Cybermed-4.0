CC=g++
CFLAGS+= -DNDEBUG -Dlinuxl -DCYBHAPTICS_H
LIBS = -lglut -lGLU -lpthread -lcybview -lcybhaptics -lcybnetwork -lcybcollaboration -lcybglove -lrt
INCLUDES = -I/usr/include/cybermed/of

TARGET=HapticServer
HDRS=
SRCS=HapticServer.cpp cybHandModel.cpp 
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

