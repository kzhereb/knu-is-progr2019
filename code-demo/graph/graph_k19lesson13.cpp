/*
 * graph_k19lesson13.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: KZ
 */
#include <iostream>
using std::cout;
using std::endl;

namespace k19lesson13 {
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

struct Node {
	int vertex;
	Node* next;
	Node(int _vertex, Node* _next=nullptr) {
		vertex = _vertex;
		next = _next;
	}
};

struct List {
	Node* start;
	Node* end;
	List() {
		start = end = nullptr;
	}
};

void add_to_list(List& list, int vertex) {
	Node* new_node = new Node(vertex);
	if (list.start) {
		list.end->next = new_node;
	} else {
		list.start = new_node;
	}
	list.end = new_node;
}

Node* search_list(const List& list, int vertex) {
	Node* result = list.start;
	while(result) {
		if(result->vertex==vertex) {
			return result;
		}
		result = result->next;
	}
	return result;
}

struct GraphStruct {
	List neighbours[MAX_VERTICES];
	int vertex_count;
	GraphStruct(int vertices) {
		if (vertices>MAX_VERTICES) {
			throw std::invalid_argument("Too many vertices");
		}
		vertex_count = vertices;
	}
};

void add_edge(GraphStruct& graph, int from, int to ){
	if (from>=graph.vertex_count
			|| to>=graph.vertex_count) {
		throw std::invalid_argument("Vertex not in graph");
	}
	List& from_neighbours = graph.neighbours[from];
	if (search_list(from_neighbours, to)) {
		cout<<"Already in graph"<<endl;
	} else {
		add_to_list(from_neighbours,to);
	}
}

void print_edges(const GraphStruct& graph) {
	for (int i=0;i<graph.vertex_count;i++) {
		Node* cur = graph.neighbours[i].start;
		while(cur) {
			int j = cur->vertex;
			cout<<"("<<i<<","<<j<<") ";
			cur = cur->next;
		}
	}
}

//GraphStruct convert_to_struct(const GraphMatr&);
//GraphMatr convert_to_matr(const GraphStruct&);


int main() {
	//GraphMatr graph(5);
	GraphStruct graph(5);
	add_edge(graph,0,1);
	add_edge(graph,2,3);
	add_edge(graph,0,4);
	print_edges(graph);

}


}
