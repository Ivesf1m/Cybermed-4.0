#Script configs
verde=[42m
vermelho=[41m
normal=[0m

MODULE		= cybcollaboration
OK			= OK

CC			= g++
LD			= ld
DOXGEN		= doxygen

OPT			= -fomit-frame-pointer -funroll-loops -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

INCDIR		= ./include
SRCDIR		= ./src
BINDIR		= ./bin
DOCDIR		= ./doc/html
LIBDIR		= ./lib

CYBCOREINCFLAGS = -I../Core/include
CYBHAPTICSINCFLAGS = -I../Haptics/include
CYBGLOVESINCFLAGS = -I../Gloves/include
CYBUTILSINCFLAGS = -I../Utils/include
CYBNETWORKINCFLAGS = -I../Network/include

CYBINCFLAGS	= $(CYBCOREINCFLAGS) $(CYBUTILSINCFLAGS) $(CYBNETWORKINCFLAGS) $(CYBHAPTICSINCFLAGS) $(CYBGLOVESINCFLAGS) -I../include -I../include/of -I../include/Core

INCFLAGS	= -I/usr/local/include -I$(INCDIR) $(CYBINCFLAGS)
FLAG		= -fPIC -O3#-Wall -Wno-deprecated
DEBUG		= -ggdb
LIBS		= -lpthread -lcybutil -lcybnetwork 
CFLAGS		= $(FLAG) $(INCFLAGS)

SOURCES		= \
			cybCollaborationIntegrant.cpp\
			cybRemoteInterator.cpp\
			cybRemoteHapticInterator.cpp\
			cybCollaborationProperties.cpp\
			cybCollaboration.cpp\
			cybDefaultCollaboration.cpp\
			$(HAPTIC_ASSISTED_FILE)\
			$(HAPTIC_FILE)\
			cybNodeFactory.cpp\
			cybCollaborationPerformance.cpp\
			$(GLOVE_FILE)\
			cybRemoteGloveInterator.cpp\
			
			
			
SRCS		= $(addprefix $(SRCDIR)/,$(SOURCES))
OBJS		= $(SRCS:.cpp=.o)
EXE			= $(LIBDIR)/lib$(MODULE).so.1.0.0
INIT		= $(LIBDIR)

.SUFFIXES: .cpp .o .h .c

all: $(INIT) $(EXE)

#collab: $(INIT)

$(INIT):
	@echo -n Criando diretorio lib...
	@mkdir $(LIBDIR)
	@echo -e " $(OK)"
#Comandos para compilação final
$(EXE): $(OBJS)
	$(CC) -shared -o $@ -Wl,-soname,lib$(MODULE).so $(SRCDIR)/*.o $(LIBS)
	@echo -e "    $(OK)"
	
	
%.o: %.cpp
	$(CC)  $(CFLAGS) $(DEBUG) $(INCFLAGS)  -c $< -o $@ $(OPT)

install:
	cp  $(LIBDIR)/* /usr/lib64/
	/sbin/ldconfig
	#ln -sf /usr/lib/lib$(MODULE).so.1.0.0 /usr/lib/lib$(MODULE).so
	cp  include/*.h /usr/include/cybermed/

uninstall:
	rm -f /usr/lib64/lib$(MODULE).so*

clean:
	@echo ${verde} Running clean... $(normal)
	@[ ! -e lib ] || rm -rf lib
	[ ! -e $(SRCDIR)/cybCollaboration.o ] || rm $(SRCDIR)/*.o
	@rm -f $(SRCDIR)/*.o
	@echo ${verde} Clean OK! $(normal)

