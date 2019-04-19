# Make environment
CC=gcc
CFLAGS=-I. -c -g -Wall
LINKARGS=-lm
LIBS=-lm

# Files
SOURCE_FILES=	client.c \
				client_support.c
OBJECT_FILES=	client.o \
				client_support.o

# Productions
all : client

asgn2 : $(OBJECT_FILES)
	$(CC) $(LINKARGS) $(OBJECT_FILES) -o $@ $(LIBS)

clean : 
	rm -f cmsc257-s16-assign2 $(OBJECT_FILES)
