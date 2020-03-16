#pragma once
#include <iostream>
#include <cassert>
#include <stack>
#include <vector>

using namespace std;

// Ѱ�������ڵ��·��
template <typename Graph>
class Path {
private:
	Graph& G;
	int s;	// ��ʼ�ڵ�
	bool* visited;
	int* from;	// ��¼��һ���ڵ�

	void dfs(int v) {
		visited[v] = true;
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next()) {
			if (!visited[i]) {
				from[i] = v;		// i�ڵ��ǰһ���ڵ���v
				dfs(i);
			}
		}
		return;
	}

public:
	Path(Graph& graph, int s) :G(graph) {
		// �㷨��ʼ��
		assert(s >= 0 && s <= G.V());
		visited = new bool[G.V()];
		from = new int[G.V()];
		for (int i = 0; i < G.V(); i++) {
			visited[i] = false;
			from[i] = -1;
		}
		this->s = s;
		
		// ��s��ʼ��dfs
		dfs(s);
	}
	~Path() {
		delete[]visited;
		delete[]from;
	}
	// �жϽڵ�s,w֮����û��·��
	bool hasPath(int w) {
		assert(w >= 0 && w <= G.V());
		return visited[w];
	}
	// ��·��
	void path(int w, vector<int> &vec) {
		stack<int> sta;
		int p = w;
		// ��w��ǰ��s
		while (p != -1) {
			sta.push(p);
			p = from[p];
		}
		vec.clear();
		// sta����������vector��
		while (!sta.empty()) {
			vec.push_back(sta.top());
			sta.pop();
		}
		return;
	}
	// չʾ·��
	void showPath(int w) {
		vector<int> vec;
		path(w, vec);
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i];
			if (i == vec.size() - 1) {
				cout << endl;
			}
			else
				cout << "->";
		}
	}
};