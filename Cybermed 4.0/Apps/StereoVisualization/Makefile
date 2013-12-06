CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lglut -lGLU -lpthread -lcybutil -lcybcore -lcybview -lrt 
INCLUDES = -I/usr/include/cybermed/mf

TARGET=StereoVisualization
HDRS=
SRCS=StereoVisualization.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

