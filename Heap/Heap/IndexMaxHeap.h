#pragma once
#include <iostream>
#include <cassert>
using namespace std;

template<typename Item>
class IndexMaxHeap {
	// �������ѣ����������Ķѡ�
	// �����û���Ҫ�ı�ĳһ�����Ķ�
	// index[i]�Ǵ�ŵ�λ��,����˵index[1]�ŵ�һ��index[1]����������ǵ�һԪ���������ڵ�λ��
private:
	Item* data;		// ����
	int* index;		// ����
	int count;		// ���ݸ���
	int capacity;	// ����

	// ���ϵ���
	void shiftUp(int k) {
		// ԭ���Ƚ�data[k]��[k / 2]��������Ҫ�ж�data����index
		while (k > 1 && data[index[k / 2]] < data[index[k]]) {
			// ����ֻ����index
			swap(index[k / 2], index[k]);
			k /= 2;
		}
		return;
	}

	// ���µ���
	void shiftDown(int k) {
		while (2 * k <= count) {
			int j = 2 * k;		// j��k������
			if (j + 1 <= count && data[index[j]] < data[index[j + 1]]) {
				++j;
			}
			if (data[index[k]] >= data[index[j]]) {
				break;
			}
			swap(index[k], index[j]);
			k = j;
		}
		return;
	}

public:
	IndexMaxHeap(int capacity) {
		// �û������Ǵ�0��ʼ�����ģ����Ƕ��Ǵ�1��ʼ��
		data = new Item[capacity + 1];
		index = new int[capacity + 1];
		count = 0;
		this->capacity = capacity + 1;
	}
	~IndexMaxHeap() {
		delete[] data;
		delete[] index;
	}
	
	int size() {
		return count;
	}
	
	bool isEmpty() {
		return count == 0;
	}
	// ����i�����û���˵�Ǵ�0��ʼ������,����ʵ����������i+1
	void insert(int i, Item item) {
		assert(count + 1 <= capacity);
		assert(i + 1 >= 1 && i + 1 <= capacity);

		i = i + 1;
		data[i] = item;
		// ???�Ƿ���ص� -- ���ص��������Ϊappend
		index[count + 1] = i;
		++count;
		shiftUp(count);
		return;
	}
	// ��ȡ���ֵ
	Item extractMax() {
		assert(count > 0);
		Item ret = data[index[1]];
		swap(index[1], index[count]);
		--count;
		shiftDown(1);
		return ret;
	}
	// ��ȡ���ֵ������
	int extractMaxIndex() {
		assert(count > 0);
		int ret = index[1];
		swap(index[1], index[count]);
		--count;
		shiftDown(1);
		return ret;
	}
	// ��ȡ���ֵ
	Item getMax() {
		assert(count > 0);
		Item ret = data[index[1]];
		return ret;
	}
	// ��ȡ���ֵ����
	int getMaxIndex() {
		assert(count > 0);
		int ret = index[1]-1;	// �û�����������Ҫ-1
		return ret;
	}
	// ��ȡ����i��ֵ
	Item getItem(int i) {
		assert(count > 0 && i + 1 <= count);
		return data[i + 1];
	}
	// �ı�����i��ֵ
	void change(int i, Item newItem) {
		i = i + 1;
		data[i] = newItem;
		// �ҵ�indexes[j] = i, j��ʾdata[i]�ڶ��е�λ��
		// ֮��shiftUp(j), ��shiftDown(j)
		for (int j = 1; j <= count; ++j) {
			if (index[j] == i) {
				shiftUp(j);
				shiftDown(j);
				return;
			}
		}
	}
	void testPrint() {
		for (int i = 1; i <= count; ++i) {
			cout <<  i << "-index" << index[i]  <<": " << data[i] << endl;
		}
		return;
	}

	// test reverse index
	bool testReverseIndex() {

		int* copyIndexes = new int[count + 1];

		for (int i = 0; i <= count; i++) {
			copyIndexes[i] = index[i];
		}

		copyIndexes[0] = 0;
		std::sort(copyIndexes, copyIndexes + count + 1);

		bool res = true;
		for (int i = 1; i <= count; i++)
			if (copyIndexes[i - 1] + 1 != copyIndexes[i])
				res = res || false;

		delete[] copyIndexes;

		if (!res) {
			cout << "Error 1" << endl;
			return res;
		}

		return true;
	}
};

template<typename T>
void heapSortUsingIndexMaxHeap(T arr[], int n) {

	IndexMaxHeap<T> indexMaxHeap = IndexMaxHeap<T>(n);
	for (int i = 0; i < n; i++)
		indexMaxHeap.insert(i, arr[i]);
	//assert(indexMaxHeap.testReverseIndex());

	for (int i = n - 1; i >= 0; i--)
		arr[i] = indexMaxHeap.extractMax();
}

