#pragma once

#include <iostream>
#include <cassert>

using namespace std;
// 并查集
// 检查两个元素是否在同一个集合内
namespace UF4 {
	// Quick Union
	// 基于rank层数的优化
	class UnionFind {
	private:
		// parent为元素集合的根，如果有相同的根，则是同一个集合
		int* parent;
		int count;
		int* rank;		// rank[i]表示以i为根的集合层数
	public:
		UnionFind(int n) {
			parent = new int[n];
			rank = new int[n];
			count = n;
			for (int i = 0; i < n; ++i) {
				parent[i] = i;
				rank[i] = 1;
			}
		}
		~UnionFind() {
			delete[]parent;
			delete[]rank;
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
		// 在合并时需要参考rank
		void unionElement(int p, int q) {
			// 找p,q元素的root
			int pRoot = find(p);
			int qRoot = find(q);
			// 如果pq元素在同一个集合中
			if (pRoot == qRoot) {
				return;
			}
			// 将元素rank低的集合合并到rank高的集合里面
			// 防止一个集合层数太高
			if (rank[pRoot] < rank[qRoot]) {
				// 此时层数不增加
				parent[pRoot] = qRoot;
			}
			else if(rank[qRoot] < rank[pRoot]) {
				parent[qRoot] = pRoot;
			}
			else {
				// rank[pRoot] == rank[qRoot]
				parent[pRoot] = qRoot;
				rank[qRoot] += 1;
			}
			return;
		}
	};
}