#pragma once
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
// ϡ��ͼ - �ڽӱ�
class SparseGraph {
private:
	int n, m;	// �ڵ�����ͱ߸���
	bool directed;	// �Ƿ�������ͼ
	vector<vector<int>> g;	// �ڽӱ�
public:
	SparseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0;
		this->directed = directed;
		for (int i = 0; i < n; i++) {
			g.push_back(vector<int>());
		}
	}
	~SparseGraph() {

	}
	// ����ͼ�ڵ����
	int V() {
		return n;
	}
	// ����ͼ������
	int E() {
		return m;
	}
	bool hasEdge(int v, int w) {
		// ��֤��Խ��
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		for (int i = 0; i < g[v].size(); i++) {
			if (g[v][i] == w) {
				return true;
			}
		}
		return false;
	}
	void addEdge(int v, int w) {
		// ��֤��Խ��
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		if (hasEdge(v, w)) {
			return;
		}
		g[v].push_back(w);
		if (v != w && !directed) {	
			// ���v��w����ͬ�ڵ㣬�ǾͲ��ټ���
			// ����ͼ��w->v�ı�ҲҪ����
			g[w].push_back(v);
		}
		m++;
	}
	// ����ͼ��չʾ
	void show() {
		for (int i = 0; i < n; i++) {
			cout << "vertex" << i << ":\t";
			for (int j = 0; j < g[i].size(); j++) {
				cout << g[i][j] << "\t";
			}
			cout << endl;
		}
		return;
	}

	// ϡ��ͼ������
	// ��Ϊgraph��private�ģ��޷����ʡ�ֻ���Լ��������������е���
	class adjIterator {
	private:
		SparseGraph& G;
		int v;	// ��ǰ�����Ľڵ�v
		int index;	// ����
	public:
		adjIterator(SparseGraph& graph, int v) :G(graph) {
			this->v = v;
			this->index = 0;	// ��ʱ��ʼ����Ϊ0
		}
		// ��������ʼ
		int begin() {
			index = 0;
			if (G.g[v].size()) {	// �����ǰ�ڵ�v���ڽӱ�
				return G.g[v][index];	// ���ص�һ��Ԫ��
			}
			return -1;
		}
		// ����������
		int next() {
			index++;
			if (index < G.g[v].size()) {
				return G.g[v][index];
			}
			return -1;
		}

		// �������ս�
		bool end() {
			// ����������ͼ�Ľڵ�ʱ���ս�
			return index >= G.g[v].size();
		}
	};
};