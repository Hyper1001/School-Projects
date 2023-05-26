CXXFLAGS = --std=c++17

all: store

debug: CXXFLAGS += -g
debug: store

store: main.o *.h
	$(CXX) $(CXXFLAGS)  store.o -o store

store.o: store.cpp *.h
	$(CXX) $(CXXFLAGS) -c store.cpp -o store.o
product.o: product.cpp *.h
	$(CXX) $(CXXFLAGS) -c product.cpp -o product.o
taxed.o: taxed.cpp *.h
	$(CXX) $(CXXFLAGS) -c taxed.cpp -o taxed.o
taxfree.o: taxfree.cpp *.h
	$(CXX) $(CXXFLAGS) -c taxfree.cpp -o taxfree.o

store: store.o taxed.o product.o taxfree.o
	$(CXX) $(CXXFLAGS) store.o taxed.o product.o taxfree.o -o store
	./store
store.o: store.cpp *.h	
	$(CXX) $(CXXFLAGS) -c store.cpp


clean:
	rm -f *.o *.gch ~* a.out store