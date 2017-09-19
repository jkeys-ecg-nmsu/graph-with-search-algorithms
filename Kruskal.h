#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <list>
#include <set>
#include <vector>
#include <iterator>

Graph Kruskal_MST_cclabels ( Graph & G);

Graph Kruskal_MST_djsets ( Graph & G);

const vector<Edge> get_MST(Graph & g);

void union_set_cc(Graph & g, Node u_in, Node v_in);

bool same_set_cc(Graph & g, Node u_in, Node v_in);

Edge cheapest_edge(vector<Edge> & v);

vector<Edge> get_all_edges(Graph & g);

void make_set_cc(Graph & g);

#endif