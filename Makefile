CXX=g++
LDR=g++
CXXFLAGS=-std=c++11 -I/System/Library/Frameworks/GLUT.framework/Versions/A/Headers
LDFLAGS=-framework GLUT -framework OpenGL -lm
#default: Cell.o Ctypes.o CellSimulation.o
OBJECTS=test.o Transform.o
default: $(OBJECTS)
	$(LDR) -o test $(OBJECTS) $(LDFLAGS)
