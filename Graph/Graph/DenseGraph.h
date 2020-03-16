#pragma once
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
// ����ͼ - �ڽӾ���
class DenseGraph {
private:
	int n, m;	// �ڵ�����ͱ߸���
	bool directed;	// �Ƿ�������ͼ
	vector<vector<bool>> g;	// �ڽӾ���

public:
	DenseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0;
		this->directed = directed;
		for (int i = 0; i < n; i++) {
			g.push_back(vector<bool>(n, false));
		}
	}

	~DenseGraph() {

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
		return g[v][w];
	}
	// ��ͼ����ӱ�
	void addEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		if (hasEdge(v, w)) {	// ���ж��Ƿ��б�
			return;
		}
		g[v][w] = true;
		if (!directed) {	// ����ͼ
			g[w][v] = true;
		}
		m++;
	}
	// ����ͼ��չʾ
	void show() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << g[i][j] << "\t";
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
		int begin() {
			index = -1;	
			return next();	// ��������һ��
		}
		// ����������
		int next() {
			for (index += 1; index < G.V(); index++) {
				if (G.g[v][index]) {
					return index;
				}
			}
			return -1;
		}
		// �������ս�
		bool end() {
			// ����������ͼ�Ľڵ�ʱ���ս�
			return index >= G.V();		
		}
	};
};

