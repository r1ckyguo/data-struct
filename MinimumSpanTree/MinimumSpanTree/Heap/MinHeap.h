#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;
template<typename Item>
class MinHeap {
private:
	Item* data;		// 元素存放数组，0位置不使用
	int count;		// 元素的个数
	int capacity;

public:
	MinHeap(int capacity) {
		data = new Item[capacity + 1];
		count = 0;
		this->capacity = capacity;
	}
	~MinHeap() {
		delete[] data;
	}
	int size() {	// 返回堆大小
		return count;
	}
	bool isEmpty() {	// 判断堆是否为空
		return count == 0;
	}
	// 插入堆
	void insert(Item item) {
		assert(count + 1 <= capacity);		// 确保count（从索引1开始）小于capacity
		data[count + 1] = item;				// 插入
		++count;			
		shiftUp(count);		// 调整堆
	}
    // 取出最小值
    Item getMin() {
        assert(count > 0);
        return data[1];
    }
    // 提取出最小值
    Item extractMin() {
        assert(count > 0);
        Item ret = data[1];
        swap(data[1], data[count]); // 将最大与最末元素交换
        --count;
        shiftDown(1);    // 从上往下调整
        return ret;
    }

    // heapify：指定一个数组，然后把其转为堆的形式
    MinHeap(Item arr[], int n) {
        data = new Item[n + 1];
        count = 0;
        this->capacity = n;
        for (int i = 0; i < n; i++) {
            data[i + 1] = arr[i];
        }
        count = n;
        for (int i = count / 2; i >= 1; i--) {
            // count/2是最后一个有孩子的节点，从他开始，查看是否需要向下调整
            shiftDown(i);
        }
        // 最后调整完后，data是一个最小堆
    }
    
private:
	// 堆调整，用于insert中的调整。向上调整
	void shiftUp(int k) {
		while (k > 1 && data[k] < data[k / 2]) {
			swap(data[k], data[k / 2]);
			k = k / 2;
		}
		return;
	}
    // 堆调整，用于extractMin的调整，向下调整
    void shiftDown(int k) {
        // 与孩子进行对比
        while (2 * k <= count) {
            int j = 2 * k;      // j是需要交换的孩子位置
            if (j + 1 <= count && data[j + 1] < data[j]) {  // 确保右孩子存在，且如果右孩子小于左孩子，那j变成右孩子
                j++;
            }
            if (data[k] <= data[j]) {
                break;
            }
            swap(data[k], data[j]);
            k = j;
        }
    }

};