#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include<queue>
using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const& i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const& i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx)
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};
class Graph
{
private:
	int V;
	Adjacency* adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
	}

	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}

	void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
	void helpDFS(int v, Adjacency*& arr, vector<int>& mark) {
		mark[v] = 1;
		arr->push(v);
		for (int i = 0; i < adj[v].getSize(); i++)
		{
			if (mark[adj[v].getElement(i)]==0) {
				helpDFS(adj[v].getElement(i), arr, mark);
			}
		}
	}
	Adjacency* DFS(int v) {
		vector<int> mark(V);
		stack<int> tan;
		Adjacency* arr = new Adjacency();
		helpDFS(v, arr, mark);
		return arr;
	}
	Adjacency* BFS(int v)
	{
		// v is a vertex we start BFS
		queue<int>tan;
		vector<int> mark(V);
		tan.push(v);
		Adjacency* arr = new Adjacency();
		while (!tan.empty()) {
			int n = tan.front();
			int size = adj[n].getSize();
			tan.pop();
			arr->push(n);
			mark[n] = 1;
			for (int i = 0; i < size; i++) {
				if (mark[adj[n].getElement(i)] == 0) {
					tan.push(adj[n].getElement(i)); mark[adj[n].getElement(i)] = 1;
				}
			}

		}
		return arr;
	}

	
	
};

class DirectedGraph
{
	int V;
	list<int>* adj;
	bool isCyclicUtil(int v, bool visited[], bool* rs);
public:
	DirectedGraph() {
		V = 0;
		adj = NULL;
	}
	DirectedGraph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
	}
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}
	
	bool isCyclic()
	{
		// Student answer
		vector<int> tan(V);
		for (int i = 0; i < V; i++) {
			tan[i] = adj[i].size();
		}
		while (1) {
			bool flag = 1;
			int j = 0;

			for (auto it : tan) {
				if (it != 0 && it != -1) {
					flag = 0; break;
				}
			}
			if (flag) return 0;
			for (auto it = tan.begin(); it != tan.end(); it++) {
				if (*it == 0) {
					flag = 1;
					tan[j]--;
					break;
				}
				j++;
			}
			if (!flag) return 1;
			for (int i = 0; i < V; i++) {
				if (find(adj[i].begin(), adj[i].end(), j) != adj[i].end()) {
					tan[i]--;
				}
			}


		}
	}
};
int main() {
	DirectedGraph g(8);
	int edege[][2] = { {0,6}, {1,2}, {1,4}, {1,6}, {3,0}, {3,4}, {5,1}, {7,0}, {7,1} };

	for (int i = 0; i < 9; i++)
		g.addEdge(edege[i][0], edege[i][1]);

	if (g.isCyclic())
		cout << "Graph contains cycle";
	else
		cout << "Graph doesn't contain cycle";
}
