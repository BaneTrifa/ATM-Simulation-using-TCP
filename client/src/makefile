SOURCE	= client.cpp helper_functions_client.cpp

ODIR=../obj
_OBJS	= client.o helper_functions_client.o
OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))

IDIR = ../include
_HEADER	= helper_functions_client.h
HEADER = $(patsubst %, $(IDIR)/%, $(_HEADER))

OUT	= client
CC	 = g++
FLAGS	 = -Wall

client: $(OBJS)
	$(CC) -o $(OUT) $(SOURCE) $(CFLAGS) $(LFLAGS)

$(ODIR)/%.o: %.cpp $(HEADER)
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJS) $(OUT)
