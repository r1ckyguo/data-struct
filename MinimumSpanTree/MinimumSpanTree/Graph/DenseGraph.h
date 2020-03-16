#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
using namespace std;
// 稠密图 - 邻接矩阵
template <typename Weight>
class DenseGraph {
private:
	int n, m;	// 节点个数和边个数
	bool directed;	// 是否是有向图
	vector<vector<Edge<Weight> *>> g;	// 邻接矩阵，里面是edge的指针

public:
	DenseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0;
		this->directed = directed;
		for (int i = 0; i < n; i++) {
			g.push_back(vector<Edge<Weight>*>(n, NULL));	// 推入n个edge，初始化为空
		}
	}

	~DenseGraph() {
		// 销毁图
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (g[i][j] != NULL) {
					delete g[i][j];
				}
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
	// 判断图中v和w两点是否有边相连
	bool hasEdge(int v, int w) {
		// 保证不越界
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		return g[v][w] != NULL;
	}
	// 往图中添加边
	void addEdge(int v, int w, Weight weight) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		if (hasEdge(v, w)) {	// 先判断是否有边
			// 如果有边的话，把覆盖为新的权值
			delete g[v][w];
			if (!directed) {
				delete g[w][v];
			}
			m--;
		}

		g[v][w] = new Edge<Weight>(v, w, weight);
		if (!directed) {	// 无向图
			g[w][v] = new Edge<Weight>(w, v, weight);
		}
		m++;
	}
	// 遍历图，展示
	void show() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][j]) {
					cout << g[i][j]->wt() << "\t";
				}
				else {
					cout << "NULL\t";
				}
			}
			cout << endl;
		}
		return;
	}

	// 稠密图迭代器
	// 因为graph是private的，无法访问。只能自己创建迭代器进行迭代
	class adjIterator {
	private:
		DenseGraph& G;
		int v;	// 当前遍历的节点v
		int index;	// 索引
	public:
		adjIterator(DenseGraph& graph, int v) :G(graph) {
			this->v = v;
			this->index = -1;	// 数组是从0开始计算，所以起始索引为-1
		}
		// 迭代器初始
		Edge<Weight> * begin() {
			index = -1;	
			return next();	// 迭代器下一个
		}
		// 迭代器往后
		Edge<Weight> * next() {
			for (index += 1; index < G.V(); index++) {
				if (G.g[v][index]) {
					return G.g[v][index];
				}
			}
			return NULL;
		}
		// 迭代器终结
		bool end() {
			// 当索引大于图的节点时就终结
			return index >= G.V();		
		}
	};
};

