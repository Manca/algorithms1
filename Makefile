all:
	$(CXX) -pthread -std=c++11 -O2 main.cpp -o algorithms1

test:
	 ./algorithms1 || exit 1

clean:
	rm algorithms1
