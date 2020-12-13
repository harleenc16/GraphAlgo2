#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <list>
#include "Graph.h"
using namespace std;

Graph::Graph(){
	
	//0 vertices, 0 edges
	x=0;
	y=0;

}

int Graph::addVertex(int v){
	
	vertices.insert(v);
	return v;
}

void Graph::addEdge(directedEdge newEdge, int weight){
	
	edges.insert(newEdge);
	weights.insert({newEdge , weight});
	
}


void Graph::generateGraph(string fileName){
	
	fstream input;
	input.open(fileName);

	input >> x >> y;
	input.ignore();
	getline(input , graph);

	for (int i = 1 ; i <= y ; i++){
		int source, dest , weight;
		input >> source >> dest >> weight;

		addVertex(source);
		addVertex(dest);
		directedEdge newEdge = {source , dest};
		addEdge(newEdge , weight);

		adj[source].push_back({dest , weight});

	}
}

void Graph::print(){
	
	for (int i = 0 ; i < x ; i++){
		sort(adj[i].begin(), adj[i].end());
}

	for (int i = 0 ; i < x ; i++){
		cout << i << ": ";
			for (int j = 0 ; j < adj[i].size() ; j++){
				cout << adj[i][j].first << " " << "(" << adj[i][j].second << ") ";
				}
			cout << '\n';
		}
}



//Modified Dijkstra Algorithm idea:
//Initialize count array(stores shortest paths)
//when any vertex is relaxed, count =1
//"formula"
// if (dist[v] + len < dist[to]){
	//dist[to] = dist[v] + len;
    //count[to]  = 1;
// }
//If vertex has already been relaxed, there is another shortest path, increment count variable
void Graph::modifiedDijkstra(int source){
	
	dist.assign(x , INF);

	dist[source] = 0;
	
	//initialize visted as false
	vector<bool> u(x , false);


	for (int i = 0 ; i < x ; i++){
		int v = -1;
		for (int j = 0 ; j < x ; j++){
			if (!u[j] && (v == -1 || dist[j] < dist[v]))
				v = j;
		}

		if (dist[v] == INF)break;

		u[v] = true;

		for (auto edge : adj[v]){
			int to = edge.first;
			int len = edge.second;

			if (dist[v] + len == dist[to])count[to]++;

			if (dist[v] + len < dist[to]){
				dist[to] = dist[v] + len;
				count[to]  = 1;
			}

		}

	}

	cout << "Shortest Path from node " << source << ":" << '\n';

	for (int i = 0 ; i < x ; i++){
		if (i == source)continue;

		cout << "Distance to vertex " << i << " is " << dist[i] << " and there are " << count[i] << " shortest paths" << '\n';
	}


}
