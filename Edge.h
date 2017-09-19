#ifndef EDGE_H
#define EDGE_H

#include "Graph.h"
#include "Node.h"

class Edge {
	// int m_id; //should be same as the 
private:
	int m_u_id, m_v_id;
	double m_edge_weight;
	
public:
	Edge(int u_id, int v_id, double edge_weight);
	
	int u_id();
	int v_id();
	const double weight() const;
	
	bool equals(Edge e) {
		return(u_id() == e.u_id() && v_id() == e.v_id() && weight() == e.weight()) ;
	}
	
	Edge reverse() {
		return Edge(m_v_id, m_u_id, m_edge_weight);
	}
	
	void print(Graph & g) {
		Node u = g.getNode(m_u_id);
		Node v = g.getNode(m_v_id);
		cerr << u.name() << "->" << v.name() << ", weight: " << weight() << "\n";
	}
	
	friend bool operator < (const Edge &e1, const Edge &e2) {
		return e1.weight() < e2.weight();
	}

	friend bool operator > (const Edge &e1, const Edge &e2) {
		return e1.weight() > e2.weight();
	} 
	
};


#endif