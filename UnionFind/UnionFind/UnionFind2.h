#pragma once
#pragma once
#include <iostream>
#include <cassert>

using namespace std;
// ���鼯
// �������Ԫ���Ƿ���ͬһ��������
namespace UF2 {
	// Quick Union
	class UnionFind {
	private:
		// parentΪԪ�ؼ��ϵĸ����������ͬ�ĸ�������ͬһ������
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
		// ��ѯp,qԪ���Ƿ���ͬһ��������
		bool isConnected(int p, int q) {
			return find(p) == find(q);
		}
		// ����Ԫ�ص���������
		int find(int p) {
			assert(p >= 0 && p < count);
			while (p != parent[p]) {
				p = parent[p];
			}
			return p;
		}
		// ������Ԫ��
		// ��ʱ��union�ǳ���
		void unionElement(int p, int q) {
			// ��p,qԪ�ص�root
			int pRoot = find(p);
			int qRoot = find(q);
			// ���pqԪ����ͬһ��������
			if (pRoot == qRoot) {
				return;
			}
			parent[pRoot] = qRoot;
		}
	};
}