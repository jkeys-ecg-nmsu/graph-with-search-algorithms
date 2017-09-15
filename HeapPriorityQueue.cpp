#include "HeapPriorityQueue.h"
#include "Graph.h"
#include "Node.h"

#include <algorithm>
#include <vector>

using namespace std;

bool heap_comp(Node a, Node b) {
	return a.dist() > b.dist();
}

HeapPriorityQueue::HeapPriorityQueue(Graph & g) {
	m_heap.reserve(MAX_NODES);
	m_heap.push_back(g.getNode(0));
	
	make_heap(m_heap.begin(), m_heap.end(), heap_comp);	
}

void HeapPriorityQueue::insert(Graph & g, Node n) {
	m_heap.push_back(n);
	
	push_heap(m_heap.begin(), m_heap.end(), heap_comp);
}

Node HeapPriorityQueue::remove_min(Graph & g) {
	pop_heap(m_heap.begin(), m_heap.end(), heap_comp);
	
	m_heap.pop_back();	
	return m_heap.front();
}