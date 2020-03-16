#pragma once
#include <iostream>
#include <cassert>

using namespace std;
// ����ͨ����
template <typename Graph>
class Component {
private:
	Graph& G;	// ͼ
	bool* visited;		// ��ʾ�ڵ���û�б����ʹ�
	int ccount;		// ��ͨ��������
	int* id;		// ��ͨ�����ķ���id�������ж������ڵ��ǲ�����ͬһ����ͨ������

	// ������ȱ���
	void dfs(int v) {
		visited[v] = true;	// ���ʵ�ǰ�ڵ�v
		id[v] = ccount;		// ��ǰ��ͨ����������
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next()) {
			if (!visited[i]) {	// ����ڵ�iû�б����ʣ����i����dfs
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
		
		// ������ͨ����
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
	// ������ͨ��������
	int count() {
		return ccount;
	}
	// �ж�������ͨ�����Ƿ���ͨ
	bool isConnected(int v, int w) {
		assert(v >= 0 && v < G.V());
		assert(w >= 0 && w < G.V());
		return id[v] == id[w];
	}
};