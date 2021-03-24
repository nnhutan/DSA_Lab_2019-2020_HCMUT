#include <iostream>
#include <list>
#include<vector>
#include <queue>
#include<stack>
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
class Graph {

	int V;
	Adjacency* adj;

public:
	Graph(int V) {
		this->V = V;
		adj = new Adjacency[V];
	}
	void addEdge(int v, int w) {
		adj[v].push(w);
	}

	//Heling functions
	/*bool isCyclic()
	{
		// Student answer
		vector<int> tan(V);
		for (int i = 0; i < V; i++) {
			//cout << adj[i].size();
			tan[i] = adj[i].getSize();
		}
		//return 1;
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
				for (int k = 0; k < adj[i].getSize(); k++) {
					if (adj[i].getElement(k) == j) tan[i]--;
				}
			}


		}
	}*/
	void topohelp(int v, stack<int>&result, vector<int>&mark) {
		mark[v] = 1;
		for (int i = 0; i < adj[v].getSize(); i++)
		{
			if (mark[adj[v].getElement(i)] == 0) {
				topohelp(adj[v].getElement(i), result, mark);
			}
		}
		result.push(v);
	}
	void topologicalSort() {
		stack<int> result; 
		vector<int> mark(V);
		for (int i = 0; i < V; i++)
		{
			if (mark[i] == 0) {
				topohelp(i, result, mark);
			}
		}
		while (!result.empty())
		{
			cout << result.top() <<" ";
			result.pop();
		}
	}
	 // number of vertices
	

	//void topologicalSortUtil(int v, bool visited[],
	//	stack<int>& Stack)
	//{
	//	// Mark the current node as visited. 
	//	visited[v] = true;

	//	// Recur for all the vertices 
	//	// adjacent to this vertex 
	//	
	//	for (int i =0; i < adj[v].getSize(); ++i)
	//		if (!visited[adj[v].getElement(i)])
	//			topologicalSortUtil(adj[v].getElement(i), visited, Stack);

	//	// Push current vertex to stack 
	//	// which stores result 
	//	Stack.push(v);
	//}

	//// The function to do Topological Sort. 
	//// It uses recursive topologicalSortUtil() 
	//void topologicalSort()
	//{
	//	stack<int> Stack;

	//	// Mark all the vertices as not visited 
	//	bool* visited = new bool[V];
	//	for (int i = 0; i < V; i++)
	//		visited[i] = false;

	//	// Call the recursive helper function 
	//	// to store Topological 
	//	// Sort starting from all 
	//	// vertices one by one 
	//	for (int i = 0; i < V; i++)
	//		if (visited[i] == false)
	//			topologicalSortUtil(i, visited, Stack);

	//	// Print contents of stack 
	//	while (Stack.empty() == false) {
	//		cout << Stack.top() << " ";
	//		Stack.pop();
	//	}
	//}
};
int main() {
	/*Graph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(3, 0);
	g.addEdge(3, 4);
	g.addEdge(2, 4);

	g.topologicalSort();*/
	Graph g(6);
	g.addEdge(5, 2);
	g.addEdge(5, 0);
	g.addEdge(4, 0);
	g.addEdge(4, 1);
	g.addEdge(2, 3);
	g.addEdge(3, 1);

	g.topologicalSort();
}