CC=g++
CFLAGS+= -DNDEBUG -Dlinux -O3
LIBS = -lGLU -lglut -lpthread -lcybutil -lcybcore -lcybview -lcybassess -lrt -lcybhaptics -lcybcollaboration -lcybglove 
INCLUDES = -I/usr/include/cybermed/mf

TARGET=SimpleNB
HDRS=
SRCS=SimpleNB.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

