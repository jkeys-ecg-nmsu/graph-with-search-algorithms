#include "Debug.h"
#include "Node.h"
#include "Graph.h"
#include "Edge.h"
#include "Dijkstra.h"
#include <stack>
#include <vector>
#include <iterator>


bool testall() {	
	Graph g("in_test_1.txt");	
	g.save("out_test_1.txt");
	
	std::cerr << g << endl << endl;	
	std::cerr << "g1 list: " << endl;	
	Node n1 = g.getNode(0);
	Dijkstra_list(g, n1);
	
	printDist(g);
	
	vector<int> pc1 = { 0, 2, 4, 6, 8 };
	if(!g.sameDistances(pc1)) 
		return false;

	std::cerr << g << endl << endl;	
	std::cerr << "g1 heap: " << endl;	
	n1 = g.getNode(0);
	Dijkstra_heap(g, n1);
	
	printDist(g);
	
	if(!g.sameDistances(pc1)) 
		return false;	
	
	/*******************************************************/
	
 	g.scan("in_test_2.txt");	
	g.save("out_test_2.txt");
	
	std::cerr << g << endl << endl;	
	std::cerr << "g2 list: " << endl;	
	Node n2 = g.getNode(0);
	Dijkstra_list(g, n2);

	printDist(g);	
	
	vector<int> pc2 = { 0, 2, 2, 4, 4, 4, 4, 6, 8, 6 };
	if(!g.sameDistances(pc2)) 
		return false;
	
	std::cerr << g << endl << endl;	
	std::cerr << "g2 heap: " << endl;	
	n2 = g.getNode(0);
	
	Dijkstra_heap(g, n2);
	printDist(g);
	
	if(!g.sameDistances(pc2)) 
		return false;		
	
	/*******************************************************/

 	g.scan("in_test_3.txt");	
	g.save("out_test_3.txt");
	
	std::cerr << g << endl << endl;	
	std::cerr << "g3 list: " << endl;	
	Node n3 = g.getNode(0);
	Dijkstra_list(g, n3);

	printDist(g);	
	
	vector<int> pc3 = { 0, 3, 6, 9, 12, 15 };
	if(!g.sameDistances(pc3)) 
		return false;

	std::cerr << g << endl << endl;	
	std::cerr << "g3 heap: " << endl;	
	n3 = g.getNode(0);
	Dijkstra_heap(g, n3);

	printDist(g);	
	
	if(!g.sameDistances(pc3)) 
		return false;
	
	/*******************************************************/
	
	g.scan("in_test_4.txt");	
	g.save("out_test_4.txt");
	
	std::cerr << g << endl << endl;	
	std::cerr << "g4 list: " << endl;	
	Node n4 = g.getNode(0);
	Dijkstra_list(g, n4);

	printDist(g);	
	
	vector<int> pc4 = { 0, 4, 8, 12, 8, 12, 12, 16, 16 };
	if(!g.sameDistances(pc4)) 
		return false;
	
	std::cerr << g << endl << endl;	
	std::cerr << "g4 heap: " << endl;	
	n4 = g.getNode(0);
	Dijkstra_heap(g, n4);

	printDist(g);	
	
	if(!g.sameDistances(pc4)) 
		return false;
	
	/*******************************************************/
	
	g.scan("in_test_5.txt");	
	g.save("out_test_5.txt");
	
	std::cerr << g << endl << endl;	
	std::cerr << "g5 list: " << endl;	
	Node n5 = g.getNode(0);
	Dijkstra_list(g, n5);

	printDist(g);	
	
	vector<int> pc5 = { 0, 5, 10, 10, 10, 15, 15, 20, 25, 30, 20, 25 };
	if(!g.sameDistances(pc5)) 
		return false;  
	
	std::cerr << g << endl << endl;	
	std::cerr << "g5 heap: " << endl;	
	n5 = g.getNode(0);
	Dijkstra_heap(g, n5);

	printDist(g);		
	
	if(!g.sameDistances(pc5)) 
		return false;  
	
	/*******************************************************/
	
	return true;	
}

void printSpaces(int n) { for(int i = 0; i != n; i++) cout << " ";}

void printReverseGraphSortedNodes(Graph & r) {	
	cerr << "every node in sorted reverse graph (by descending post number)" << endl;
	for(vector<Node>::iterator i = r.begin(); i != r.end(); i++) {
		cerr << i->name() << "\tid: " << i->id() << endl;
	} 	
}

void print_cc(Graph & g, vector<size_t> cc_vec) {
	for(int i = 0; i != cc_vec.size(); i++) {
		Node v = g.getNode(i);
		cerr << v.name() << ".id(): " << v.id() << '\t' << "cc: " << cc_vec.at(i) << endl;
	}
}

void printTimes(Graph & g) {
	for (int i = 0; i != g.num_nodes(); i++) {
		Node e = g.getNode(i);
		cerr << e.name() << ".id() == " << i << ", .pre() == " << g.pre(e) << ", " << e.name() 
			 << ".post() == " << g.post(e) << ".cc() == " << g.cc(e) << endl;
	}
	
}

void printStack(Graph & g, stack<Node> s) {
	cerr << "Top of stack:" << endl;
	while( !s.empty() ) {
		Node v = s.top();
		cerr << "s.top() == " << v.name() << ", .pre() == " << g.pre(v) 
			 << ", .post() == " << g.post(v) << ", .cc() == " << g.cc(v) << endl;
		
		s.pop();
	}
	
	cerr << ": Bottom of stack" << endl;
}

void printDist(Graph & g) {
	for(int i = 0; i != g.num_nodes(); i++) {
		Node v = g.getNode(i);
		cerr << v.name() << ".id(): " << v.id() << "\tdist: " << g.dist(v) << endl;
	}
}