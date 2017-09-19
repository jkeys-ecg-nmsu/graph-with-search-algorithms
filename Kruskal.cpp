#include "Graph.h"
#include "Kruskal.h"

#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <list>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;


bool edge_heap_comp(Edge a, Edge b) {
	return a.weight() < b.weight();
}

void make_edge_heap(vector<Edge> & E) {
	make_heap(E.begin(), E.end(), edge_heap_comp);
}


void insert_edge(vector<Edge> & E, Edge e) {
	E.push_back(e);	
	push_heap(E.begin(), E.end(), edge_heap_comp);
}

Edge remove_min_edge(vector<Edge> & E) {
	pop_heap(E.begin(), E.end(), edge_heap_comp);
	
	E.pop_back();	
	return E.front();
}


void make_set_cc(Graph & g) {
	for(int i = 0; i != g.num_nodes(); i++) {
		Node n = g.getNode(i);
		g.setCC(n, i);
	}
}

vector<Edge> get_all_edges(Graph & g) {
	vector<Edge> E;
	E.reserve(g.num_nodes());
	
	for(int i = 0; i != g.num_nodes(); i++) {
		list<Edge> edge_list = g.getEdges(g.getNode(i));
		for(list<Edge>::iterator e = edge_list.begin(); e != edge_list.end(); e++) {
			E.push_back(*e);
		}
	}
	
	return E;
}

Edge cheapest_edge(vector<Edge> & E) {
	pop_heap(E.begin(), E.end(), edge_heap_comp);
	
	E.pop_back();	
	return E.front();
}

bool same_set_cc(Graph & g, Node u_in, Node v_in) {
	Node u = g.getNode(u_in.id());
	Node v = g.getNode(v_in.id());
	
	return(g.cc(u) == g.cc(v));
}

void union_set_cc(Graph & g, Node u_in, Node v_in) {
	int new_cc = g.cc(u_in);
	int orig_cc = g.cc(v_in);
	for(int i = 0; i != g.num_nodes(); i++) {
		Node n = g.getNode(i);
		if(g.cc(n) == orig_cc) {
			g.setCC(n, new_cc);
		}
	}
}

const vector<Edge> & MST(Graph & g) {
	// g = Kruskal_MST_cclabels(g);
	return g.get_MST(); 
}

void make_set(Graph & g) {
	for(int i = 0; i != g.num_nodes(); i++) {
		Node n = g.getNode(i);
		g.setParent(n, i);
		g.setRank(n, 0);
	}	
}

int find(Graph & g, Node u) {
	if(g.parent(u) != u.id())
		g.setParent(u, find(g, g.getNode(g.parent(u))) );
	
	return g.parent(u);
}

void MST_union(Graph & g, Node & a, Node & b) {
	int a_root = find(g, a), b_root = find(g, b);
	
	if(a_root == b_root) return;
	
	if(g.rank(a) < g.rank(b)) {
		g.setParent(a, b_root);
	} else if (g.rank(a) > g.rank(b)) {
		g.setParent(b, a_root);
	} else {
		g.setParent(b, a_root);
		g.setRank(a, g.rank(a) + 1);
	}
}


Graph Kruskal_MST_cclabels ( Graph & g) {	
	Graph r(g.num_nodes() + 1);
	r.copyNodes(g);
	r.copyEdges(g);
	r.reset();
		
	make_set_cc(g);
	
	vector<Edge> E = get_all_edges(g);
	
	// make_edge_heap(E);
	
	sort(E.begin(), E.end(), edge_heap_comp);
	
	// while(!E.empty()) {
	for(int i = 0; i != E.size(); i++) {
		// Edge e = cheapest_edge(E); //get cheapest edge and pop
		Edge e = E.at(i);
		Node u = g.getNode(e.u_id());
		Node v = g.getNode(e.v_id());
		
		if(!same_set_cc(g, u, v)) {
			// cerr << "in cc, sets are disjoint, edge: ";
			// e.print(r);
			
			r.pushEdge(e);			
			union_set_cc(g, u, v);
		}
		
		
	}
	
	return r;
}


Graph Kruskal_MST_djsets ( Graph & g) {	
	Graph r(g.num_nodes() + 1);
	r.copyNodes(g);
	r.copyEdges(g);
		
	make_set(g);
	
	vector<Edge> E = get_all_edges(g);
	
	// make_edge_heap(E);
	
	sort(E.begin(), E.end(), edge_heap_comp);
	
	// while(!E.empty()) {
	for(int i = 0; i != E.size(); i++) {
		// Edge e = cheapest_edge(E); //get cheapest edge and pop
		Edge e = E.at(i);
		Node u = g.getNode(e.u_id());
		Node v = g.getNode(e.v_id());
		
		if(find(g, u) != find(g,v)) {
			// cerr << "in djsets, sets are disjoint, edge: ";
			// e.print(r);			
			
			r.pushEdge(e);
			MST_union(g, u, v);
		}
	}
	
	return r; //MST is contained in m_edges_MST
}
