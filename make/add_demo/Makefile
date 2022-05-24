CC = g++
CFLAGS = -c
SOURCES = main.cpp add.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:*.h
	$(CC) $(SOURCES) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)