//Graph.cpp

#include <vector>
#include <list>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Graph.h"
#include "Edge.h"
#include "Node.h"
#include "Debug.h"

using namespace std;


/************************ ctors & scan from/save to file *************************/

Graph::Graph() { 
	initEmpty(MAX_NODES); 
}

Graph::Graph(int num_nodes) { 
	initEmpty(num_nodes); 
}
 

Graph::Graph(const string & file) {
	scan(file);	
}

void Graph::scan(const string & file) {
    ifstream fs;
    string line, u, v;
	int u_id, v_id, weight;	
    std::set<string> node_names;
	std::map<string, int> node_id_map;
		
	initEmpty(MAX_NODES); //reserve memory space, initialize vector set 
	
	fs.open(file.c_str());	
	assert(fs.is_open());
	
	while (!fs.eof()) {	  
		fs >> u >> v >> weight;
		
		 u = trim(u); /***/ v = trim(v); 		 
		 if(u.size() == 0 || v.size() == 0) continue; //skip blank lines (EOF)

		set<string>::iterator u_string_itr = node_names.find(u);
		 
		//check if node exists
		if(u_string_itr == node_names.end()) { //does not exist
			u_id = current_id;
			current_id++;			
			
			node_names.insert(u);
			node_id_map.insert( pair<string, int>(u, u_id)  );
			Node nodeU(u, u_id); //the source node; put it in the node_set
			m_nodes.push_back(nodeU);
		} else { //does exist, find that nodes id by looking up node name in map (node name string is key, node id is value)
			u_id = node_id_map.at(u);
		}		
		
		set<string>::iterator v_string_itr = node_names.find(v);
			
		if(v_string_itr == node_names.end()) {
			v_id = current_id;
			current_id++;			
			
			node_names.insert(v);
			node_id_map.insert( pair<string, int>(v, v_id)  );
			Node nodeV(v, v_id);
			m_nodes.push_back(nodeV);
		} 	else {
			v_id = node_id_map.at(v);
		}		
		
		Node child(v, v_id);	
		Edge edge(u_id, v_id, weight);
		
		m_adjList[u_id].insert(child);		
		m_edgeList[u_id].push_front(edge);
	} //end while		
	
	fs.close();
}

void Graph::scan_undirected(const string & file) {
    ifstream fs;
    string line, u, v;
	int u_id, v_id, weight;	
    std::set<string> node_names;
	std::map<string, int> node_id_map;
		
	initEmpty(MAX_NODES); //reserve memory space, initialize vector set 
	
	fs.open(file.c_str());	
	assert(fs.is_open());
	
	while (!fs.eof()) {	  
		fs >> u >> v >> weight;
		
		 u = trim(u); /***/ v = trim(v); 		 
		 if(u.size() == 0 || v.size() == 0) continue; //skip blank lines (EOF)

		set<string>::iterator u_string_itr = node_names.find(u);
		 
		//check if node exists
		if(u_string_itr == node_names.end()) { //does not exist
			u_id = current_id;
			current_id++;			
			
			node_names.insert(u);
			node_id_map.insert( pair<string, int>(u, u_id)  );
			Node nodeU(u, u_id); //the source node; put it in the node_set
			m_nodes.push_back(nodeU);
		} else { //does exist, find that nodes id by looking up node name in map (node name string is key, node id is value)
			u_id = node_id_map.at(u);
		}		
		
		set<string>::iterator v_string_itr = node_names.find(v);
			
		if(v_string_itr == node_names.end()) {
			v_id = current_id;
			current_id++;			
			
			node_names.insert(v);
			node_id_map.insert( pair<string, int>(v, v_id)  );
			Node nodeV(v, v_id);
			m_nodes.push_back(nodeV);
		} 	else {
			v_id = node_id_map.at(v);
		}		
		
		Node node_u = getNode(u_id);
		Node node_v = getNode(v_id);
		Edge u_v_edge(u_id, v_id, weight);
		Edge v_u_edge(v_id, u_id, weight);
		
		m_adjList[u_id].insert(node_v);		
		m_adjList[v_id].insert(node_u);
		m_edgeList[u_id].push_front(u_v_edge);
		m_edgeList[v_id].push_front(v_u_edge);
	} //end while		
	
	fs.close();
}


