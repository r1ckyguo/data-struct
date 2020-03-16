#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;
// 稀疏图 - 邻接表
template <typename Weight>
class SparseGraph {
private:
	int n, m;	// 节点个数和边个数
	bool directed;	// 是否是有向图
	vector<vector<Edge<Weight> *>> g;	// 邻接表
public:
	SparseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0;
		this->directed = directed;
		for (int i = 0; i < n; i++) {
			g.push_back(vector<Edge<Weight> *>());
		}
	}
	~SparseGraph() {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < g[i].size(); ++j) {
				delete g[i][j];
			}
		}
	}

	// 返回图节点个数
	int V() {
		return n;
	}
	// 返回图边条数
	int E() {
		return m;
	}
	bool hasEdge(int v, int w) {
		// 保证不越界
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		for (int i = 0; i < g[v].size(); i++) {
			if (g[v][i]->other(v) == w) {
				return true;
			}
		}
		return false;
	}
	void addEdge(int v, int w, Weight weight) {
		// 保证不越界
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		if (hasEdge(v, w)) {
			// 如果有边的话，那么覆盖
			delete g[v][w];
			if (!directed) {
				delete g[w][v];
			}
			--m;
		}
		g[v].push_back(new Edge<Weight>(v, w, weight));
		if (v != w && !directed) {	
			// 如果v和w是相同节点，那就不再加入
			// 无向图则w->v的边也要加入
			g[w].push_back(new Edge<Weight>(w, v, weight));
		}
		m++;
	}
	// 遍历图，展示
	void show() {
		for (int i = 0; i < n; i++) {
			cout << "vertex" << i << ":\t";
			for (int j = 0; j < g[i].size(); j++) {
				cout << "(to:" << g[i][j]->w() << ",wt:" << g[i][j]->wt() << ")\t";
			}
			cout << endl;
		}
		return;
	}

	// 稀疏图迭代器
	// 因为graph是private的，无法访问。只能自己创建迭代器进行迭代
	class adjIterator {
	private:
		SparseGraph& G;
		int v;	// 当前遍历的节点v
		int index;	// 索引
	public:
		adjIterator(SparseGraph& graph, int v) :G(graph) {
			this->v = v;
			this->index = 0;	// 此时初始索引为0
		}
		// 迭代器初始
		Edge<Weight>* begin() {
			index = 0;
			if (G.g[v].size()) {	// 如果当前节点v有邻接边
				return G.g[v][index];	// 返回第一个元素
			}
			return NULL;
		}
		// 迭代器往后
		Edge<Weight>* next() {
			index++;
			if (index < G.g[v].size()) {
				return G.g[v][index];
			}
			return NULL;
		}

		// 迭代器终结
		bool end() {
			// 当索引大于图的节点时就终结
			return index >= G.g[v].size();
		}
	};
};