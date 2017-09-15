#include "Edge.h"

Edge::Edge(int u_id, int  v_id, double edge_weight) {
	m_u_id = u_id;
	m_v_id = v_id;
	m_edge_weight = edge_weight;
}

int Edge::u_id() { return m_u_id; }
int Edge::v_id() { return m_v_id; }
const double Edge::weight() const { return m_edge_weight; }
	