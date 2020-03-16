#pragma once
#include <iostream>
#include <cassert>

using namespace std;
// 并查集
// 检查两个元素是否在同一个集合内
namespace UF1 {
	// Quick Find
	class UnionFind {
	private:
		// id表示集合号，只要在同一个集合里面则
		int* id;
		int count;

	public:
		UnionFind(int n) {
			id = new int[n];
			count = n;
			for (int i = 0; i < n; ++i) {
				id[i] = i;
			}
		}
		~UnionFind() {
			delete[]id;
		}
		// 查询p,q元素是否在同一个集合中
		bool isConnected(int p, int q) {
			return id[p] == id[q];
		}
		// 查找元素的所属集合
		// 这时的find非常快
		int find(int p) {
			assert(p >= 0 && p < count);
			return id[p];
		}
		// 并两个元素
		void unionElement(int p, int q) {
			// 找p,q元素的id
			int pID = find(p);
			int qID = find(q);
			// 如果pq元素在同一个集合中
			if (pID == qID) {
				return;
			}
			for (int i = 0; i < count; ++i) {
				// 找到p所属的集合，然后将其改为q所属集合
				if (id[i] == pID) {
					id[i] = qID;
				}
			}
		}
	};
}