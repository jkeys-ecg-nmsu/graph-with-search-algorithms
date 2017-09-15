#ifndef HEAP_PRIORITY_QUEUE_H
#define HEAP_PRIORITY_QUEUE_H

#include <algorithm>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>


class Graph;
class Node;

using namespace std;

class HeapPriorityQueue {
private:
	vector<Node> m_heap; 

public:
	HeapPriorityQueue(Graph & g);

	void insert(Graph & g, Node n);
	void change_priority(Graph & g, Node n);
	Node remove_min(Graph & g);
	
	bool empty() { return m_heap.empty(); }
	
};

#endif