#include "Dijkstra.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "ListPriorityQueue.h"
#include "HeapPriorityQueue.h"
#include <list>
#include <set>
#include <queue>
#include <iterator>

double findEdgeWeight(Node v, list<Edge> uEdges) { //find the destination node v containing edge from u
	for(list<Edge>::iterator itr = uEdges.begin(); itr != uEdges.end(); itr++) {
		Edge e = *itr;
		if(e.v_id() == v.id()) 
			return e.weight();
	}
	
	cerr << "findEdgeWeight: should never reach here!" << endl;
	return -1;
}

void Dijkstra_list(Graph & g, Node & s) {
	ListPriorityQueue q(g);
	
	g.resetAllDist();	
	g.setDist(s, 0); //s is the root 

	q.insert(g, s);
	
	while ( !q.empty() ) {
		Node u = q.remove_min(g);
		
		set<Node> uAdjNodes = g.getAdjNodes(u);
		list<Edge> uEdges = g.getEdges(u);
		
		// for every adjacent node v: (u)--->(v)
		for(set<Node>::iterator v = uAdjNodes.begin(); v != uAdjNodes.end(); v++) {
			int edgeWeight = findEdgeWeight(*v, uEdges);

			if(g.dist(*v) > g.dist(u) + edgeWeight || g.dist(*v) == M_INFINITY) {		//if v has not been visited
				g.setDist(*v, g.dist(u) + edgeWeight);	//v.dist == u.dist + 1
				q.change_priority(g, *v);						//push the adjacent node to back of the queue
			}
		} //end adjNodes loop
	} //end while	
}

void Dijkstra_heap(Graph & g, Node & s) {
	HeapPriorityQueue q(g);
	
	g.resetAllDist();	
	g.setDist(s, 0); //s is the root 
	
	q.insert(g, s);
	
	while ( !q.empty() ) {
		Node u = q.remove_min(g);
		
		//instead of using a decrease-key operation on the heap, 
		//we will simply insert redundant nodes and skip visited nodes;
		//this means more nodes will be inserted, but since heap is already logarithmic,
		//the increase in runtime will not be significant		
		if (g.visited(u)) continue; //skip already visited nodes
		
		g.setVisited(u);
		
		set<Node> uAdjNodes = g.getAdjNodes(u);
		list<Edge> uEdges = g.getEdges(u);
		
		// for every adjacent node v: (u)--->(v)
		for(set<Node>::iterator v = uAdjNodes.begin(); v != uAdjNodes.end(); v++) {
			int edgeWeight = findEdgeWeight(*v, uEdges);

			if(g.dist(*v) > g.dist(u) + edgeWeight || g.dist(*v) == M_INFINITY) {
				g.setDist(*v, g.dist(u) + edgeWeight);	
				q.insert(g, *v);						
			}
		} //end adjNodes loop
	} //end while		
}


void Dijkstra_tmg(Graph & g, Node & s, Node & e) {
	HeapPriorityQueue q(g);
	list<int> path;
	
	g.resetAllDist();	
	g.setDist(s, 0); //s is the root 
	
	q.insert(g, s);
	
	while ( !q.empty() ) {
		Node u = q.remove_min(g);
		
		if (g.visited(u)) continue; //skip previously visited nodes		
		if (g.visited(e)) break;	//don't bother continuing once we've hit destination
		
		g.setVisited(u);
		
		set<Node> uAdjNodes = g.getAdjNodes(u);
		list<Edge> uEdges = g.getEdges(u);
		
		// for every adjacent node v: (u)--->(v)
		for(set<Node>::iterator v = uAdjNodes.begin(); v != uAdjNodes.end(); v++) {
			double edgeWeight = findEdgeWeight(*v, uEdges);

			if(g.dist(*v) > g.dist(u) + edgeWeight || g.dist(*v) == M_INFINITY) {
				g.setDist(*v, g.dist(u) + edgeWeight);								
				g.setParent(*v, u.id());
				q.insert(g, *v);						
			}
		} //end adjNodes loop
	} //end while		
		
	/**** dijkstra has been run on source waypoint, check if destination visited ****/
	
	if(!g.visited(e)) {
		cout << "No path from start waypoint to destination waypoint." << endl; 
		return; //print error and return 
	}
	
	/**** path has been found ****/
		
	cout << "Path found!\nStart waypoint id: " << s.id() << " name:" << s.name() << endl;
	cout << "End waypoint id:   " << e.id() << " name:" << e.name() << endl;
	
	int rover_prev;
	Node rover = g.getNode(e.id());
	
	
	while( rover.parent() != -1) {
		rover_prev = g.parent(rover);	
		
		path.push_front(rover.id());	
		
		if(rover_prev == -1 || rover_prev == rover.id()) 
			break;
		
		rover = g.getNode(rover_prev);	
	}
		 
	// cin.ignore();		
	cout << "Origin: " << endl;		
	for(list<int>::iterator i = path.begin(); i != path.end(); i++) {
		Node n = g.getNode(*i);
		if(n.name() == e.name()) cout << "Destination: " << endl;	
		
		cout << n.edgeRoads() << endl;
		cout << n.name() << " " << n.latitude() << " " << n.longitude() << endl;
	}
	
	cout << "Total distance: " << g.dist(e) << endl;
}