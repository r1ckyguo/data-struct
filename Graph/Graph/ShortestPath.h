#pragma once
#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
// ��������Լ�Ѱ����Ȩͼ�����·��
template <typename Graph>
class ShortestPath{
private:
	Graph& graph;
	int s;
	bool* visited;
	int* from;
	int* ord;		// �ڵ�s���ڵ�i�ľ���
	// �������
	void bfs() {
		queue<int> q;	// ������ʶ���
		q.push(s);
		visited[s] = true;
		ord[s] = 0;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			typename Graph::adjIterator adj(graph, v);
			for (int i = adj.begin(); !adj.end(); i = adj.next()) {
				if (!visited[i]) {
					q.push(i);
					visited[i] = true;
					from[i] = v;		// ��¼��һ��λ��
					// ����ͼ���·���㷨���������
					ord[i] = ord[v] + 1;
				}
			}
		}
		return;
	}
public:
	ShortestPath(Graph &graph, int s):graph(graph) {
		// �㷨��ʼ��
		assert(s >= 0 && s < graph.V());

		visited = new bool[graph.V()];
		from = new int[graph.V()];
		ord = new int[graph.V()];
		this->s = s;
		
		for (int i = 0; i < graph.V(); i++) {
			visited[i] = false;
			from[i] = -1;
			ord[i] = -1;
		}
		// �������
		bfs();
	}
	~ShortestPath() {
		delete[]visited;
		delete[]from;
		delete[]ord;
	}
	bool hasPath(int w) {
		assert(w >= 0 && w < graph.V());
		return visited[w];
	}
	// ��·��
	void path(int w, vector<int>& vec) {
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
	int length(int w) {
		assert(w >= 0 && w < graph.V());
		return ord[w];
	}
};