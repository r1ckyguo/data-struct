#pragma once
#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
// 层序遍历以及寻找无权图的最短路径
template <typename Graph>
class ShortestPath{
private:
	Graph& graph;
	int s;
	bool* visited;
	int* from;
	int* ord;		// 节点s到节点i的距离
	// 层序遍历
	void bfs() {
		queue<int> q;	// 层序访问队列
		q.push(s);
		visited[s] = true;
		ord[s] = 0;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			typename Graph::adjIterator adj(graph, v);
			for (int i = adj.begin(); !adj.end(); i = adj.next()) {
				if (!visited[i]) {
					q.push(i);
					visited[i] = true;
					from[i] = v;		// 记录上一个位置
					// 无向图最短路径算法，计算距离
					ord[i] = ord[v] + 1;
				}
			}
		}
		return;
	}
public:
	ShortestPath(Graph &graph, int s):graph(graph) {
		// 算法初始化
		assert(s >= 0 && s < graph.V());

		visited = new bool[graph.V()];
		from = new int[graph.V()];
		ord = new int[graph.V()];
		this->s = s;
		
		for (int i = 0; i < graph.V(); i++) {
			visited[i] = false;
			from[i] = -1;
			ord[i] = -1;
		}
		// 层序遍历
		bfs();
	}
	~ShortestPath() {
		delete[]visited;
		delete[]from;
		delete[]ord;
	}
	bool hasPath(int w) {
		assert(w >= 0 && w < graph.V());
		return visited[w];
	}
	// 求路径
	void path(int w, vector<int>& vec) {
		stack<int> sta;
		int p = w;
		// 从w往前找s
		while (p != -1) {
			sta.push(p);
			p = from[p];
		}
		vec.clear();
		// sta弹出，插入vector中
		while (!sta.empty()) {
			vec.push_back(sta.top());
			sta.pop();
		}
		return;
	}
	// 展示路径
	void showPath(int w) {
		vector<int> vec;
		path(w, vec);
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i];
			if (i == vec.size() - 1) {
				cout << endl;
			}
			else
				cout << "->";
		}
	}
	int length(int w) {
		assert(w >= 0 && w < graph.V());
		return ord[w];
	}
};