void Graph::scan_tmg(const string & file) {	
	string tmg_start, tmg_version, tmg_simple;
	string num_nodes_s, num_edges_s;
	string waypoint, latitude_s, longitude_s;	
	int u_id, v_id, weight;
	double latitude, longitude;
    ifstream fs;
	
	int num_nodes, num_edges;
	
	fs.open(file.c_str()); assert(fs.is_open());
	
	/**** read in header data ****/
	
	fs >> tmg_start >> tmg_version >> tmg_simple >> num_nodes >> num_edges;
	
	assert(tmg_start == "TMG"); assert(tmg_version == "1.0"); assert(tmg_simple == "simple");	
		
	initEmpty(num_edges + 10); //twice num_edges because undirected
	
	/**** read in all nodes ****/
	
	cout << num_nodes << endl << num_edges << endl;	
	
	for (size_t i = 0; i != num_nodes; i++) {
		fs >> waypoint >> latitude >> longitude;
		// cout << waypoint << latitude_s << longitude_s << endl;
				 
		u_id = current_id;
		current_id++;			
			
		Node n(waypoint, u_id); 
		
		n.setLatitude(latitude);
		n.setLongitude(longitude);
		
		m_nodes.push_back(n);	
	} //end for
	
	
	/**** have read in all nodes, now read in all edges ****/
	
	string adjRoads;
	
	
	for (size_t i = 0; i != num_edges; i++) {
		fs >> u_id >> v_id >> adjRoads;
		
		Node u = m_nodes[u_id]; 
		Node v = m_nodes[v_id];
		
		double u_v_distance = calculateDistance(u, v);
				
		Edge u_v(u_id, v_id, u_v_distance);
		Edge v_u(v_id, u_id, u_v_distance); //undirected
		
		addEdge(u, v); addEdge(v, u);
		
		addEdgeObj(u, u_v); addEdgeObj(v, v_u);
		
		setEdgeRoads(m_nodes[u_id], adjRoads);
		setEdgeRoads(m_nodes[v_id], adjRoads);
	} //end for
	
	fs.close();
}


/************************* setters *************************/
  
void Graph::addEdge(const Node & a, const Node & b) { m_adjList[a.id()].insert(b); }
void Graph::addEdgeObj(const Node & a, const Edge & b) { m_edgeList[a.id()].push_front(b); }
void Graph::addNode(const Node & a) { m_nodes[a.id()] = a; }

void Graph::setRank(const Node & a, int rank) { m_nodes[a.id()].setRank(rank); }  
void Graph::setVisited(const Node & a) { m_nodes[a.id()].setVisited(); }  
void Graph::setPre(const Node & a, int pre) { m_nodes[a.id()].setPre(pre); }  
void Graph::setPost(const Node & a, int post) { m_nodes[a.id()].setPost(post); }  
void Graph::setDist(const Node & a, double dist) { m_nodes[a.id()].setDist(dist); }  
void Graph::setCC(const Node & a, int cc) { m_nodes[a.id()].setCC(cc); }  
void Graph::setParent(const Node & a, int parent) { m_nodes[a.id()].setParent(parent); }
void Graph::setNext(const Node & a, int next) { m_nodes[a.id()].setNext(next); }
void Graph::setEdgeRoads(const Node & a, string roads) { m_nodes[a.id()].setEdgeRoads(roads); }

void Graph::incrementClock() { m_clock++; }   
void Graph::incrementCurrentCC() { current_cc++; } 
  
  void Graph::pushNode(const Node & a) {
	  m_nodes.push_back(a);
  }
    
  void Graph::pushEdge(const Edge & e) {
	  m_edges_MST.push_back(e);
  }

/************************* getters *************************/

const size_t Graph::num_edges() const { return m_edgeList.size(); }

const string Graph::name(int u_id) const { return m_nodes[u_id].name(); }

