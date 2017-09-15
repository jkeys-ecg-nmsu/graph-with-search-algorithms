#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <iterator>

#include <limits>
#include <climits>


// [[Rcpp::plugins("cpp11")]]

using namespace std;

const int MAX_NODES = 1000000; //100,000 parent nodes at maxmimum

class Node;
class Edge;

double calculateDistance(Node & s, Node & e);

class Graph {
private:
  vector <Node> m_nodes;
  vector < set<Node> > m_adjList;
  vector < list<Edge> > m_edgeList;
  
  int current_id;  
  int current_cc;
  int m_clock;
  
  int m_max_nodes;
  
public:
  Graph(const string & file);
  
  Graph();
  
  vector<Node> nodes() { return m_nodes; }
  
  void preAllocate();
  
  void initEmpty(int num_nodes);
  
  void copyNodes(Graph & g);
    
  Graph reverse();
  
  bool sameDistances(vector<int> V);
  
  void addEdge(const Node & a, const Node & b);
  void addEdgeObj(const Node & a, const Edge & b);
  void addNode(const Node & a);
  
  void setVisited(const Node & a);  
  void setPre(const Node & a, int pre); 
  void setPost(const Node & a, int post);
  void setDist(const Node & a, double dist);
  void setCC(const Node & a, int cc);
  void setParent(const Node & a,int parent);
  void setNext(const Node & a,int next);
  void setEdgeRoads(const Node & a, string roads);
    
  const string edgeRoads(const Node & a) const;
  const bool visited(const Node & a) const; 
  const double dist(const Node & a) const;  
  const int pre(const Node & a) const; 
  const int post(const Node & a) const; 
  const int cc(const Node & a) const;  
  const int next(const Node & a) const;
  const int currentCC() const;
  const size_t num_nodes() const;
  const int clock() const;
  
  const string name(int u_id) const;
  
  int parent(const Node & a);
  
  void incrementClock();
  void incrementCurrentCC();
  
  void resetClock();
  void resetAllDist();  
  void resetAllVisited();
  
  void reset(); //resetClock, reset pre`s, reset posts
  
  void clearNodes();
  
  void explore(Node v, int indent = 0); //when initially called, v is the root
 
  void printNames(); 
  
  const Node & getNode (size_t i) const;
  set <Node> & getAdjNodes(const Node & a);
  const set <Node> & getAdjNodes(const Node & a) const;
  
  list <Edge> & getEdges(const Node & a);
  const list <Edge> & getEdges(const Node & a) const;
  
  void scan(const string & file);  
  
  void scan_tmg(const string & file);  
  
  void save(const string & file) const;  
  void saveUndirected(const string & file) const;  
  void saveReverse(const string & file) const;
  
  vector<Node>::iterator begin(); 
  vector<Node>::iterator end();
  
	friend std::ostream& operator<<(std::ostream & out, const Graph & g);
};



#endif
