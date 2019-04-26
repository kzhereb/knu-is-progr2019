/*
 * spanningtree_k19lesson14.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: KZ
 */
#include <iostream>
using std::cout;
using std::endl;

//copypaste
const int MAX_VERTICES = 20;

struct GraphMatr {
	bool adjacent[MAX_VERTICES][MAX_VERTICES];
	int vertex_count;
	bool is_oriented=false;
	GraphMatr(int vertices) {
		if (vertices>MAX_VERTICES) {
			throw std::invalid_argument("Too many vertices");
		}
		vertex_count = vertices;
		for(int i=0;i<vertex_count;i++) {
			for(int j=0; j<vertex_count;j++) {
				adjacent[i][j]=false;
			}
		}
	}
};

void add_edge(GraphMatr& graph, int from, int to, int weight=1 ){
	if (from>=graph.vertex_count
			|| to>=graph.vertex_count) {
		throw std::invalid_argument("Vertex not in graph");
	}
	graph.adjacent[from][to] = weight;
	if (!graph.is_oriented) {
		graph.adjacent[to][from] = weight;
	}
}

void print_edges(const GraphMatr& graph) {
	for(int i=0; i<graph.vertex_count;i++) {
		int j = 0;
		if (!graph.is_oriented) { j = i+1; }
		for (; j<graph.vertex_count;j++) {
			if (graph.adjacent[i][j]) {
				cout<<"("<<i<<","<<j<<",w="<<graph.adjacent[i][j]<<") ";
			}
		}
	}
	cout<<endl;
}
//copypaste-end


int main() {
	GraphMatr graph(5);
	add_edge(graph,0,1);
	add_edge(graph,2,3);
	add_edge(graph,0,4);
	print_edges(graph);
	return 0;
}



