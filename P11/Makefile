CXXFLAGS += --std=c++17
all: main

main:main.o cart.o item.o
	$(CXX) $(CXXFLAGS) main.o cart.o item.o -o main
	
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

item.o: item.cpp
	$(CXX) $(CXXFLAGS) -c item.cpp -o item.o


cart.o: cart.cpp
	$(CXX) $(CXXFLAGS) -c cart.cpp -o cart.o

clean:
	rm -rf *.o main *.gch

