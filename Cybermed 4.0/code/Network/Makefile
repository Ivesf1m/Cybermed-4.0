#Script configs
verde=[42m
vermelho=[41m
normal=[0m

MODULE		= cybnetwork
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

CYBINCFLAGS	= -I../Utils/include

INCFLAGS	= -I/usr/local/include -I$(INCDIR) $(CYBINCFLAGS)
FLAG		=  -fPIC -O3#-Wall -Wno-deprecated
DEBUG		= -ggdb
LIBS		= -lpthread -lcybutil -lcybcore
CFLAGS		= $(FLAG) $(INCFLAGS)

SOURCES		= \
			cybCommunicationException.cpp\
			cybDatagramSock.cpp\
			cybDatagramSockException.cpp\
			cybNodeAddress.cpp\
			cybReceiverThread.cpp\
			cybSenderThread.cpp\
			cybSock.cpp\
			cybStreamSock.cpp\
			cybStreamSockException.cpp\
			cybTCPClient.cpp\
			cybTCPConcurrentServer.cpp\
			cybTCPException.cpp\
			cybTCPIteractiveServer.cpp\
			cybTCPServer.cpp\
			cybTCPServerThread.cpp\
			cybUDPClient.cpp\
			cybUDPConcurrentServer.cpp\
			cybUDPIteractiveServer.cpp\
			cybUDPServer.cpp\
			cybUDPServerThread.cpp\
			cybClientMulticast.cpp\
			cybServerMulticast.cpp\
			cybMulticastPeer.cpp\
			cybMulticastException.cpp\
			
			
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
	#ln -sf /usr/lib/lib$(MODULE).so.1.0.0 /usr/lib/lib$(MODULE).so
	cp  include/*.h /usr/include/cybermed/

uninstall:
	rm -f /usr/lib64/lib$(MODULE).so*

clean:
	@echo ${verde} Running clean... $(normal)
	@[ ! -e lib ] || rm -rf lib
	#[ ! -e $(SRCDIR)/cybInterator.o ] || rm $(SRCDIR)/*.o
	@rm -f $(SRCDIR)/*.o
	@echo ${verde} Clean OK! $(normal)

