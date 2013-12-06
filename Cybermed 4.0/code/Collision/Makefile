#Script configs

verde=[42m
vermelho=[41m
normal=[0m

#Project Configs

MODULE		= cybcollision
OK			= OK

CC			= g++
LD			= ld
DOXGEN		= doxygen

OPT			= -fomit-frame-pointer -funroll-loops -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE $(HAPTIC_OPT)

INCDIR		= ./include
SRCDIR		= ./src
BINDIR		= ./bin
DOCDIR		= ./doc/html
LIBDIR		= ./lib

CYBCOREINCFLAGS = -I ../Core/include
CYBUTILSINCFLAGS = -I../Utils/include 

CYBINCFLAGS	= $(CYBCOREINCFLAGS) $(CYBUTILSINCFLAGS) -I../include -I../include/of -I../Haptics/include

INCFLAGS	= -I/usr/local/include -I$(INCDIR) $(CYBINCFLAGS)
FLAG		=  -fPIC #-Wall -Wno-deprecated
DEBUG		= -ggdb
LIBS		= -lpthread -lglut -lcybutil -lcybcore -Xlinker -zmuldefs
CFLAGS		= $(FLAG) $(INCFLAGS)

SOURCES		=   \
				cybBroadCollision.cpp\
				cybCollision.cpp\
				cybCollisionData.cpp\
				cybNarrowCollision.cpp\
				cybSomeBroad.cpp\
				cybSphereTriangle.cpp\
				cybAABB.cpp\
				cybCollisionManager.cpp\
				cybCollisionObserver.cpp\
				cybCollisionInstance.cpp\
				cybOBB.cpp
		
SRCS		= $(addprefix $(SRCDIR)/,$(SOURCES))
OBJS		= $(SRCS:.cpp=.o)
EXE			= $(LIBDIR)/lib$(MODULE).so.1.0.0
INIT		= $(LIBDIR)

.SUFFIXES: .cpp .o .h .c

all: $(INIT) $(EXE)

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
	@echo ${verde} Installing $(MODULE) module! $(normal)
	cp  $(LIBDIR)/* /usr/lib64/
	/sbin/ldconfig
	#ln -s /usr/lib/lib$(MODULE).so.1.0.0 /usr/lib/lib$(MODULE).so
	cp  include/*.h /usr/include/cybermed/
	@echo ${verde} Ininstalling complete! $(normal)

uninstall:
	@echo ${verde} Uninstalling $(MODULE) module! $(normal)
	rm -f /usr/lib64/lib$(MODULE).so*
	@echo ${verde} Uninstalling complete! $(normal)

clean:
	@echo ${verde} Running clean... $(normal)
	@[ ! -e lib ] || rm -rf lib
	@[ ! -e $(SRCDIR)/cybBroadCollision.o ] || rm $(SRCDIR)/*.o
	@echo ${verde} Clean OK! $(normal)

