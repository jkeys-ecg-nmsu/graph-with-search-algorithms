#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "Node.h"
#include <list>

double findEdgeWeight(Node v, list<Edge> uEdges);

void Dijkstra_list(Graph & g, Node & s);

void Dijkstra_heap(Graph & g, Node & s);

void Dijkstra_tmg(Graph & g, Node & s, Node & e);

#endif