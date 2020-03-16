#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;
template<typename Item>
class MaxHeap {
private:
	Item* data;		// 元素存放数组，0位置不使用
	int count;		// 元素的个数
	int capacity;

public:
	MaxHeap(int capacity) {
		data = new Item[capacity + 1];
		count = 0;
		this->capacity = capacity;
	}
	~MaxHeap() {
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
    // 取出最大值
    Item getMax() {
        assert(count > 0);
        return data[1];
    }
    // 提取出最大值
    Item extractMax() {
        assert(count > 0);
        Item ret = data[1];
        swap(data[1], data[count]); // 将最大与最末元素交换
        --count;
        shiftDown(1);    // 从上往下调整
        return ret;
    }

    // heapify：指定一个数组，然后把其转为堆的形式
    MaxHeap(Item arr[], int n) {
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
        // 最后调整完后，data是一个最大堆
    }
    
private:
	// 堆调整，用于insert中的调整。向上调整
	void shiftUp(int k) {
		while (k > 1 && data[k] > data[k / 2]) {
			swap(data[k], data[k / 2]);
			k = k / 2;
		}
		return;
	}
    // 堆调整，用于extractMax的调整，向下调整
    void shiftDown(int k) {
        // 与孩子进行对比
        while (2 * k <= count) {
            int j = 2 * k;      // j是需要交换的孩子位置
            if (j + 1 <= count && data[j + 1] > data[j]) {  // 确保右孩子存在，且如果右孩子大于左孩子，那j变成右孩子
                j++;
            }
            if (data[k] >= data[j]) {
                break;
            }
            swap(data[k], data[j]);
            k = j;
        }
    }
public:
    void testPrint() {

        if (size() >= 100) {
            cout << "Fancy print can only work for less than 100 int";
            return;
        }

        if (typeid(Item) != typeid(int)) {
            cout << "Fancy print can only work for int item";
            return;
        }

        cout << "The Heap size is: " << size() << endl;
        cout << "data in heap: ";
        for (int i = 1; i <= size(); i++)
            cout << data[i] << " ";
        cout << endl;
        cout << endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while (n > 0) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level - 1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for (int level = 0; level < max_level; level++) {
            string line1 = string(max_level_number * 3 - 1, ' ');

            int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
            bool isLeft = true;
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++) {
                putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
                isLeft = !isLeft;
            }
            cout << line1 << endl;

            if (level == max_level - 1)
                break;

            string line2 = string(max_level_number * 3 - 1, ' ');
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
                putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
            cout << line2 << endl;

            cur_tree_max_level_number /= 2;
        }
    }

private:
    void putNumberInLine(int num, string& line, int index_cur_level, int cur_tree_width, bool isLeft) {

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if (num >= 10) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else {
            if (isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine(string& line, int index_cur_level, int cur_tree_width) {

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
        assert(offset_left + 1 < line.size());
        int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert(offset_right < line.size());

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }
};