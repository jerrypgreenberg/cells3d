CXX=g++
CXXFLAGS=-std=c++11 -I/System/Library/Frameworks/OpenGL.framework/Headers -I/System/Library/Frameworks/GLUT.framework/Versions/A/Headers -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers
LDFLAGS=-framework GLUT -framework OpenGL -lm
#default: Cell.o Ctypes.o CellSimulation.o
OBJECTS=test.o Transform.o
default: $(OBJECTS)
	cc -o test $(OBJECTS) $(LDFLAGS)
