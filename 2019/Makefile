EXEC=qualif_lyon

FILES = qualif_lyon slideshow
OBJECTS=$(FILES:=.o)
CXXFLAGS=-O3 -std=c++14 -Wall
OTHER_LDFLAGS = -L/usr/local/opt/llvm/lib -I/usr/local/opt/llvm/include
CXX=g++
all: $(EXEC)

qualif_lyon: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OTHER_LDFLAGS) $(OBJECTS) -o $@

%.o: $(SOURCEDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

mrproper: clean
	$(RM) $(EXEC)

