//read into file
//check how the adj list is represented using print fcn
//then hardcode the expected pre and post times for each edge/node that would be expected by the scan method
  //do by hand, then hardcode/encode into test fcn

#include <iterator>
#include <list>
#include <stack>
#include <cassert>
#include <algorithm>
#include <queue>
#include <functional>

#include "Edge.h"
#include "Node.h"
#include "Graph.h"
#include "ListPriorityQueue.h"
#include "HeapPriorityQueue.h"
#include "Debug.h"
#include "Dijkstra.h"
#include "Kruskal.h"
  
//#include "Rcpp.h"

// [[Rcpp::plugins("cpp11")]]
  
using namespace std;

void LargeGraphList(Graph & g) { Node root = g.getNode(0); Dijkstra_list(g, root); }
void LargeGraphHeap(Graph & g) { Node root = g.getNode(0); Dijkstra_heap(g, root); }

//[[Rcpp::export]]
void LargeGraphCCWrapper() {
  Graph g1("in_test_very_big.txt");
  Kruskal_MST_cclabels(g1);
}

//[[Rcpp::export]]
void LargeGraphDJSetWrapper() {
  Graph g1("in_test_very_big.txt");
  Kruskal_MST_djsets(g1);
}


//[[Rcpp::export]]
int main() {
	if(testall()) 
		cout << "All tests PASSED!" << endl;
	else
		cout << "Some test FAILED!" << endl;
	
	// Graph g;
	
	// g.scan_tmg("tmg-master-simple.txt");
	
	// Node s = g.getNode(86257);
	// Node e = g.getNode(38953);
	
	// Dijkstra_tmg(g, s, e);
}

/***R

source("random_graph_dist.R")

##Here you can call the functions declared in random_graph.R.
#random.graph(number.of.nodes = 10, number.of.edges = 100, min_dist = 0, max_dist = 5, output.file = "in_test_small_1.txt")
#random.graph(number.of.nodes = 50, number.of.edges = 500, min_dist = 0, max_dist = 5,output.file = "in_test_small_2.txt")
#random.graph(number.of.nodes = 500, number.of.edges = 5000, min_dist = 0, max_dist = 5,output.file = "in_test_small_3.txt")
#random.graph(number.of.nodes = 1000, number.of.edges = 10000, min_dist = 0, max_dist = 5,output.file = "in_test_small_4.txt")
#random.graph(number.of.nodes = 2000, number.of.edges = 20000, min_dist = 0, max_dist = 5,output.file = "in_test_small_5.txt")
#random.graph(number.of.nodes = 10000, number.of.edges = 30000, min_dist = 0, max_dist = 5,output.file = "in_test_big.txt")

#t1 <- graph.compare("C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\in_test_1.txt", "C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\out_test_1.txt")
#t2 <- graph.compare("C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\in_test_2.txt", "C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\out_test_2.txt")
#t3 <- graph.compare("C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\in_test_3.txt", "C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\out_test_3.txt")
#t4 <- graph.compare("C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\in_test_4.txt", "C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\out_test_4.txt")
#t5 <- graph.compare("C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\in_test_5.txt", "C:\\Users\\jkeys\\Desktop\\NMSU\\Algorithms\\lab8\\out_test_5.txt")
##t6 <-graph.compare("C:\\Users\\jkeys\\Desktop\\NMSU\\lab4\\in_test_big.txt", "C:\\Users\\jkeys\\Desktop\\NMSU\\lab4\\out_test_big.txt")


#if(t1 && t2 && t3 && t4 && t5) {
#	print("All tests passed!")
#}

num_samples <- 5
num_steps   <- 5
node_step   <- 2500
edge_step   <- 5000

nodes <- seq(node_step, node_step*num_steps, node_step)
edges <- seq(node_step, edge_step*num_steps, edge_step)

runtime_cc <- vector(length=num_samples)
runtime_djset <- vector(length=num_samples)
cc_avg <- vector(length=num_steps)
djset_avg <- vector(length=num_steps)

for (i in 1:num_steps) {
	node_size <- node_step + node_step * i
	edge_size <- edge_step + edge_step * i	
	random.graph(number.of.nodes = node_size, number.of.edges = edge_size, min_dist = 1, max_dist =  10, output.file = "in_test_very_big.txt")

	for (j in 1:num_samples) {
		runtime_djset[j] <- system.time(LargeGraphDJSetWrapper())[["user.self"]]
		runtime_cc[j] <- system.time(LargeGraphCCWrapper())[["user.self"]]
	}
	
	cc_avg[i] <- sum(runtime_cc) / num_samples
	djset_avg[i] <- sum(runtime_djset) / num_samples

  print(nodes[i])
  print("Average Kruskal cc time: ")
  print(cc_avg[i])  
  print("Average Kruskal djset time: ")
  print(djset_avg[i])  
}

plot(nodes, cc_avg, type = "l", xlab="Nodes", ylab = "seconds", col = "red", main = "Kruskal CC")
lines(edges, cc_avg, xlab="Edges", type = "l", ylab = "seconds", col = "green", main = "Kruskal CC")
plot(nodes, djset_avg, type = "l", xlab="Nodes", ylab = "seconds", col = "red", main = "Kruskal Disjoint sets")
lines(edges, djset_avg, xlab="Edges", type = "l", ylab = "seconds", col = "green", main = "Kruskal Disjoint sets")

*/

