CXX           = g++
INCPATH       = -I. `pkg-config libxml++-2.6 --cflags`
CXXFLAGS      = $(INCPATH) -pipe -Wall -O3 -ffast-math -mtune=native -funroll-loops
LINK          = g++ -g -pg
LFLAGS        = -Wl,-O1
LIBS          = -L/usr/lib -lpthread -lSDL -lGL -lglut -lGLU `pkg-config libxml++-2.6 --cflags --libs`
SOURCEFIND    = find src -type f -path '*.cpp' ! -path '*.svn*'
SOURCES       = $(shell $(SOURCEFIND))
HEADERFIND    = find src -type f -path '*.h' ! -path '*.svn*'
HEADERS       = $(shell $(HEADERFIND))
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
	rm -f $(OBJECTS) $(EXECUTABLE) src/*.gcda src/*.gcno src/*.gcov

flaw:
	flawfinder -c --html $(SOURCES) $(HEADERS) > flawfinder.htm
	its4 $(SOURCES) $(HEADERS) > its4.txt

tar:
	tar -caf $(EXECUTABLE).tar.gz $(SOURCES) $(HEADERS) Makefile Makefile.intel doc/* files/* LICENSE README

