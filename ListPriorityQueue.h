#ifndef LIST_PRIORITY_QUEUE_H
#define LIST_PRIORITY_QUEUE_H

#include <list>

class Graph;
class Node;

using namespace std;

class ListPriorityQueue {
private:
	list<Node> m_queue; 

public:
	ListPriorityQueue(Graph & g);

	void insert(Graph & g, Node n);
	void change_priority(Graph & g, Node n);
	Node remove_min(Graph & g);
	
	bool empty() { return m_queue.empty(); }
	
};

#endif