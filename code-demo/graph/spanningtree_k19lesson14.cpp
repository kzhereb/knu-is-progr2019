/*
 * spanningtree_k19lesson14.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: KZ
 */

#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;

const int MAX_VERTICES = 20;

struct GraphMatr {
	int adjacent[MAX_VERTICES][MAX_VERTICES];
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

struct Edge {
	int from;
	int to;
	int weight;
	Edge(int _from, int _to, int w=1) {
		from=_from;
		to = _to;
		weight = w;
	}
};

std::vector<Edge> get_edges_sorted(GraphMatr const & graph) {
	std::vector<Edge> result;
	for(int i=0;i<graph.vertex_count;i++) {
		for (int j=i+1;j<graph.vertex_count;j++) {
			if (graph.adjacent[i][j]) {
				result.emplace_back(Edge{i,j,graph.adjacent[i][j]});
			}
		}
	}
	std::sort(result.begin(),result.end(),
			[](Edge e1, Edge e2) {
				if (e1.weight<e2.weight) return true;
				return false;
	});
	return result;
}

GraphMatr min_spanning_tree_kruskal(GraphMatr const & graph ) {
	GraphMatr result(graph.vertex_count);
	int which_tree[MAX_VERTICES];
	for(int i=0;i<graph.vertex_count;i++) {
		which_tree[i]=i;
	}
	auto edges = get_edges_sorted(graph);
	for(auto edge:edges) {
		if (which_tree[edge.from]!=which_tree[edge.to]) {
			add_edge(result,edge.from,edge.to,edge.weight);
			for (int i=0;i<graph.vertex_count;i++) {
				if(which_tree[i] == which_tree[edge.to]) {
					which_tree[i] = which_tree[edge.from];
				}
			}

		}
	}
	return result;
}

GraphMatr min_spanning_tree_djp(GraphMatr const & graph ) {
	GraphMatr result(graph.vertex_count);
	int cheapest_cost[MAX_VERTICES];
	int cheapest_edge[MAX_VERTICES];
	bool already_picked[MAX_VERTICES];
	int vertices_in_result=0;
	for(int i=0;i<graph.vertex_count;i++) {
		cheapest_cost[i]=INT32_MAX;
		cheapest_edge[i]=-1;
		already_picked[i]=false;
	}
	//already_picked[0]=true;
	while (vertices_in_result<graph.vertex_count){
		int min_cost = INT32_MAX,min_vertex=0;

		for(int i=0;i<graph.vertex_count;i++) {
			if (!already_picked[i] && cheapest_cost[i]<min_cost) {
				min_vertex=i;
				min_cost= cheapest_cost[i];
			}
		}
		cout<<"Picked "<<min_vertex<<endl;
		vertices_in_result++;
		already_picked[min_vertex]=true;
		if(cheapest_edge[min_vertex]!=-1) {
			add_edge(result,min_vertex,cheapest_edge[min_vertex],
					graph.adjacent[min_vertex][cheapest_edge[min_vertex]]);
		}
		for(int i=0;i<graph.vertex_count;i++) {
			if (!already_picked[i]
				&& graph.adjacent[min_vertex][i]
				&& graph.adjacent[min_vertex][i] < cheapest_cost[i]) {
				cheapest_cost[i] = graph.adjacent[min_vertex][i];
				cheapest_edge[i] = min_vertex;
			}
		}
		for(int i=0;i<graph.vertex_count;i++) {
			cout<<i<<": cost="<<cheapest_cost[i]<<",edge="<<cheapest_edge[i]<<endl;
		}
	}

	return result;
}

int main() {
	GraphMatr graph(6);
	//GraphStruct graph(5);
	add_edge(graph,0,1,1);
	add_edge(graph,0,3,4);
	add_edge(graph,0,4,3);
	add_edge(graph,1,3,4);
	add_edge(graph,1,4,2);
	add_edge(graph,2,4,4);
	add_edge(graph,2,5,5);
	add_edge(graph,3,4,4);
	add_edge(graph,4,5,7);
	print_edges(graph);
	auto edges = get_edges_sorted(graph);
	for(Edge& e:edges) {
		cout<<e.from<<","<<e.to<<","<<e.weight<<endl;
	}
	auto span_tree = min_spanning_tree_kruskal(graph);
	print_edges(span_tree);
	auto span_tree2 = min_spanning_tree_djp(graph);
	print_edges(span_tree2);

}
