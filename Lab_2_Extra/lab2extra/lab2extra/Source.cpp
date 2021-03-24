#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
using namespace std;
bool isValidParentheses(string s)
{
	/*TODO*/
	stack<char> st;
	int t = s.size();
	for (int i = 0; i < t; i++)
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
			st.push(s[i]);
		if (s[i] == ')')
		{
			if (st.size() == 0)
				return 0;
			if (st.top() != '(')
				return 0;
			st.pop();
		}
		if (s[i] == ']')
		{
			if (st.size() == 0)
				return 0;
			if (st.top() != '[')
				return 0;
			st.pop();
		}
		if (s[i] == '}')
		{
			if (st.size() == 0)
				return 0;
			if (st.top() != '{')
				return 0;
			st.pop();
		}
	}
	if (st.size() == 0)
		return 1;
	else
		return 0;
}
int baseballScore(string ops)
{
	/*TODO*/
	stack<int> score;
	int t = ops.size();
	for (int i = 0; i < t; i++)
	{
		if (ops[i] >= 48 && ops[i] <= 57)
		{
			int x = ops[i] - '0';
			score.push(x);
		}
		if (ops[i] == 'C')
		{

			score.pop();
		}
		if (ops[i] == 'D')
		{
			int x = 2 * score.top();
			score.push(x);
		}
		if (ops[i] == '+')
		{
			int a = score.top();
			score.pop();
			int b = a + score.top();
			score.push(a);
			score.push(b);
		}
	}
	int ans = 0;
	int n = score.size();
	for (int i = 0; i < n; i++)
	{
		ans += score.top();
		score.pop();
	}

	return ans;
}
string removeDuplicates(string S)
{
	/*TODO*/
	stack<char> st;
	int t = S.size();
	for (int i = t - 1; i >= 0; i--)
	{
		if (st.size() == 0)
			st.push(S[i]);
		else if (S[i] != st.top())
			st.push(S[i]);
		else
			st.pop();
	}
	int n = st.size();
	string s = "";
	for (int i = 0; i < n; i++)
	{

		s += st.top();

		st.pop();
	}

	return s;
}
void bfs(vector<vector<int>> graph, int start)
{
	int n = graph.size();
	vector<int> mark(n);
	queue<int> temp;
	queue<int> result;
	mark[start] = 1;
	result.push(start);
	for (auto i : graph[start])
	{
		temp.push(i);
		mark[i] = 1;
	}
	while (temp.size())
	{
		for (auto i : graph[temp.front()])
		{
			if (mark[i] != 1)
			{
				temp.push(i);
				mark[i] = 1;
			}
		}
		result.push(temp.front());
		mark[temp.front()] = 1;
		temp.pop();
	}
	while (result.size() != 0)
	{
		cout << result.front() << " ";
		result.pop();
	}
}
bool isBipartite(vector<vector<int>> graph)
{
	vector<int> id(graph.size());
	queue<int> q;
	for (int i = 0; i < graph.size(); ++i)
	{
		if (id[i])
			continue;
		q.push(i);
		id[i] = 1;
		while (q.size())
		{
			int u = q.front();
			q.pop();
			for (int v : graph[u])
			{
				if (id[v])
				{
					if (id[v] != -id[u])
						return false;
					continue;
				}
				id[v] = -id[u];
				q.push(v);
			}
		}
	}
	return true;
}
vector<int> topologicalSorting(vector<vector<int>> graph)
{
	//int n = graph.size();
	//vector<int> q;
	//vector<int> id(n);
	//vector<int> tmp;
	//for (int i = 0; i < n; i++)
	//	tmp.push_back(i);
	//for (int i = n-1; i >= 0; i--)
	//{
	//	if (graph[tmp[i]].size() == 0)
	//	{
	//		q.push_back(tmp[i]);
	//		id[tmp[i]] = 1;
	//		tmp.erase(tmp.begin() + i);
	//		break;
	//	}
	//}
	//if (tmp.size() == n)
	//	return q;

	//while (tmp.size())
	//{
	//	int s = tmp.size();
	//	for (int i = s - 1; i >= 0; i--)
	//	{
	//		int l = graph[tmp[i]].size();
	//		bool flag = 1;
	//		for (auto i : graph[tmp[i]]) {
	//			if (id[i] != 1) {
	//				flag = 0;
	//				break;
	//			}
	//		}
	//		if (flag == 1)
	//		{
	//			q.push_back(tmp[i]);
	//			id[tmp[i]] = 1;
	//			tmp.erase(tmp.begin() + i);
	//			break;
	//		}
	//	}
	//	if (s == tmp.size()) {
	//		q.clear();
	//		return q;
	//	}
	//
	//}
	//while (q.size())
	//{
	//	tmp.push_back(q.back());
	//	q.pop_back();
	//}
	//return tmp;
	int size = graph.size();
	vector<int> visited(size);
	vector<int> result;
	vector<int> e;
	queue<int> q;
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		for (auto j : graph[i])
		{
			visited[j]++;
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (visited[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		result.push_back(x);
		for (auto k : graph[x])
		{
			visited[k]--;
			if (visited[k] == 0)
			{
				q.push(k);
			}
		}
		count++;
	}
	if (count != size) return e;
	return result;
}
int main()
{
	/*int n = 6;
	int G[6][6] = { {0, 1, 0, 1, 0, 0},
					{0, 0, 1, 1, 0, 0},
					{0, 0, 0, 1, 1, 1},
					{0, 0, 0, 0, 1, 1},
					{0, 0, 0, 0, 0, 1},
					{0, 1, 0, 0, 0, 0} };
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (G[i][j] == 1) graph[i].push_back(j);
		}
	}

	vector<int> res = topologicalSorting(graph);
	if (res.empty()) printf("-1");
	else {
		for (int e : res) printf("%d ", e);
	}*/
	/*int n = 6;
	int G[6][6] = { {0, 1, 0, 1, 0, 0},
						{0, 0, 1, 1, 0, 0},
						{0, 0, 0, 1, 1, 1},
						{0, 0, 0, 0, 1, 1},
						{0, 0, 0, 0, 0, 1},
						{0, 0, 0, 0, 0, 0} };
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (G[i][j] == 1) graph[i].push_back(j);
		}
	}*/

	//vector<int> res = topologicalSorting(graph);
	//if (res.empty()) printf("-1");
	//else {
	//	for (int e : res) printf("%d ", e);
	//}
	int n = 8;
	int G[8][8] = { {0, 1, 0, 0, 0, 0, 0, 0},
				   {0, 0, 1, 0, 0, 0, 0, 0},
				   {0, 0, 0, 1, 1, 0, 0, 0},
				   {0, 0, 0, 0, 1, 0, 0, 0},
				   {0, 0, 0, 0, 0, 0, 0, 0},
				   {0, 0, 0, 0, 0, 0, 1, 0},
				   {0, 0, 0, 0, 0, 0, 0, 0},
				   {1, 0, 0, 0, 0, 1, 0, 0} };
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (G[i][j] == 1)
				graph[i].push_back(j);
		}
	}

	vector<int> res = topologicalSorting(graph);
	if (res.empty())
		printf("-1");
	else
	{
		for (int e : res)
			printf("%d ", e);
	}
	/* int init_graph[10][10] = {{0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
	 						  {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
	 						  {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
	 						  {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	 						  {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
	 						  {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
	 						  {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
	 						  {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
	 						  {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	 						  {1, 0, 1, 0, 1, 0, 0, 0, 1, 0}};
	 int n = 10;
	 vector<vector<int>> graph(n, vector<int>());
	 for (int i = 0; i < n; ++i)
	 {
	 	for (int j = 0; j < n; ++j)
	 	{
	 		if (init_graph[i][j])
	 			graph[i].push_back(j);
	 	}
	 }

	bfs(graph, 0);*/
	// int G[6][6] = {{0, 1, 0, 0, 0, 1},
	// 			   {1, 0, 1, 0, 0, 0},
	// 			   {0, 1, 0, 1, 0, 0},
	// 			   {0, 0, 1, 0, 1, 0},
	// 			   {0, 0, 0, 1, 0, 1},
	// 			   {1, 0, 0, 0, 1, 0}};
	// int n = 6;

	// vector<vector<int>> graph(n, vector<int>());
	// for (int i = 0; i < n; ++i)
	// {
	// 	for (int j = 0; j < n; ++j)
	// 	{
	// 		if (G[i][j])
	// 			graph[i].push_back(j);
	// 	}
	// }

	// isBipartite(graph) ? cout << "Yes" : cout << "No";
}