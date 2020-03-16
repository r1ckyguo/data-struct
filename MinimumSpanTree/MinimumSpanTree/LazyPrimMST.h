#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
#include "Heap/MinHeap.h"
using namespace std;

template <typename Graph, typename Weight>
class LazyPrimMST {
// lazy Prim����ĳ���ڵ㿪ʼ���ʣ���������ӱߵ���С�ѣ�ȡ����С�߼���mst����
// Ȼ���ظ��������ֱ�����нڵ㶼�����ʹ�
// ʱ�临�Ӷ�o(ElogE)
private:
	Graph& G;
	MinHeap<Edge<Weight>> heap;			// ��С������ߣ��Ѷ�����С�ı�
	bool* marked;						// ��ǽڵ��Ƿ�ѡ����С��
	vector<Edge<Weight>> mst;			// ����С�߼���
	Weight mstWeight;					// ��¼��С�ߵ�Ȩֵ

	// ����v�ڵ���ʣ�����v��ӵ�ı߶�������С��
	void visit(int v) {
		assert(!marked[v]);
		marked[v] = true;
		// ��ʼ�����ڽӱ�
		typename Graph::adjIterator adj(G, v);
		for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()) {
			if (!marked[e->other(v)]) {
				heap.insert(*e);
			}
		}
	}
public:
	LazyPrimMST(Graph &graph):G(graph), heap(MinHeap<Edge<Weight>>(graph.E())) {
		// ��ʼ��
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); ++i) {
			marked[i] = false;
		}
		mst.clear();
		// Lazy Prim��ʼ
		visit(0);	// ��0��ʼ���ʣ�����0��ӵ�ı߶���Ҫ������С���н�������
		while (!heap.isEmpty()) {
			Edge<Weight> e = heap.extractMin();
			if (marked[e.v()] == marked[e.w()]) {
				// ��������б�(���Ѿ�����)���򲻼���
				// false��ͬ������û�У�true��ͬ�����������Ѿ�����
				continue;
			}
			// ����С��e����mst
			mst.push_back(e);
			if (!marked[e.v()]) {	//����ڵ�aû�м��룬���a��ʼ����
				visit(e.v());
			}
			else {
				// �������b
				visit(e.w());
			}
		}
		// ����mstWeight
		mstWeight = mst[0].wt();
		for (int i = 1; i < mst.size(); ++i) {
			mstWeight += mst[i].wt();
		}
	}
	~LazyPrimMST() {
		delete[]marked;
	}
	// ������С�߼���
	vector<Edge<Weight>> mstEdge() {
		return mst;
	}
	// ������СȨֵ
	Weight result() {
		return mstWeight;
	}
};