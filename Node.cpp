#include "Node.h"

#include "Graph.h"
#include "Edge.h"

#include <string>

using namespace std;

Node::Node(const string & name, int id) 
  {m_name = name, m_id = id; m_visited = false; m_pre_visit = -1; m_post_visit = -1; m_cc = 0; m_parent = -1; }
  
Node::Node(const string & name, int id, bool visited, int pre_visit, int post_visit) 
  {m_name = name, m_id = id; m_visited = visited; m_pre_visit = pre_visit; m_post_visit = post_visit; m_cc = 0; }
  
  
void Node::setVisited() { m_visited = true; }  
void Node::resetVisitedFlag() { m_visited = false; }

void Node::setRank(int rank) { m_rank = rank; }
void Node::setCC(int cc) { m_cc = cc; }  
void Node::setPre(int pre) { m_pre_visit = pre; }  
void Node::setPost(int post) { m_post_visit = post; }  
void Node::setDist(double dist) { m_distance = dist; }  
void Node::setParent(int parent) { m_parent = parent; }    
void Node::setNext(int next) { m_next = next; }    
void Node::setLongitude(double longitude) { m_longitude = longitude; }
void Node::setLatitude(double lat) { m_latitude = lat; }
  
//not sure how to make const correct
const int Node::parent() const { return m_parent; }

const int Node::rank() const { return m_rank; }
int Node::id() const { return m_id; }
const string & Node::name() const {  return m_name; }
const bool Node::visited() const { return m_visited;  }
const int Node::pre() const { return m_pre_visit;  }  
const int Node::post() const {  return m_post_visit;  }  
const int Node::cc() const {  return m_cc;  }  
const double Node::dist() const { return m_distance; }
const double Node::latitude() const { return m_latitude; }
const double Node::longitude() const { return m_longitude; }