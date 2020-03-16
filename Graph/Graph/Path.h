#pragma once
#include <iostream>
#include <cassert>
#include <stack>
#include <vector>

using namespace std;

// 寻找两个节点的路径
template <typename Graph>
class Path {
private:
	Graph& G;
	int s;	// 起始节点
	bool* visited;
	int* from;	// 记录上一个节点

	void dfs(int v) {
		visited[v] = true;
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next()) {
			if (!visited[i]) {
				from[i] = v;		// i节点的前一个节点是v
				dfs(i);
			}
		}
		return;
	}

public:
	Path(Graph& graph, int s) :G(graph) {
		// 算法初始化
		assert(s >= 0 && s <= G.V());
		visited = new bool[G.V()];
		from = new int[G.V()];
		for (int i = 0; i < G.V(); i++) {
			visited[i] = false;
			from[i] = -1;
		}
		this->s = s;
		
		// 求s开始的dfs
		dfs(s);
	}
	~Path() {
		delete[]visited;
		delete[]from;
	}
	// 判断节点s,w之间有没有路径
	bool hasPath(int w) {
		assert(w >= 0 && w <= G.V());
		return visited[w];
	}
	// 求路径
	void path(int w, vector<int> &vec) {
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
};