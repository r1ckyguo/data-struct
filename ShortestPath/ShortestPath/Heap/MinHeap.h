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
	Item* data;		// Ԫ�ش�����飬0λ�ò�ʹ��
	int count;		// Ԫ�صĸ���
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
	int size() {	// ���ضѴ�С
		return count;
	}
	bool isEmpty() {	// �ж϶��Ƿ�Ϊ��
		return count == 0;
	}
	// �����
	void insert(Item item) {
		assert(count + 1 <= capacity);		// ȷ��count��������1��ʼ��С��capacity
		data[count + 1] = item;				// ����
		++count;			
		shiftUp(count);		// ������
	}
    // ȡ����Сֵ
    Item getMin() {
        assert(count > 0);
        return data[1];
    }
    // ��ȡ����Сֵ
    Item extractMin() {
        assert(count > 0);
        Item ret = data[1];
        swap(data[1], data[count]); // ���������ĩԪ�ؽ���
        --count;
        shiftDown(1);    // �������µ���
        return ret;
    }

    // heapify��ָ��һ�����飬Ȼ�����תΪ�ѵ���ʽ
    MinHeap(Item arr[], int n) {
        data = new Item[n + 1];
        count = 0;
        this->capacity = n;
        for (int i = 0; i < n; i++) {
            data[i + 1] = arr[i];
        }
        count = n;
        for (int i = count / 2; i >= 1; i--) {
            // count/2�����һ���к��ӵĽڵ㣬������ʼ���鿴�Ƿ���Ҫ���µ���
            shiftDown(i);
        }
        // ���������data��һ����С��
    }
    
private:
	// �ѵ���������insert�еĵ��������ϵ���
	void shiftUp(int k) {
		while (k > 1 && data[k] < data[k / 2]) {
			swap(data[k], data[k / 2]);
			k = k / 2;
		}
		return;
	}
    // �ѵ���������extractMin�ĵ��������µ���
    void shiftDown(int k) {
        // �뺢�ӽ��жԱ�
        while (2 * k <= count) {
            int j = 2 * k;      // j����Ҫ�����ĺ���λ��
            if (j + 1 <= count && data[j + 1] < data[j]) {  // ȷ���Һ��Ӵ��ڣ�������Һ���С�����ӣ���j����Һ���
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