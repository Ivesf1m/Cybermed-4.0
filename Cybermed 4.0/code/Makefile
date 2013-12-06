MODULE		= teste
OK			= OK

CC			= g++
DOXGEN		= doxygen

OPT			= -fomit-frame-pointer -funroll-loops -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

INCDIR		= ./include
SRCDIR		= ./src
BINDIR		= ./bin
DOCDIR		= ./doc/html

INCFLAGS	= -I/usr/local/include -I$(INCDIR) 
FLAG		=  #-Wall -Wno-deprecated -lglut -lpthread
DEBUG		= -ggdb
LIBS		= -lpthread -lglut -lHL -lHLU -lHDU -lHD #aqui se soloca as libs que se deseja incluir como -lpthread
CFLAGS		= $(FLAG) $(INCFLAGS)
		

SRCS		= $(addprefix $(SRCDIR)/,$(SOURCES))
OBJS		= $(SRCS:.cpp=.o)
EXE			= $(BINDIR)/$(MODULE)
INIT		= $(BINDIR)

.SUFFIXES: .cpp .o .h .c

all:
	#rm -rf /usr/include/cybermed
	#mkdir /usr/include/cybermed

	#rm -rf /usr/src/cybermed
	#mkdir /usr/src/cybermed

	make -C Utils
	#make install -C Utils
	make -C Core
	#make install -C Core
	make -C View
	#make install -C View
	make -C Collision
	#make install -C Collision
	make -C Deformation
	#make install -C Deformation
	make -C Assess
	#make install -C Assess
	make -C Haptics
	#make install -C Haptics
	make -C Network
	#make install -C Network
	make -C Trackers
	#make install -C Trackers
	
uninstall:
	make uninstall -C Utils
	make uninstall -C Core
	make uninstall -C Deformation
	make uninstall -C View
	make uninstall -C Collision
	make uninstall -C Assess
	make uninstall -C Haptics
	make uninstall -C Network
	make uninstall -C Trackers
    rm -rf /usr/include/cybermed
	rm -rf /usr/src/cybermed

clean:
	make clean -C Utils
	make clean -C Core
	make clean -C View
	make clean -C Collision
	make clean -C Deformation
	make clean -C Assess
	make clean -C Haptics
	make clean -C Network	
	make clean -C Trackers	
