#pragma once
#include<iostream>
#include<algorithm>
#include<ctime>
#include "SortTestHelper.h"
using namespace std;

template<typename T>
int __partition(T arr[], int left, int right) {
	// 优化:随机找一个元素与哨兵进行交换
	swap(arr[left], arr[(rand() % (right - left + 1) + left)]);
	// 合并过程，小于v的放左边，大于v的放右边
	T v = arr[left];
	int j = left;		// j维护小于v的索引，[left, j]都是小于v的，[j+1, right]是大于v的
	for (int i = left + 1; i <= right; i++) {
		if (arr[i] < v) {
			++j;
			swap(arr[j], arr[i]);
		}
	}
	// 将哨兵位置与最后一个小于v的进行交换
	swap(arr[j], arr[left]);
	// 此时j的位置就是v，左边小于v，右边大于v
	return j;
}


template<typename T>
void __quickSort(T arr[], int left, int right) {
	// 此时可以退出
	if (left >= right) {
		return;
	}
	// 优化：在需要排序到一定范围时，使用插入排序
	if (right - left <= 15) {
		insertionSort4(arr, left, right);
		return;
	}
	// p的位置是当前已经分割好的元素，小于p放左边，大于p放右边
	int p = __partition(arr, left, right);
	__quickSort(arr, left, p - 1);		// 排小于p，左边的元素
	__quickSort(arr, p + 1, right);		// 排大于p，右边的元素
	return;
}

template<typename T>
void quickSort(T arr[], int n) {
	srand(time(NULL));
	__quickSort(arr, 0, n - 1);
	return;
}

// =v的元素分散在两边。第一版=v元素只在一边，会不平衡导致效率低。
template<typename T>
int __partition2(T arr[], int left, int right) {
	swap(arr[left], arr[rand() % (right - left + 1) + left]);
	T v = arr[left];

	// 优化：arr[l+1...i) <= v; arr(j...r] >= v. =v的元素可以放在两边， 当相同元素多时效率会高一点
	int i = left + 1, j = right;
	while (true) {
		// i向右对比索引
		while (i <= right && arr[i] < v) {
			i++;
		}
		// j向左对比索引
		while (j >= left + 1 && arr[j] > v) {
			j--;
		}
		// 此时已经拍好，可以退出
		if (i > j) {
			break;
		}
		// 此时i和j处，分别放着大于v和小于v的元素。所以需要交换一下
		swap(arr[i], arr[j]);
		i++;
		j--;
	}
	swap(arr[left], arr[j]);
	return j;
}

template<typename T>
void __quickSort2(T arr[], int left, int right) {
	// 此时可以退出
	if (left >= right) {
		return;
	}
	// 优化：在需要排序到一定范围时，使用插入排序
	if (right - left <= 15) {
		insertionSort4(arr, left, right);
		return;
	}
	// p的位置是当前已经分割好的元素，小于p放左边，大于p放右边
	int p = __partition2(arr, left, right);
	__quickSort2(arr, left, p - 1);
	__quickSort2(arr, p + 1, right);
	return;
}

template<typename T>
void quickSort2(T arr[], int n) {
	srand(time(NULL));
	__quickSort2(arr, 0, n - 1);
	return;
}

template<typename T>
void __quickSort3Way(T arr[], int left, int right) {
	if (right - left <= 15) {
		insertionSort4(arr, left, right);
		return;
	}

	swap(arr[left], arr[rand() % (right - left + 1) + left]);

	T v = arr[left];
	// lt负责维护小于v的，ge负责维护大于v的，i负责维护等于v的索引
	int lt = left;			// arr[l+1...lt] < v
	int gt = right + 1;		// arr[gt...r] > v
	int i = left + 1;		 // arr[lt+1...i) == v
	while (i < gt) {	// i往右，gt往左，当相遇时就结束
		if (arr[i] < v) {
			swap(arr[i], arr[lt + 1]);		// 等于v的i区域首个元素（lt+1）与arr[i]交换
			++lt;
			++i;	// 此时i需要往后移
		}
		else if (arr[i] > v) {
			swap(arr[i], arr[gt - 1]);		// gt的首个区域元素与arr[i]交换
			gt--;		// 此时i不需要往后移，因为交换后的arr[i]还没有比较过
		}
		else {	// arr[i] = v
			++i;
		}
	}
	swap(arr[lt], arr[left]);			// 最后将小于v区域的最后一个元素（lt）与哨兵元素进行交换即可排序完成
	// 递归排序左边[left, lt-1]和右边[gt, right]区域，跳过中间区域
	__quickSort3Way(arr, left, lt - 1);	
	__quickSort3Way(arr, gt, right);
	return;
}

template<typename T>
void quickSort3Way(T arr[], int n) {
	srand(time(NULL));
	__quickSort3Way(arr, 0, n - 1);
	return;
}

int quickSortTest() {
	int n = 1000000;

	// 测试1 一般性测试
	cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
	int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);
	int* arr3 = SortTestHelper::copyIntArray(arr1, n);
	int* arr4 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Merge Sort", mergeSort2, arr1, n);
	SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
	SortTestHelper::testSort("Quick Sort2", quickSort2, arr3, n);
	SortTestHelper::testSort("Quick Sort3 ways", quickSort3Way, arr4, n);


	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;


	cout << endl;


	// 测试2 测试近乎有序的数组
	int swapTimes = 100;
	cout << "Test for Random Nearly Ordered Array, size = " << n << ", swap time = " << swapTimes << endl;
	arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	arr3 = SortTestHelper::copyIntArray(arr1, n);
	arr4 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Merge Sort", mergeSort2, arr1, n);
	SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
	SortTestHelper::testSort("Quick Sort2", quickSort2, arr3, n);
	SortTestHelper::testSort("Quick Sort3 ways", quickSort3Way, arr4, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;

	cout << endl;


	// 测试3 测试存在包含大量相同元素的数组
	cout << "Test for Random Array, size = " << n << ", random range [0,10]" << endl;
	arr1 = SortTestHelper::generateRandomArray(n, 0, 10);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	arr3 = SortTestHelper::copyIntArray(arr1, n);
	arr4 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Merge Sort", mergeSort2, arr1, n);
	SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
	SortTestHelper::testSort("Quick Sort2", quickSort2, arr3, n);
	SortTestHelper::testSort("Quick Sort3 ways", quickSort3Way, arr4, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;

	return 0;
}

/*
Test for Random Array, size = 1000000, random range [0, 1000000]
Merge Sort: 0.228 s
Quick Sort: 0.17 s
Quick Sort2: 0.129 s
Quick Sort3 ways: 0.118 s

Test for Random Nearly Ordered Array, size = 1000000, swap time = 100
Merge Sort: 0.005 s
Quick Sort: 0.075 s
Quick Sort2: 0.061 s
Quick Sort3 ways: 0.155 s

Test for Random Array, size = 1000000, random range [0,10]
Merge Sort: 0.186 s
Quick Sort: 40.506 s
Quick Sort2: 0.037 s
Quick Sort3 ways: 0.018 s
*/