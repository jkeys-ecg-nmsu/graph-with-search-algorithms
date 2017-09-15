all: lab8

lab8: clean
	g++ -std=c++11 lab8EC.cpp Graph.cpp Node.cpp Edge.cpp ListPriorityQueue.cpp HeapPriorityQueue.cpp Debug.cpp BFS.cpp Dijkstra.cpp -o lab8EC
	
clean:
	rm *.o -f
	rm *.exe -f
	rm *.out -f

debug: clean
	g++ -std=c++11 -g lab8EC.cpp Graph.cpp Node.cpp Edge.cpp ListPriorityQueue.cpp HeapPriorityQueue.cpp  Debug.cpp BFS.cpp Dijkstra.cpp -o lab8EC
	