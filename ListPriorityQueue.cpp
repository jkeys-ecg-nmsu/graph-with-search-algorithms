#include "ListPriorityQueue.h"
#include "Graph.h"
#include "Node.h"

#include <iterator>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

ListPriorityQueue::ListPriorityQueue(Graph & g) {
	for(size_t i = 0; i != g.num_nodes(); i++) {
		this->m_queue.push_front(g.getNode(i));
	}
}

Node ListPriorityQueue::remove_min(Graph & g) {
	std::list<Node>::iterator min_node = this->m_queue.begin();
	for(std::list<Node>::iterator curr = this->m_queue.begin(); curr != this->m_queue.end(); curr++) {
		if(g.dist(*curr) < g.dist(*min_node)) {
			min_node = curr;
		}
	}
	
	Node result = g.getNode(min_node->id());
	this->m_queue.erase(min_node);
	return result;
}

void ListPriorityQueue::insert(Graph & g, Node n) {
	this->m_queue.push_front(n);	
}


void ListPriorityQueue::change_priority(Graph & g, Node n) {
	std::list<Node>::iterator pos = find(this->m_queue.begin(), this->m_queue.end(), n);
	this->m_queue.erase(pos);
	this->insert(g, n);
}



/* void ListPriorityQueue::insert(Graph & g, Node n) {
	if(g.dist(n) < g.dist(m_queue.front())) {
		m_queue.push_front(n);
		return;
	}
	
	std::list<Node>::iterator pos = m_queue.begin();
	
	while(pos != m_queue.end()) {
		if (g.dist(n) > g.dist(*pos)) {
			pos++; //start pointer at min value; advance until it 
		} else {
			break;
		}
	}
	
	if(pos != m_queue.end()) {
		m_queue.insert(pos, n);
	} else {
		cerr << "list_insert: something bad happened";
	}
	
	return;
} */