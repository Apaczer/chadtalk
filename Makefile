SOURCES ?= stbresize.cpp
PROG ?= stbresize

CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++
STRIP=$(CROSS_COMPILE)strip

CFLAGS = -ggdb -Ofast
CFLAGS += -flto
EXTRAFLAGS ?= -Wall
#LIBS ?= -lSDL

all:
	$(CXX) $(SOURCES) -o $(PROG) $(CFLAGS) $(EXTRAFLAGS)
	$(STRIP) $(PROG)
clean:
	rm -rf $(PROG)
