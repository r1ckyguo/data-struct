#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "Edge.h"
#include "Heap/IndexMinHeap.h"

using namespace std;

template <typename Graph, typename Weight>
class Dijkstra {
private:
	Graph& G;
	int s;
	Weight* dist;
	bool* marked;
	vector<Edge<Weight>*> from;

public:
	Dijkstra(Graph& graph, int s) :G(graph) {
		this->s = s;
		dist = new Weight[G.V()];
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); ++i) {
			dist[i] = Weight();
			marked[i] = false;
			from.push_back(NULL);
		}

		IndexMinHeap<Weight> idxheap(G.V());

		// start dijkstra
		dist[s] = Weight();
		idxheap.insert(s, dist[s]);
		marked[s] = true;
		while (!idxheap.isEmpty()) {
			int v = idxheap.extractMinIndex();

			marked[v] = true;
			typename Graph::adjIterator adj(G, v);
			for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()) {
				int w = e->other(v);
				if (!marked[w]) {
					if (from[w] == NULL || dist[v] + e->wt() < dist[w]) {
						dist[w] = dist[v] + e->wt();
						from[w] = e;
						if (idxheap.contain(w)) {	//?
							idxheap.change(w, dist[w]);
						}
						else {
							idxheap.insert(w, dist[w]);
						}
					}
				}
			}
		}
	}

	~Dijkstra() {
		delete[]dist;
		delete[]marked;
	}
	// s->w的最短距离
	Weight shortestPathTo(int w) {
		assert(w >= 0 && w < G.V());
		return dist[w];
	}
	// s->w是否有路
	bool hasPathTo(int w) {
		assert(w >= 0 && w < G.V());
		return marked[w];
	}
	// 获取s->w的最短距离vec
	void shortestPath(int w, vector<Edge<Weight>>& vec) {
		assert(w >= 0 && w < G.V());
		stack<Edge<Weight>*> s;
		Edge<Weight>* e = from[w];
		while (e->v() != this->s) {
			s.push(e);
			e = from[e->v()];		//
		}
		s.push(e);
		while (!s.empty()) {
			e = s.top();
			vec.push_back(*e);
			s.pop();
		}
	}
	// 展示路径
	void showPath(int w) {
		assert(w >= 0 && w < G.V());
		vector<Edge<Weight>> vec;
		shortestPath(w, vec);
		for (int i = 0; i < vec.size(); ++i) {
			cout << vec[i].v() << " -> ";
			if (i == vec.size() - 1) {
				cout << vec[i].w() << endl;
			}
		}
		return;
	}
};