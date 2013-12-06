MODULE		= cybassess
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

CYBINCFLAGS	= -I../Utils/include -I../Utils/include/of -I../Core/include/ -I../Haptics/include

INCFLAGS	= -I/usr/local/include -I$(INCDIR) $(CYBINCFLAGS)
FLAG		=  -fPIC -O3#-Wall -Wno-deprecated
DEBUG		= -ggdb
LIBS		= -lpthread -lglut -lcybutil -lcybcore
CFLAGS		= $(FLAG) $(INCFLAGS)

SOURCES		= \
			  cybAssess.cpp\
			  cybAssessIO.cpp\
			  cybAssessDataProvider.cpp\
			  cybBayesianNetwork.cpp\
			  cybNetworkIO.cpp\
			  cybMLM.cpp\
			  cybMLMIO.cpp\
			  cybAssessLinker.cpp\
			  cybFuzzyGaussianNaiveBayes.cpp\
			  cybFuzzyGaussianNaiveBayesIO.cpp\
			  cybFuzzyNaiveBayes.cpp\
			  cybFuzzyNaiveBayesIO.cpp\
			  cybGaussianNaiveBayes.cpp\
			  cybGaussianNaiveBayesIO.cpp\
			  cybNaiveBayes.cpp\
			  cybNaiveBayesIO.cpp\
			
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
	cp  $(LIBDIR)/* /usr/lib64/
	/sbin/ldconfig
	#ln -s /usr/lib/lib$(MODULE).so.1.0.0 /usr/lib/lib$(MODULE).so
	cp  include/*.h /usr/include/cybermed/

uninstall:
	rm -f /usr/lib64/lib$(MODULE).so*

clean:
	rm -rf lib
	rm $(SRCDIR)/*.o

