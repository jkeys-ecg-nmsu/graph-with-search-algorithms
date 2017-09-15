#include "BFS.h"
#include "Graph.h"
#include "Node.h"
#include <queue>
#include <set>
#include <iterator>

void BFS(Graph & g, Node & s) {
	queue<Node> q;
	
	g.resetAllDist();
	
	g.setDist(s, 0); //s is the root 
	q.push(s);
	
	while ( !q.empty() ) {
		Node u = q.front();
		q.pop();
		
		set<Node> uAdjNodes = g.getAdjNodes(u);
		
		//for every adjacent node v: (u)--->(v)
		for(set<Node>::iterator v = uAdjNodes.begin(); v != uAdjNodes.end(); v++) {
			if(g.dist(*v) == M_INFINITY) {		//if v has not been visited in BFS
				g.setDist(*v, g.dist(u) + 1);	//v.dist == u.dist + 1
				q.push(*v);						//push the adjacent node to back of the queue
			}
		} //end adjNodes loop
	} //end while
} //end BFS