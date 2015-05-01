CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c basetypes.c board.c console.c errors.c game.c game-io.c \
	menus.c nine-men-morris.c settings.c sounds.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Nine-Men-Morris.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
