CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lGLU -lglut -lcybutil -lcybcore -lpthread -lcybview -lrt -lcybhaptics -lcybcollaboration -lcybglove
INCLUDES = -I/usr/include/cybermed/mf

TARGET=SimpleTexturing
HDRS=
SRCS=SimpleTexturing.cpp \
     TextureView.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

