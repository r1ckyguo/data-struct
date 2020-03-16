#pragma once
#include <iostream>
#include <cassert>
using namespace std;

template<typename Item>
class IndexMaxHeap {
	// 索引最大堆，带有索引的堆。
	// 便于用户需要改变某一索引的堆
	// index[i]是存放的位置,比如说index[1]排第一，index[1]里面的索引是第一元素真正存在的位置
private:
	Item* data;		// 数据
	int* index;		// 索引
	int count;		// 数据个数
	int capacity;	// 容量

	// 向上调整
	void shiftUp(int k) {
		// 原本比较data[k]和[k / 2]，现在需要判断data里面index
		while (k > 1 && data[index[k / 2]] < data[index[k]]) {
			// 交换只交换index
			swap(index[k / 2], index[k]);
			k /= 2;
		}
		return;
	}

	// 向下调整
	void shiftDown(int k) {
		while (2 * k <= count) {
			int j = 2 * k;		// j是k的左孩子
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
		// 用户索引是从0开始索引的，但是堆是从1开始的
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
	// 传入i对于用户来说是从0开始索引的,所以实际索引数是i+1
	void insert(int i, Item item) {
		assert(count + 1 <= capacity);
		assert(i + 1 >= 1 && i + 1 <= capacity);

		i = i + 1;
		data[i] = item;
		// ???是否会重叠 -- 会重叠，建议改为append
		index[count + 1] = i;
		++count;
		shiftUp(count);
		return;
	}
	// 提取最大值
	Item extractMax() {
		assert(count > 0);
		Item ret = data[index[1]];
		swap(index[1], index[count]);
		--count;
		shiftDown(1);
		return ret;
	}
	// 提取最大值的索引
	int extractMaxIndex() {
		assert(count > 0);
		int ret = index[1];
		swap(index[1], index[count]);
		--count;
		shiftDown(1);
		return ret;
	}
	// 获取最大值
	Item getMax() {
		assert(count > 0);
		Item ret = data[index[1]];
		return ret;
	}
	// 获取最大值索引
	int getMaxIndex() {
		assert(count > 0);
		int ret = index[1]-1;	// 用户看到的索引要-1
		return ret;
	}
	// 获取索引i的值
	Item getItem(int i) {
		assert(count > 0 && i + 1 <= count);
		return data[i + 1];
	}
	// 改变索引i的值
	void change(int i, Item newItem) {
		i = i + 1;
		data[i] = newItem;
		// 找到indexes[j] = i, j表示data[i]在堆中的位置
		// 之后shiftUp(j), 再shiftDown(j)
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
	// 索引最大堆，带有索引的堆。
	// 便于用户需要改变某一索引的堆
private:
	Item* data;		// 数据
	int* index;		// 索引， index[i]是存放的位置,比如说index[1]排第一，index[1]里面的索引是第一元素真正存在的位置
	// rev[i]表示索引i在index堆中的位置
	//index[i] = j
	//rev[j] = i
	//index[rev[i]]=i , rev[index[i]] = i
	int* reverse;	// 反向查找，比如说想找i=4的在堆中的位置，如果没有rev，那就需要线性搜索index[j]==i。rev[4]记录的是i，通过访问index[i]即可找到堆中的位置
	int count;		// 数据个数
	int capacity;	// 容量

	// 向上调整
	void shiftUp(int k) {
		// 原本比较data[k]和[k / 2]，现在需要判断data里面index
		while (k > 1 && data[index[k / 2]] < data[index[k]]) {
			// 交换只交换index
			swap(index[k / 2], index[k]);
			reverse[index[k / 2]] = k / 2;
			reverse[index[k]] = k;
			k /= 2;
		}
		return;
	}

	// 向下调整
	void shiftDown(int k) {
		while (2 * k <= count) {
			int j = 2 * k;		// j是k的左孩子
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
		// 用户索引是从0开始索引的，但是堆是从1开始的
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
	// 传入i对于用户来说是从0开始索引的,所以实际索引数是i+1
	void insert(int i, Item item) {
		assert(count + 1 <= capacity);
		assert(i + 1 >= 1 && i + 1 <= capacity);

		i = i + 1;
		data[i] = item;
		// ???是否会重叠 -- 会重叠，建议改为append
		index[count + 1] = i;
		reverse[i] = count + 1;
		++count;
		shiftUp(count);
		return;
	}
	// 提取最大值
	Item extractMax() {
		assert(count > 0);
		Item ret = data[index[1]];
		swap(index[1], index[count]);
		reverse[index[count]] = 0;	// 这个是删除的
		reverse[index[1]] = 1;
		--count;
		shiftDown(1);
		return ret;
	}
	// 提取最大值的索引
	int extractMaxIndex() {
		assert(count > 0);
		int ret = index[1];
		swap(index[1], index[count]);
		reverse[index[count]] = 0;	// 这个是删除的
		reverse[index[1]] = 1;
		--count;
		shiftDown(1);
		return ret;
	}
	// 获取最大值
	Item getMax() {
		assert(count > 0);
		Item ret = data[index[1]];
		return ret;
	}
	// 获取最大值索引
	int getMaxIndex() {
		assert(count > 0);
		int ret = index[1] - 1;	// 用户看到的索引要-1
		return ret;
	}
	// 获取索引i的值
	Item getItem(int i) {
		assert(count > 0 && i + 1 <= count);
		return data[i + 1];
	}
	// 改变索引i的值
	void change(int i, Item newItem) {
		i = i + 1;
		data[i] = newItem;
		int j = reverse[i];
		shiftUp(j);
		shiftDown(j);
		return;
		//// 找到indexes[j] = i, j表示data[i]在堆中的位置
		//// 之后shiftUp(j), 再shiftDown(j)
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