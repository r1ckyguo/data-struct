#pragma once
#pragma once
#include <iostream>
#include <cassert>

using namespace std;
// 并查集
// 检查两个元素是否在同一个集合内
namespace UF2 {
	// Quick Union
	class UnionFind {
	private:
		// parent为元素集合的根，如果有相同的根，则是同一个集合
		int* parent;
		int count;

	public:
		UnionFind(int n) {
			parent = new int[n];
			count = n;
			for (int i = 0; i < n; ++i) {
				parent[i] = i;
			}
		}
		~UnionFind() {
			delete[]parent;
		}
		// 查询p,q元素是否在同一个集合中
		bool isConnected(int p, int q) {
			return find(p) == find(q);
		}
		// 查找元素的所属集合
		int find(int p) {
			assert(p >= 0 && p < count);
			while (p != parent[p]) {
				p = parent[p];
			}
			return p;
		}
		// 并两个元素
		// 这时的union非常快
		void unionElement(int p, int q) {
			// 找p,q元素的root
			int pRoot = find(p);
			int qRoot = find(q);
			// 如果pq元素在同一个集合中
			if (pRoot == qRoot) {
				return;
			}
			parent[pRoot] = qRoot;
		}
	};
}