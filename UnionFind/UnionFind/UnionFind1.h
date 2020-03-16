#pragma once
#include <iostream>
#include <cassert>

using namespace std;
// ���鼯
// �������Ԫ���Ƿ���ͬһ��������
namespace UF1 {
	// Quick Find
	class UnionFind {
	private:
		// id��ʾ���Ϻţ�ֻҪ��ͬһ������������
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
		// ��ѯp,qԪ���Ƿ���ͬһ��������
		bool isConnected(int p, int q) {
			return id[p] == id[q];
		}
		// ����Ԫ�ص���������
		// ��ʱ��find�ǳ���
		int find(int p) {
			assert(p >= 0 && p < count);
			return id[p];
		}
		// ������Ԫ��
		void unionElement(int p, int q) {
			// ��p,qԪ�ص�id
			int pID = find(p);
			int qID = find(q);
			// ���pqԪ����ͬһ��������
			if (pID == qID) {
				return;
			}
			for (int i = 0; i < count; ++i) {
				// �ҵ�p�����ļ��ϣ�Ȼ�����Ϊq��������
				if (id[i] == pID) {
					id[i] = qID;
				}
			}
		}
	};
}