CC=g++
CFLAGS+= -DNDEBUG -Dlinux -O3
LIBS = -lGLU -lglut -lpthread -lcybcore -lcybview -lcybassess -lrt #-lcybhaptics -lcybcollaboration -lcybglove
INCLUDES = -I/usr/include/cybermed/mf

TARGET=SimpleFGNBread.exe
HDRS=
SRCS=SimpleFGNBread.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

