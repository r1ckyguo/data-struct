#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

// 写法1
template<typename T>
void insertionSort1(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		// 寻找元素arr[i]合适的插入位置
		// j为当前位置，往前查找进行插入
		for (int j = i; j > 0; j--) {
			if (arr[j] < arr[j - 1]) {
				swap(arr[j], arr[j - 1]);
			}
			else {
				break;	//当前j已经放置好位置了，可以退出当前循环
			}
		}
	}
	return;
}

// 写法2
template<typename T>
void insertionSort2(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
			swap(arr[j], arr[j - 1]);
		}
	}
	return;
}

// 优化版
template<typename T>
void insertionSort3(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		T e = arr[i];
		int j;
		for (j = i; j > 0 && e < arr[j - 1]; j--) {
			arr[j] = arr[j - 1];		// 把前一个移动到后一个坑中
		}
		arr[j] = e; // 此时j才是e需要放入的地方
	}
	return;
}

// 用于归并排序优化的插入排序
template<typename T>
void insertionSort4(T arr[], int left, int right) {
	for (int i = left+1; i <= right; i++) {
		T e = arr[i];
		int j;
		for (j = i; j > left && e < arr[j - 1]; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = e;
	}
	return;
}


// test
int insertionTest() {
	int n = 10000;
	cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
	int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);
	// 1.对比插入和选择排序
	SortTestHelper::testSort("Insertion Sort", insertionSort1, arr1, n);
	SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);
	
	delete[] arr1;
	delete[] arr2;

	cout << "Test for Nearly Ordered Array, size = " << n << ", random range [0, " << n << "]" << endl;
	arr1 = SortTestHelper::generateNearlyOrderedArray(n, 10);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	// 2.对比插入和选择排序,在近有序的情况下
	SortTestHelper::testSort("Insertion Sort", insertionSort2, arr1, n);
	SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);

	delete[] arr1;
	delete[] arr2;
	cout << endl;

	cout << "Test for Nearly Same Array, size = " << n << ", random range [0, " << n << "]" << endl;
	arr1 = SortTestHelper::generateRandomArray(n, 0, 10);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	// 3.对比插入和选择排序,在有较多相同元素的情况下
	SortTestHelper::testSort("Insertion Sort", insertionSort2, arr1, n);
	SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);

	delete[] arr1;
	delete[] arr2;
	cout << endl;

	cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
	arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	// 4. 对比插入和插入优化版排序   
	SortTestHelper::testSort("Insertion Sort", insertionSort2, arr1, n);
	SortTestHelper::testSort("Insertion Sort advance", insertionSort3, arr2, n);

	delete[] arr1;
	delete[] arr2;
	return 0;
}