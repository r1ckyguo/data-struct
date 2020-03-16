#pragma once

#include <iostream>
#include <cassert>

using namespace std;
// ���鼯
// �������Ԫ���Ƿ���ͬһ��������
namespace UF5 {
	// Quick Union
	// ����rank�������Ż�, �Լ�·��ѹ��
	class UnionFind {
	private:
		// parentΪԪ�ؼ��ϵĸ����������ͬ�ĸ�������ͬһ������
		int* parent;
		int count;
		int* rank;		// rank[i]��ʾ��iΪ���ļ��ϲ���
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
		// ��ѯp,qԪ���Ƿ���ͬһ��������
		bool isConnected(int p, int q) {
			return find(p) == find(q);
		}
		// ����Ԫ�ص���������
		int find(int p) {
			assert(p >= 0 && p < count);
			// path compression 1
			//while (p != parent[p]) {
			//	parent[p] = parent[parent[p]];	// �Ѹ��ڵ����үү�ڵ�
			//	p = parent[p];
			//}

			// path compression2
			if (p != parent[p]) {
				parent[p] = find(parent[p]);		// ֱ���������Ƚڵ�
				return parent[p];
			}
			return p;
		}
		// ������Ԫ��
		// ��ʱ��union�ǳ���
		// �ںϲ�ʱ��Ҫ�ο�rank
		void unionElement(int p, int q) {
			// ��p,qԪ�ص�root
			int pRoot = find(p);
			int qRoot = find(q);
			// ���pqԪ����ͬһ��������
			if (pRoot == qRoot) {
				return;
			}
			// ��Ԫ��rank�͵ļ��Ϻϲ���rank�ߵļ�������
			// ��ֹһ�����ϲ���̫��
			if (rank[pRoot] < rank[qRoot]) {
				// ��ʱ����������
				parent[pRoot] = qRoot;
			}
			else if (rank[qRoot] < rank[pRoot]) {
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