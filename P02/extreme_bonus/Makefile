CXXFLAGS = --std=c++17

all: example test color

color: main.o color.o *.h
	$(CXX) $(CXXFLAGS) main.o color.o -o color
	
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o
color.o: color.cpp *.h
	$(CXX) $(CXXFLAGS) -c color.cpp -o color.o

color.gch: color.h
	$(CXX) $(CXXFLAGS) -c color.h -o color.gch

clean:
	rm -f *.o *.gch ~* a.out  color 
