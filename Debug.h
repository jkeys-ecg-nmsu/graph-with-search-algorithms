#ifndef DEBUG_H
#define DEBUG_H

#include "Graph.h"
#include <vector>
#include <stack>

void printSpaces(int n);

void printReverseGraphSortedNodes(Graph & r);

void print_cc(Graph & g, vector<size_t> cc_vec);

void printTimes(Graph & g);

void printStack(Graph & g, stack<Node> s);

void printDist(Graph & g);

bool testall();

#endif