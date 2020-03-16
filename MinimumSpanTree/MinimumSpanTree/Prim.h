#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
#include "Heap/IndexMinHeap.h"

using namespace std;
template <typename Graph, typename Weight>
class PrimMST {
	// o(ElogV)
private:
	Graph& G;
	vector<Edge<Weight>> mst;
	bool* marked;
	Weight mstWeight;
	IndexMinHeap<Weight> idxheap;
	vector<Edge<Weight>*>edgeTo;		// 与节点w相接的最短横切边

	void visit(int v) {
		assert(!marked[v]);
		marked[v] = true;
		
		typename Graph::adjIterator adj(G, v);
		for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()) {
			int w = e->other(v);		// w是与v相连的邻节点
			if (!marked[w]) {	// 如果已经把w节点加入，则退出
				if (!edgeTo[w]) {	// 如果edgeTo中与w节点没有相连的边，则加入
					edgeTo[w] = e;
					idxheap.insert(w, e->wt());
				}
				// 如果此时与w相连的边e权值小于edgeTo中w的边权值，则更新
				else if (e->wt() < edgeTo[w]->wt()) {
					edgeTo[w] = e;
					idxheap.change(w, e->wt());
				}
			}
		}
	}
	
public:
	PrimMST(Graph& graph) :G(graph), idxheap(IndexMinHeap<double>(graph.V())) {
		assert(graph.E() >= 1);
		// 初始化
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); ++i) {
			marked[i] = false;
			edgeTo.push_back(NULL);
		}
		mst.clear();

		// Prim算法
		visit(0);
		while (!idxheap.isEmpty()) {
			int v = idxheap.extractMinIndex();	// 找出最小边的索引
			assert(graph.E() >=1);	//	确保有边
			mst.push_back(*edgeTo[v]);	// 此时v是最小边的邻接点，这条边是最小边，推入mst中
			visit(v);	// 从v继续找
		}

		// 计算权值
		mstWeight = mst[0].wt();
		for (int i = 1; i < mst.size(); ++i) {
			mstWeight += mst[i].wt();
		}
	}
	~PrimMST() {
		delete[]marked;
	}
	// 返回mst最小边集合
	vector<Edge<Weight>> mstEdge() {
		return mst;
	}
	// 返回最小边权值
	Weight result() {
		return mstWeight;
	}
};