const bool Graph::visited(const Node & a) const {  return m_nodes[a.id()].visited();  }  
const double Graph::dist(const Node & a) const { return m_nodes[a.id()].dist(); }  
const int Graph::pre(const Node & a) const { return m_nodes[a.id()].pre(); }  
const int Graph::post(const Node & a) const { return m_nodes[a.id()].post(); }  
const int Graph::cc(const Node & a) const { return m_nodes[a.id()].cc(); }  
const int Graph::currentCC() const { return current_cc; }  
const size_t Graph::num_nodes() const { return m_nodes.size(); }
const int Graph::clock() const { return m_clock; }
const int Graph::next(const Node & a) const { return m_nodes[a.id()].next(); }

	const int Graph::rank(const Node & a) const { return m_nodes[a.id()].rank(); }
  const int Graph::max_nodes() const { return m_max_nodes; }
const string Graph::edgeRoads(const Node & a) const { return m_nodes[a.id()].edgeRoads(); }

int Graph::parent(const Node & a) { return m_nodes[a.id()].parent(); }

vector<Node>::iterator Graph::begin() { return m_nodes.begin(); }  
vector<Node>::iterator Graph::end() { return m_nodes.end(); } 
  
const Node & Graph::getNode (size_t i) const { return m_nodes[i]; }

set <Node> & Graph::getAdjNodes(const Node & a) { return m_adjList[a.id()]; }    
const set <Node> & Graph::getAdjNodes(const Node & a) const { return m_adjList[a.id()]; }

list <Edge> & Graph::getEdges(const Node & a) { return m_edgeList[a.id()]; }    
const list  <Edge> & Graph::getEdges(const Node & a) const { return m_edgeList[a.id()]; }


  
vector<Node> Graph::nodes() { return m_nodes; }
  
const vector<Edge> & Graph::get_MST() const { return m_edges_MST; }

// const vector<Edge> Graph::get_MST() const { return m_edges_MST; }
  
/************************* test, print and debug *************************/

bool Graph::sameDistances(vector<int> V) {
	assert(m_nodes.size() == V.size());
	
	for(size_t i = 0; i != V.size(); i++) {
		if(V.at(i) != dist(m_nodes.at(i)))
			return false;
	}
	
	return true;
}

bool Graph::sameEdges(vector<Edge> E) {
	assert(m_edges_MST.size() == E.size());	
	
	for(size_t i = 0; i != E.size(); i++) {
		cerr << "in same edges, edge: ";
		m_edges_MST.at(i).print(*this);
		if( !m_edges_MST.at(i).equals(E.at(i)) )
			return false;
	}
	
	return true;
}

double calculateDistance(Node & u, Node & v) {
	const double EARTH_RADIUS = 3961.0;
	const double MY_PI = 3.14159;
	
	double lat_change = (v.latitude() - u.latitude())*MY_PI/180.0; 
	double long_change = (v.longitude() - u.longitude())*MY_PI/180.0;
	
	double a = sin(lat_change/2.0)*sin(lat_change/2.0)  +  (  cos(u.latitude()*MY_PI/180.0)*cos(v.latitude()*MY_PI/180.0)*sin(long_change/2.0)*sin(long_change/2.0) );
	
	double c = 2.0 * atan2(sqrt(a), sqrt(1-a));
	double d = EARTH_RADIUS*c;

	return d;	
}

void Graph::printNames() { 
	cout << "Nodes in the graph index: " << endl;
	for (unsigned int i = 0; i < this->num_nodes(); i++) {
	  cout << this->getNode(i).name() << " ";
	}		
}
  
  
void printSet(set<string> s) {
	cerr << "printing set of strings already loaded into m_nodes: " << endl;
	for(set<string>::iterator itr = s.begin(); itr != s.end(); itr++)
		cerr << *itr << "_and size of it: " << itr->size() << endl;
	
	cerr << "exit printSet" << endl;
}


/************************* init, update and reset *************************/

void Graph::resetClock() { m_clock = 1; }  
void Graph::resetAllDist() { 
	for(size_t i = 0; i != m_nodes.size(); i++) {
		m_nodes[i].setDist(M_INFINITY); 
		m_nodes[i].setParent(-1);
	}
}
  
void Graph::resetAllVisited() { 
	for(size_t i = 0; i != m_nodes.size(); i++) 
		m_nodes[i].resetVisitedFlag(); 
}  

void Graph::clearNodes() { 
	m_nodes.clear(); 
}  

