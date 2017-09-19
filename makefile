all: graph-search

graph-search: clean
	g++ -std=c++11 main.cpp Graph.cpp Node.cpp Edge.cpp ListPriorityQueue.cpp HeapPriorityQueue.cpp Debug.cpp BFS.cpp Dijkstra.cpp Kruskal.cpp -o graph-search
	
clean:
	rm *.o -f
	rm *.exe -f
	rm *.out -f
	rm in_test_small* -f
	rm in_test_big.txt -f
	rm in_test_very_big.txt -f

debug: clean
	g++ -std=c++11 -g main.cpp Graph.cpp Node.cpp Edge.cpp ListPriorityQueue.cpp HeapPriorityQueue.cpp  Debug.cpp BFS.cpp Dijkstra.cpp Kruskal.cpp -o graph-search
	