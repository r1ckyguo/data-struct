#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
using namespace std;
// ����ͼ - �ڽӾ���
template <typename Weight>
class DenseGraph {
private:
	int n, m;	// �ڵ�����ͱ߸���
	bool directed;	// �Ƿ�������ͼ
	vector<vector<Edge<Weight> *>> g;	// �ڽӾ���������edge��ָ��

public:
	DenseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0;
		this->directed = directed;
		for (int i = 0; i < n; i++) {
			g.push_back(vector<Edge<Weight>*>(n, NULL));	// ����n��edge����ʼ��Ϊ��
		}
	}

	~DenseGraph() {
		// ����ͼ
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (g[i][j] != NULL) {
					delete g[i][j];
				}
			}
		}
	}
	// ����ͼ�ڵ����
	int V() {
		return n;
	}
	// ����ͼ������
	int E() {
		return m;
	}
	// �ж�ͼ��v��w�����Ƿ��б�����
	bool hasEdge(int v, int w) {
		// ��֤��Խ��
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		return g[v][w] != NULL;
	}
	// ��ͼ����ӱ�
	void addEdge(int v, int w, Weight weight) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		if (hasEdge(v, w)) {	// ���ж��Ƿ��б�
			// ����бߵĻ����Ѹ���Ϊ�µ�Ȩֵ
			delete g[v][w];
			if (!directed) {
				delete g[w][v];
			}
			m--;
		}

		g[v][w] = new Edge<Weight>(v, w, weight);
		if (!directed) {	// ����ͼ
			g[w][v] = new Edge<Weight>(w, v, weight);
		}
		m++;
	}
	// ����ͼ��չʾ
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

	// ����ͼ������
	// ��Ϊgraph��private�ģ��޷����ʡ�ֻ���Լ��������������е���
	class adjIterator {
	private:
		DenseGraph& G;
		int v;	// ��ǰ�����Ľڵ�v
		int index;	// ����
	public:
		adjIterator(DenseGraph& graph, int v) :G(graph) {
			this->v = v;
			this->index = -1;	// �����Ǵ�0��ʼ���㣬������ʼ����Ϊ-1
		}
		// ��������ʼ
		Edge<Weight> * begin() {
			index = -1;	
			return next();	// ��������һ��
		}
		// ����������
		Edge<Weight> * next() {
			for (index += 1; index < G.V(); index++) {
				if (G.g[v][index]) {
					return G.g[v][index];
				}
			}
			return NULL;
		}
		// �������ս�
		bool end() {
			// ����������ͼ�Ľڵ�ʱ���ս�
			return index >= G.V();		
		}
	};
};

