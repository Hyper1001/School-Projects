CXXFLAGS += --std=c++17

all:clean main

main: customer.o desktop.o main.o options.o order.o store.o -o main

customer.o: customer.cpp
	$(CXX) $(CXXFLAGS) -c customer.cpp -o customer.o

desktop.o: desktop.cpp
	$(CXX) $(CXXFLAGS) -c desktop.cpp -o desktop.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

options.o: options.cpp
	$(CXX) $(CXXFLAGS) -c options.cpp -o options.o

order.o: order.cpp
	$(CXX) $(CXXFLAGS) -c order.cpp -o order.o

store.o: store.cpp
	$(CXX) $(CXXFLAGS) -c store.cpp -o store.o

clean:
	rm -r -f *.o *.gch main