# Make environment
CC=gcc
CFLAGS=-I. -c -g -Wall
LINKARGS=-lm
LIBS=-lm

# Files
SOURCE_FILES=	assign3_main.c \
				a3support.c
OBJECT_FILES=	assign3_main.o \
				a3support.o

# Productions
all : asgn3

asgn3 : $(OBJECT_FILES)
	$(CC) $(LINKARGS) $(OBJECT_FILES) -o $@ $(LIBS)

clean :
	rm -rf $(OBJECT_FILES)
