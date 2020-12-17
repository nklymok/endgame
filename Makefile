#directories
IDIR = inc
ODIR = obj
SDIR = src
LDIR = lib
#compiler settings
CC = clang
CFLAGS= -I $(IDIR)
#set -std=c11 for general purposes, and -std=gnu99 for ubuntu 20
CCFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I $(IDIR)
#dependencies
EXECUTABLE = endgame
#libs
LIBS =	 -lncurses
LIBS_AWS = -lncursesw
#headers
_DEPS = main.h character.h controls.h menu.h platforms.h about_us.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#objects
# file with main and environment.o MUST BE included
_OBJ = main.o character.o controls.o environment.o menu.o platforms.o about_us.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: $(EXECUTABLE)

#make objects
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
		mkdir -p obj
		$(CC) -c -o $@ $< $(CCFLAGS)
#make excecutable
$(EXECUTABLE): $(OBJ)
		$(CC) -o $@ $^ $(CCLAGS) $(LIBS)

.PHONY: clean uninstall reinstall
#delete all files
uninstall: clean
		rm -f $(LIB_NAME)
		rm -f $(EXECUTABLE)
		rm -rf $(LDIR)
#remove all temporary files
clean:
		rm -rf $(ODIR)
		rm -f *.a
#rebuild project
reinstall: uninstall all
