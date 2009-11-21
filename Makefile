CXX           = g++
INCPATH       = -I. `freetype-config --cflags`
CXXFLAGS      = $(INCPATH) -g -pg -pipe -O3 -Wall -W -mtune=native -funroll-loops -ffast-math
LINK          = g++ -g -pg
LFLAGS        = -Wl,-O1
LIBS          = -L/usr/lib -lpthread -lSDL -lGL -lglut -lpng -lpngwriter -lz -lfreetype
SOURCEFIND    = find src -type f -path '*.cpp' ! -path '*.svn*'
SOURCES       = $(shell $(SOURCEFIND))
OBJECTS       = $(SOURCES:%.cpp=%.o)
EXECUTABLE    = LSys2D

all: $(OBJECTS) $(EXECUTABLE)
intel:
	make -f Makefile.intel

allinone:
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(LIBS) $(SOURCES) -o $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(LINK) $(LFLAGS) $(LIBS) $(OBJECTS) -o $@

.o:
	$(CXX) $(CXXFLAGS) $(@:%.o=%.cpp) -o `basename $@`

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

