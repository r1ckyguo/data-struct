#pragma once
#include <iostream>
#include <cassert>

using namespace std;
// 求连通分量
template <typename Graph>
class Component {
private:
	Graph& G;	// 图
	bool* visited;		// 表示节点有没有被访问过
	int ccount;		// 连通分量个数
	int* id;		// 连通分量的分组id，可以判断两个节点是不是在同一个连通分量中

	// 深度优先遍历
	void dfs(int v) {
		visited[v] = true;	// 访问当前节点v
		id[v] = ccount;		// 当前连通分量分组编号
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next()) {
			if (!visited[i]) {	// 如果节点i没有被访问，则对i进行dfs
				dfs(i);
			}
		}
		return;
	}

public:
	Component(Graph& graph) :G(graph) {
		visited = new bool[G.V()];
		ccount = 0;
		id = new int[G.V()];
		for (int i = 0; i < G.V(); i++) {
			visited[i] = false;
			id[i] = -1;
		}
		
		// 计算连通分量
		for (int i = 0; i < G.V(); i++) {
			if (!visited[i]) {
				dfs(i);
				ccount++;
			}
		}
	}

	~Component() {
		delete[]visited;
		delete[]id;
	}
	// 返回连通分量个数
	int count() {
		return ccount;
	}
	// 判断两个连通分量是否连通
	bool isConnected(int v, int w) {
		assert(v >= 0 && v < G.V());
		assert(w >= 0 && w < G.V());
		return id[v] == id[w];
	}
};