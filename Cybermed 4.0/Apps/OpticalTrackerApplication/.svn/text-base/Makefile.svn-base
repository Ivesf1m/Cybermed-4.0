CC=g++
CFLAGS+= -DNDEBUG -Dlinux -Wall
LIBS = -lcv -lcvaux -lhighgui -lglut -lcybutil -lcybcore -lcybview -lcybtrackers -lblob
INCLUDES = -I/usr/include/cybermed/of

TARGET=Stereo
HDRS=
SRCS=	\
		InteractionHandle.cpp\
		OpenGLTeste.cpp

OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

