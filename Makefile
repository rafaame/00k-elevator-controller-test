##### Variables

SRCDIR = src
OBJDIR = obj
INCDIR = -Isrc -Iinclude
LIBDIR =
CPPFLAGS = -g -std=c++11 -Wall $(INCDIR)
LFLAGS =
CC = g++

##### Files

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
SRCFILES = $(patsubst $(SRCDIR)/%,%,$(SOURCES))
DEPENDENCIES = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.cpp=.o))
OBJTEMP = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES))
OBJECTS = $(patsubst %.cpp,%.o,$(OBJTEMP))
TARGET = bin/main

##### Build rules

run: all
	cd bin && ./main

all: $(DEPENDENCIES)
	$(CC) $(CPPFLAGS) $(LIBDIR) $(OBJECTS) $(LFLAGS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $(OBJDIR)/$*.o $(SRCDIR)/$*.cpp

depend:
	gcc -E -MM $(CPPFLAGS) $(SOURCES) | sed 's|[a-zA-Z0-9_-]*\.o|$(OBJDIR)/&|' > deps.d

clean:
	@rm -rf $(TARGET) $(TARGET).exe $(OBJDIR)/*.o *.bak *~ *%

memtest:
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./bin/main

include deps.d
