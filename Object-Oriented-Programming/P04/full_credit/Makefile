CXXFLAGS = --std=c++17

all: test coin

coin: test.o coin.o *.h
	$(CXX) $(CXXFLAGS) -DLOGGER main.o coin.o -o coin
	
test.o: test.cpp *.h
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o
coin.o: logger.h coin.cpp *.h
	$(CXX) $(CXXFLAGS) -DLOGGER -c coin.cpp -o coin.o

coin.gch: coin.h
	$(CXX) $(CXXFLAGS) -DLOGGER -c coin.h -o coin.gch

clean:
	rm -f *.o *.gch ~* a.out  coin 
