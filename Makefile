CXX=c++
LDR=c++
CXXFLAGS=-std=c++11 -I/System/Library/Frameworks/GLUT.framework/Versions/A/Headers
LDFLAGS=-framework GLUT -framework OpenGL -lm
#OBJECTS=test.o Transform.o
OBJECTS=Cell.o Ctypes.o CellSimulation.o Transform.o test.o
default: $(OBJECTS)
	$(LDR) -v -o test $(OBJECTS) $(LDFLAGS)
clean:
	rm *.o
