#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
using namespace std;

struct Graph
{
	int V, E;
	vector< pair<int, pair<int, int>> > edges;
	// Constructor 
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}

	void addEdge(int u, int v, int w)
	{
		edges.push_back({ w, {u, v} });
	}

	//YOUR CODE HERE
	int kruskalMST() {
		// TODO: return weight of the minimum spanning tree.
		sort(edges.begin(), edges.end());
		vector<int>  mark(V);
		for (int i = 0; i < V; i++) mark[i] = i;
		int n = 0;
		int count =0;
		while (count!=V-1) {
			if (mark[edges[0].second.first] != mark[edges[0].second.second]) {
				n += edges[0].first;
				int tmp = mark[edges[0].second.second];
				int tmp2 = mark[edges[0].second.first];
				mark[edges[0].second.second] = mark[edges[0].second.first];
				for (int i = 0; i < V; i++) {
					if (mark[i] == tmp) mark[i] = tmp2;
				}
				edges.erase(edges.begin());
				count++;
			}
			else {
				edges.erase(edges.begin());
			}
		}
		return n;
	}

};
int Dijkstra(int** graph, int src, int dst) {
	// TODO: return the length of shortest path from src to dst.
	vector<int> distance(6);
	for (int i = 0; i < 6; i++) {
		distance[i] = 10000;
	}
	vector<int > mark(6);
	distance[src] = 0;
	mark[src] = 1;
	while (mark[dst] != 1) {
		for (int i = 0; i < 6; i++) {
			if (graph[src][i] != 0&&mark[i]!=1) {
				if (distance[i] > graph[src][i]+distance[src]) distance[i] = graph[src][i] + distance[src];
			}
		}
		bool flag = 0;
		int pos = 0;
		for (int i = 0; i < 6; i++) {
			if (flag == 0) {
				if (mark[i] != 1) { pos = i; flag = 1; }
			}
			else if (mark[i] != 1 && distance[i] < distance[pos]) pos = i;
		}
		mark[pos] = 1;
		src = pos;
	}
	return distance[dst];
}
int main() {
	int n = 6;
	int init[6][6] = {
		{0, 10, 20, 0, 0, 0},
		{10, 0, 0, 50, 10, 0},
		{20, 0, 0, 20, 33, 0},
		{0, 50, 20, 0, 20, 2},
		{0, 10, 33, 20, 0, 1},
		{0, 0, 0, 2, 1, 0} };

	int** graph = new int* [n];
	for (int i = 0; i < n; ++i) {
		graph[i] = init[i];
	}

	cout << Dijkstra(graph, 0, 5);
}