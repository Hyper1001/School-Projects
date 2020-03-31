CXXFLAGS += --std=c++17
GTKFLAGS += `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`


all: clean main

customer.o: customer.cpp
	$(CXX) $(CXXFLAGS) -c customer.cpp -o customer.o

desktop.o: desktop.cpp
	$(CXX) $(CXXFLAGS) -c desktop.cpp -o desktop.o

entrydialog.o: entrydialog.cpp
	$(CXX) $(CXXFLAGS) -c entrydialog.cpp $(GTKFLAGS) -o entrydialog.o

main: mainwin.o main.o entrydialog.o customer.o store.o options.o desktop.o order.o
	$(CXX) $(CXXFLAGS) mainwin.o main.o entrydialog.o customer.o store.o options.o desktop.o order.o $(GTKFLAGS) -o main
	./main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS) -o main.o

mainwin.o: mainwin.cpp
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS) -o mainwin.o

options.o: options.cpp
	$(CXX) $(CXXFLAGS) -c options.cpp -o options.o

order.o: order.cpp
	$(CXX) $(CXXFLAGS) -c order.cpp -o order.o

store.o: store.cpp
	$(CXX) $(CXXFLAGS) -c store.cpp -o store.o

clean:
	rm -r -f *.o *.gch main
