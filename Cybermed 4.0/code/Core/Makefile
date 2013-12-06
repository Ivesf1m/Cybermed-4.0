#Script configs
verde=[42m
vermelho=[41m
normal=[0m

MODULE		= cybcore
OK			= OK

CC			= g++
LD			= ld
DOXGEN		= doxygen

OPT			= -fomit-frame-pointer -funroll-loops -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE $(HAPTIC_OPT) $(TRACKOPT_OPT) $(TRACKMAG_OPT) $(COLLAB_OPT) $(GLOVE_OPT)

INCDIR		= ./include
SRCDIR		= ./src
BINDIR		= ./bin
DOCDIR		= ./doc/html
LIBDIR		= ./lib

CYBINCFLAGS	= -I../Utils/include -I../Utils/include/mf -I../Haptics/include -I../Trackers/include -I../Collaboration/include -I../Gloves/include

INCFLAGS	= -I/usr/local/include -I$(INCDIR) $(CYBINCFLAGS)
FLAG		=  -fPIC -g -O3#-Wall -Wno-deprecated
DEBUG		= -ggdb
LIBS		= -lpthread -lGLEW -lglut -lGL -lGLU -lcybutil 
CFLAGS		= $(FLAG) $(INCFLAGS)

SOURCES		= \
			cybDevice.cpp\
			cybInterator.cpp\
			cybMouse.cpp\
			cybMouseInterator.cpp\
			cybMouseInteraction.cpp\
			cybPointOperator.cpp\
			cybParameters.cpp\
			cybModel.cpp\
			cybMultiModel.cpp\
			cybUpdateModel.cpp\
			
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
	$(CC)  $(CFLAGS) $(INCFLAGS)  -c $< -o $@ $(OPT)

install:
	cp  $(LIBDIR)/* /usr/lib/
	/sbin/ldconfig
	#ln -s /usr/lib/lib$(MODULE).so.1.0.0 /usr/lib/lib$(MODULE).so
	cp  include/*.h /usr/include/cybermed/

uninstall:
	rm -f /usr/lib64/lib$(MODULE).so*

clean:
	@echo ${verde} Running clean... $(normal)
	@[ ! -e lib ] || rm -rf lib
	@[ ! -e $(SRCDIR)/cybInterator.o ] || rm $(SRCDIR)/*.o
	@echo ${verde} Clean OK! $(normal)

