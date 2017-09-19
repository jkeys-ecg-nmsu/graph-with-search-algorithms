#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <iterator>
#include <string>

#include <limits>
#include <climits>

using namespace std;

const int M_INFINITY = numeric_limits<int>::max();

// const double M_INFINITY = numeric_limits<double>::infinity();

class Node {
private:
  string m_name;
  int m_id;
  int m_cc;
  
  bool m_visited;
  int m_pre_visit;
  int m_post_visit;
  double m_distance;
  
  double m_latitude;
  double m_longitude;
  
  int m_heap_idx;
  
  int m_parent;
  int m_rank;
  
  int m_next;
  
  string m_edge_roads;
      
public:
  Node();
  Node(const string & name, int id);
  
  Node(const string & name, int id, bool visited, int pre_visit, int post_visit);
  
  void setVisited();
  void resetVisitedFlag();
  
  void setRank(int rank);
  void setCC(int cc); 
  void setPre(int pre);
  void setPost(int post);
  void setDist(double dist);
  void setLatitude(double lat);
  void setLongitude(double longitude);
  void setParent(int parent);
  void setNext(int next);
  void setEdgeRoads(string edgeRoads) { m_edge_roads = edgeRoads; }
  
  void setHeapID(int idx) { m_heap_idx = idx; }
  int heapID() { return m_heap_idx; }
  
  //not sure how to make const correct
  const int parent() const;
  
  const int rank() const;
  int id() const;
  const string & name() const;
  const bool visited() const;
  const int pre() const; 
  const int post() const;  
  const int cc() const;
  const double dist() const;
  const int next() const { return m_next; }
  
  const string edgeRoads() const { return m_edge_roads; }
  
  const double latitude() const;
  const double longitude() const;
  
	friend bool operator < (const Node &n1, const Node &n2) {
		return n1.id() < n2.id();
	}

	friend bool operator > (const Node &n1, const Node &n2) {
		return n1.id() > n2.id();
	} 
	
	friend bool operator== (const Node&n1, const Node &n2) {
		return (n1.id() == n2.id());
	}
};


#endif