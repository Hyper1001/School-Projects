CXXFLAGS = --std=c++17

all: test coin

coin: test.o coin.o *.h
	$(CXX) $(CXXFLAGS) main.o coin.o -o coin
	
test.o: test.cpp *.h
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o
coin.o: coin.cpp *.h
	$(CXX) $(CXXFLAGS) -c coin.cpp -o coin.o

coin.gch: coin.h
	$(CXX) $(CXXFLAGS) -c coin.h -o coin.gch

clean:
	rm -f *.o *.gch ~* a.out  coin 
