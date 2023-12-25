SOURCE	= server.cpp helper_functions_server.cpp data_base.cpp conversion.cpp

ODIR=../obj
_OBJS	= server.o helper_functions_server.o data_base.o conversion.o
OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))

IDIR = ../include
_HEADER	= helper_functions_server.h data_base.h conversion.h
HEADER = $(patsubst %, $(IDIR)/%, $(_HEADER))

OUT	= server
CC	 = g++
CFLAGS	 = -Wall
LFLAGS	 = -l sqlite3


server: $(OBJS)
	$(CC) -o $(OUT) $(SOURCE) $(CFLAGS) $(LFLAGS)

$(ODIR)/%.o: %.cpp $(HEADER)
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJS) $(OUT)
