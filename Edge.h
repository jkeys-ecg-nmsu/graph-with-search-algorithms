#ifndef EDGE_H
#define EDGE_H

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
	
	friend bool operator < (const Edge &e1, const Edge &e2) {
		return e1.weight() < e2.weight();
	}

	friend bool operator > (const Edge &e1, const Edge &e2) {
		return e1.weight() > e2.weight();
	} 
	
};


#endif