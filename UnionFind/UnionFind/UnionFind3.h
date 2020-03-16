#pragma once

#include <iostream>
#include <cassert>

using namespace std;
// ���鼯
// �������Ԫ���Ƿ���ͬһ��������
namespace UF3 {
	// Quick Union
	// ����size���Ż�
	class UnionFind {
	private:
		// parentΪԪ�ؼ��ϵĸ����������ͬ�ĸ�������ͬһ������
		int* parent;
		int count;
		int* sz;		// sz[i]��ʾ��iΪ���ļ�����Ԫ�ظ���
	public:
		UnionFind(int n) {
			parent = new int[n];
			sz = new int[n];
			count = n;
			for (int i = 0; i < n; ++i) {
				parent[i] = i;
				sz[i] = 1;
			}
		}
		~UnionFind() {
			delete[]parent;
			delete[]sz;
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
		// �ںϲ�ʱ��Ҫ�ο�size
		void unionElement(int p, int q) {
			// ��p,qԪ�ص�root
			int pRoot = find(p);
			int qRoot = find(q);
			// ���pqԪ����ͬһ��������
			if (pRoot == qRoot) {
				return;
			}
			// ��Ԫ���ٵļ��Ϻϲ���Ԫ�ض�ļ�������
			// ��ֹһ�����ϲ���̫��
			if (sz[pRoot] < sz[qRoot]) {
				parent[pRoot] = qRoot;
				sz[qRoot] += sz[pRoot];
			}
			else {
				parent[qRoot] = pRoot;
				sz[pRoot] += sz[qRoot];
			}
		}
	};
}