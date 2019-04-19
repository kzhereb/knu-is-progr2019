/*
 * graph_k19lesson13.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: KZ
 */
#include <iostream>
using std::cout;
using std::endl;

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

void add_edge(GraphMatr& graph, int from, int to ){
	if (from>=graph.vertex_count
			|| to>=graph.vertex_count) {
		throw std::invalid_argument("Vertex not in graph");
	}
	graph.adjacent[from][to] = 1;
	if (!graph.is_oriented) {
		graph.adjacent[to][from] = 1;
	}
}

void print_edges(const GraphMatr& graph) {
	for(int i=0; i<graph.vertex_count;i++) {
		int j = 0;
		if (!graph.is_oriented) { j = i+1; }
		for (; j<graph.vertex_count;j++) {
			if (graph.adjacent[i][j]) {
				cout<<"("<<i<<","<<j<<") ";
			}
		}
	}
	cout<<endl;
}






int main() {
	GraphMatr graph(5);
	add_edge(graph,0,1);
	add_edge(graph,2,3);
	add_edge(graph,0,4);
	print_edges(graph);

}


