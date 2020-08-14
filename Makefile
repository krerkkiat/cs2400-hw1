.PHONY: clean
CXXFLAGS=`python3.8-config --cflags`
LDFLAGS=`python3.8-config --ldflags --embed`

all: main

main: main.o
	$(CXX) $^ $(LDFLAGS) -o $@

main.o: src/main.cc
	$(CXX) -c $(CXXFLAGS) $^ -o $@

clean:
	-rm -f main main.o