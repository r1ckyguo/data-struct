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
	vector<Edge<Weight>*>edgeTo;		// ��ڵ�w��ӵ���̺��б�

	void visit(int v) {
		assert(!marked[v]);
		marked[v] = true;
		
		typename Graph::adjIterator adj(G, v);
		for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()) {
			int w = e->other(v);		// w����v�������ڽڵ�
			if (!marked[w]) {	// ����Ѿ���w�ڵ���룬���˳�
				if (!edgeTo[w]) {	// ���edgeTo����w�ڵ�û�������ıߣ������
					edgeTo[w] = e;
					idxheap.insert(w, e->wt());
				}
				// �����ʱ��w�����ı�eȨֵС��edgeTo��w�ı�Ȩֵ�������
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
		// ��ʼ��
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); ++i) {
			marked[i] = false;
			edgeTo.push_back(NULL);
		}
		mst.clear();

		// Prim�㷨
		visit(0);
		while (!idxheap.isEmpty()) {
			int v = idxheap.extractMinIndex();	// �ҳ���С�ߵ�����
			assert(graph.E() >=1);	//	ȷ���б�
			mst.push_back(*edgeTo[v]);	// ��ʱv����С�ߵ��ڽӵ㣬����������С�ߣ�����mst��
			visit(v);	// ��v������
		}

		// ����Ȩֵ
		mstWeight = mst[0].wt();
		for (int i = 1; i < mst.size(); ++i) {
			mstWeight += mst[i].wt();
		}
	}
	~PrimMST() {
		delete[]marked;
	}
	// ����mst��С�߼���
	vector<Edge<Weight>> mstEdge() {
		return mst;
	}
	// ������С��Ȩֵ
	Weight result() {
		return mstWeight;
	}
};