void Graph::reset() {	
	this->resetClock();
	this->current_cc = 0;
	
  for (size_t i = 0; i != this->m_nodes.size(); i++) { 
	setDist(m_nodes[i], M_INFINITY);
	this->m_nodes[i].resetVisitedFlag();
	setPre(this->m_nodes[i], -1);
	setPost(this->m_nodes[i], -1);
  }
}

void Graph::initEmpty(int max_nodes) {
	current_id = 0;
	current_cc = 0;
	m_clock = 0;
	
	m_nodes.clear();
	m_adjList.clear();
	m_edgeList.clear();
	
	m_nodes.reserve(max_nodes); 
	m_adjList.reserve(max_nodes); 
	m_edgeList.reserve(max_nodes);
	set<Node> empty_list;	
	list<Edge> empty_edge_list;	
	for(size_t i = 0; i != max_nodes; i++) {
		m_adjList.push_back(empty_list);
		m_edgeList.push_back(empty_edge_list);
	}
}

void Graph::copyNodes(Graph & g) {
	for(size_t i = 0; i != g.num_nodes(); i++) {
		this->m_nodes.push_back( g.getNode(i) );
	}
}

void Graph::copyEdges(Graph & g) {
	for(size_t i = 0; i != g.num_nodes(); i++) {
		this->m_edgeList.push_back( g.getEdges(g.getNode(i)) );
	}
}

// void Graph::copyEdges(Graph & g) {
	// for(size_t i = 0; i != g.num_nodes(); i++) {
		// this->m_edgeList.push_back( g.getEdges(g.getNode(i)) );
	// }
// }

Graph Graph::reverse() {
	Graph g_new;
	g_new.initEmpty(75000); //75,000 nodes
	g_new.copyNodes(*this);
			
	for(unsigned int u = 0; u != m_nodes.size(); u++) {
		set<Node> adjNodes = getAdjNodes(m_nodes[u]);
		for(set<Node>::iterator v = adjNodes.begin(); v != adjNodes.end(); v++) {
			g_new.addEdge(*v, m_nodes[u]);
		}
 	}
	
	return g_new;
}


/************************* file output *************************/

void Graph::save(const string & file) const {
	ofstream fs( file.c_str() );
	assert( fs.is_open() );
	
	
	for(unsigned int u = 0; u != m_nodes.size(); u++) {
		set<Node> adjNodes = getAdjNodes(m_nodes[u]);
		list<Edge> uEdges = getEdges(m_nodes[u]);
		//only print to file if this node has children (directed)
		for(list<Edge>::iterator e = uEdges.begin(); e != uEdges.end(); e++) {
			fs << name(e->u_id()) << '\t' << name(e->v_id()) << '\t' << e->weight() << '\n';
		}
 	}
		
	fs.close();
}

void Graph::saveUndirected(const string & file) const {
	ofstream fs( file.c_str() );
	assert( fs.is_open() );
		
	for(unsigned int u = 0; u != m_nodes.size(); u++) {
		set<Node> adjNodes = getAdjNodes(m_nodes[u]);
		for(set<Node>::iterator v = adjNodes.begin(); v != adjNodes.end(); v++) {
			fs << m_nodes[u].name() << '\t' << m_nodes[v->id()].name() << '\n';
			fs << m_nodes[v->id()].name() << '\t' << m_nodes[u].name() << '\n'; //may print duplicates;		
		}
 	}
	
	
	fs.close();
}


/************************* C++ stream output *************************/


std::ostream& operator<<(std::ostream & out, const Graph & g) {
	//cout << "in Graph out stream operator, g.m_nodes.size(): " << g.num_nodes() << endl;

	out << "Nodes in the graph: " << endl;
	for (unsigned int i = 0; i < g.num_nodes(); i++) {
	  out << g.getNode(i).name() << " ";
	}

	out << endl;
	out << "Adjacency list of the graph: " << endl;

	for (unsigned int i = 0; i < g.num_nodes(); i++) {
		out << "Node " << g.getNode ( i ).name() << ": ";
		const set<Node> neighbors = g.getAdjNodes(g.getNode(i));
		for (set < Node> :: const_iterator itr = neighbors.begin(); itr != neighbors.end(); ++itr) {
			out << itr->name() << " ";
	}
	  out << endl;
	}

	return out;
}  
