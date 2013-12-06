#Script configs

verde=[42m
vermelho=[41m
normal=[0m

MODULE		= cybutil
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

INCFLAGS	= -I/usr/local/include -I$(INCDIR) -I$(INCDIR)/mf 
FLAG		=  -fPIC -g#-Wall -Wno-deprecated
DEBUG		= -ggdb
LIBS		= -lpthread -lglut -lGLEW
CFLAGS		= $(FLAG) $(INCFLAGS)

SOURCES		= \
			cybThread.cpp\
			cybMatrixOperator.cpp\
			cybMenuNode.cpp\
			cybMenu.cpp\
			cybBoxHolder.cpp\
			cybBoxDrawer.cpp\
			cybAABBDrawer.cpp\
			cybOBBDrawer.cpp\
			cybLineMatrix.cpp\
			cybFrame.cpp\
			cybProjection.cpp\
			cybOrthographicProjection.cpp\
			cybPerspectiveProjection.cpp\
			cybMatrixStack.cpp\
			cybShader.cpp\
			cybShaderManager.cpp\
			cybBasicBatch.cpp\
			cybTriangleBatch.cpp

			
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
	#$(CC) $(CFLAGS) -o $@  $(SRCDIR)/*.o  $(LIBS)
	$(CC) -shared -o $@ -Wl,-soname,lib$(MODULE).so $(SRCDIR)/*.o $(LIBS)
	@echo -e "    $(OK)"
	
	
%.o: %.cpp
	$(CC)  $(CFLAGS) $(INCFLAGS)  -c $< -o $@ $(OPT)

install:
	cp  $(LIBDIR)/* /usr/lib/
	/sbin/ldconfig
	#ln -s /usr/lib/lib$(MODULE).so.1.0.0 /usr/lib/lib$(MODULE).so
	cp  include/*.h /usr/include/cybermed/
	cp -r include/mf /usr/include/cybermed/

uninstall:
	rm -f /usr/lib64/lib$(MODULE).so*

clean:
	@echo ${verde} Running clean... $(normal)
	@[ ! -e lib ] || rm -rf lib
	@[ ! -e $(SRCDIR)/cybThread.o ] || rm $(SRCDIR)/*.o
	@echo ${verde} Clean OK! $(normal)

