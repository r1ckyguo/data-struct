#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
#include "Heap/MinHeap.h"
using namespace std;

template <typename Graph, typename Weight>
class LazyPrimMST {
// lazy Prim：从某个节点开始访问，加入其领接边到最小堆，取出最小边加入mst集合
// 然后重复其操作，直至所有节点都被访问过
// 时间复杂度o(ElogE)
private:
	Graph& G;
	MinHeap<Edge<Weight>> heap;			// 最小堆排序边，堆顶是最小的边
	bool* marked;						// 标记节点是否选进最小边
	vector<Edge<Weight>> mst;			// 存最小边集合
	Weight mstWeight;					// 记录最小边的权值

	// 遍历v节点访问，把与v相接点的边都加入最小堆
	void visit(int v) {
		assert(!marked[v]);
		marked[v] = true;
		// 开始遍历邻接边
		typename Graph::adjIterator adj(G, v);
		for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()) {
			if (!marked[e->other(v)]) {
				heap.insert(*e);
			}
		}
	}
public:
	LazyPrimMST(Graph &graph):G(graph), heap(MinHeap<Edge<Weight>>(graph.E())) {
		// 初始化
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); ++i) {
			marked[i] = false;
		}
		mst.clear();
		// Lazy Prim开始
		visit(0);	// 从0开始访问，将与0相接点的边都需要加入最小堆中进行排序
		while (!heap.isEmpty()) {
			Edge<Weight> e = heap.extractMin();
			if (marked[e.v()] == marked[e.w()]) {
				// 如果不是切边(即已经加入)，则不加入
				// false相同：基本没有，true相同：即两个点已经加入
				continue;
			}
			// 把最小边e推入mst
			mst.push_back(e);
			if (!marked[e.v()]) {	//如果节点a没有加入，则从a开始访问
				visit(e.v());
			}
			else {
				// 否则访问b
				visit(e.w());
			}
		}
		// 计算mstWeight
		mstWeight = mst[0].wt();
		for (int i = 1; i < mst.size(); ++i) {
			mstWeight += mst[i].wt();
		}
	}
	~LazyPrimMST() {
		delete[]marked;
	}
	// 返回最小边集合
	vector<Edge<Weight>> mstEdge() {
		return mst;
	}
	// 返回最小权值
	Weight result() {
		return mstWeight;
	}
};