template<typename Item>
class IndexMaxHeap2 {
	// �������ѣ����������Ķѡ�
	// �����û���Ҫ�ı�ĳһ�����Ķ�
private:
	Item* data;		// ����
	int* index;		// ������ index[i]�Ǵ�ŵ�λ��,����˵index[1]�ŵ�һ��index[1]����������ǵ�һԪ���������ڵ�λ��
	// rev[i]��ʾ����i��index���е�λ��
	//index[i] = j
	//rev[j] = i
	//index[rev[i]]=i , rev[index[i]] = i
	int* reverse;	// ������ң�����˵����i=4���ڶ��е�λ�ã����û��rev���Ǿ���Ҫ��������index[j]==i��rev[4]��¼����i��ͨ������index[i]�����ҵ����е�λ��
	int count;		// ���ݸ���
	int capacity;	// ����

	// ���ϵ���
	void shiftUp(int k) {
		// ԭ���Ƚ�data[k]��[k / 2]��������Ҫ�ж�data����index
		while (k > 1 && data[index[k / 2]] < data[index[k]]) {
			// ����ֻ����index
			swap(index[k / 2], index[k]);
			reverse[index[k / 2]] = k / 2;
			reverse[index[k]] = k;
			k /= 2;
		}
		return;
	}

	// ���µ���
	void shiftDown(int k) {
		while (2 * k <= count) {
			int j = 2 * k;		// j��k������
			if (j + 1 <= count && data[index[j]] < data[index[j + 1]]) {
				++j;
			}
			if (data[index[k]] >= data[index[j]]) {
				break;
			}
			swap(index[k], index[j]);
			reverse[index[j]] = j;
			reverse[index[k]] = k;
			k = j;
		}
		return;
	}

public:
	IndexMaxHeap2(int capacity) {
		// �û������Ǵ�0��ʼ�����ģ����Ƕ��Ǵ�1��ʼ��
		data = new Item[capacity + 1];
		index = new int[capacity + 1];
		reverse = new int[capacity + 1];
		for (int i = 0; i <= capacity; i++)
			reverse[i] = 0;
		count = 0;
		this->capacity = capacity + 1;
	}
	~IndexMaxHeap2() {
		delete[] data;
		delete[] index;
		delete[] reverse;
	}

	int size() {
		return count;
	}

	bool isEmpty() {
		return count == 0;
	}
	// ����i�����û���˵�Ǵ�0��ʼ������,����ʵ����������i+1
	void insert(int i, Item item) {
		assert(count + 1 <= capacity);
		assert(i + 1 >= 1 && i + 1 <= capacity);

		i = i + 1;
		data[i] = item;
		// ???�Ƿ���ص� -- ���ص��������Ϊappend
		index[count + 1] = i;
		reverse[i] = count + 1;
		++count;
		shiftUp(count);
		return;
	}
	// ��ȡ���ֵ
	Item extractMax() {
		assert(count > 0);
		Item ret = data[index[1]];
		swap(index[1], index[count]);
		reverse[index[count]] = 0;	// �����ɾ����
		reverse[index[1]] = 1;
		--count;
		shiftDown(1);
		return ret;
	}
	// ��ȡ���ֵ������
	int extractMaxIndex() {
		assert(count > 0);
		int ret = index[1];
		swap(index[1], index[count]);
		reverse[index[count]] = 0;	// �����ɾ����
		reverse[index[1]] = 1;
		--count;
		shiftDown(1);
		return ret;
	}
	// ��ȡ���ֵ
	Item getMax() {
		assert(count > 0);
		Item ret = data[index[1]];
		return ret;
	}
	// ��ȡ���ֵ����
	int getMaxIndex() {
		assert(count > 0);
		int ret = index[1] - 1;	// �û�����������Ҫ-1
		return ret;
	}
	// ��ȡ����i��ֵ
	Item getItem(int i) {
		assert(count > 0 && i + 1 <= count);
		return data[i + 1];
	}
	// �ı�����i��ֵ
	void change(int i, Item newItem) {
		i = i + 1;
		data[i] = newItem;
		int j = reverse[i];
		shiftUp(j);
		shiftDown(j);
		return;
		//// �ҵ�indexes[j] = i, j��ʾdata[i]�ڶ��е�λ��
		//// ֮��shiftUp(j), ��shiftDown(j)
		//for (int j = 1; j <= count; ++j) {
		//	if (index[j] == i) {
		//		shiftUp(j);
		//		shiftDown(j);
		//		return;
		//	}
		//}
	}
	void testPrint() {
		for (int i = 1; i <= count; ++i) {
			cout << i << "-index" << index[i] << ": " << data[i] << endl;
		}
		return;
	}

	// test reverse index
	bool testReverseIndex() {

		int* copyIndexes = new int[count + 1];

		for (int i = 0; i <= count; i++) {
			copyIndexes[i] = index[i];
		}

		copyIndexes[0] = 0;
		std::sort(copyIndexes, copyIndexes + count + 1);

		bool res = true;
		for (int i = 1; i <= count; i++)
			if (copyIndexes[i - 1] + 1 != copyIndexes[i])
				res = res || false;

		delete[] copyIndexes;

		if (!res) {
			cout << "Error 1" << endl;
			return res;
		}

		return true;
	}
};