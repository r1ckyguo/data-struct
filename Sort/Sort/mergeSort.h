#pragma once
#include <iostream>
using namespace std;

// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template<typename T>
void __merge(T arr[], int left, int middle, int right) {
	int n = right - left + 1;
	T* aux = new T[n];	// 辅助数组
	for (int i = left; i <= right; i++) {
		// 给辅助数组附上值
		aux[i - left] = arr[i];
	}
	int i = left, j = middle + 1;
	for (int k = left; k <= right; k++) {
		if (i > middle) {
			arr[k] = aux[j - left];
			j++;
		}
		else if (j > right) {
			arr[k] = aux[i - left];
			i++;
		}
		else if (aux[i - left] < aux[j - left]) {
			arr[k] = aux[i - left];
			i++;
		}
		else if (aux[i - left] >= aux[j - left]) {
			arr[k] = aux[j - left];
			j++;
		}
	}
	delete[]aux;
	return;
}
// 递归使用归并排序,对arr[l...r]的范围进行排序
template<typename T>
void __mergeSort(T arr[], int left, int right) {
	if (left >= right) {
		return;
	}
	int middle = (left + right) / 2;
	__mergeSort(arr, left, middle);
	__mergeSort(arr, middle + 1, right);
	__merge(arr, left, middle, right);		// 进行合并，也就是排序过程
	//SortTestHelper::printArray(arr, 10);
	return;
}

// 优化版归并排序
template<typename T>
void __mergeSort2(T arr[], int left, int right) {
	if (right - left <= 15) {
		// 优化1
		insertionSort4(arr, left, right);			// 用于归并排序的插入排序
		return;
	}
	int middle = (left + right) / 2;
	__mergeSort2(arr, left, middle);
	__mergeSort2(arr, middle + 1, right);
	// 优化2
	// 对于arr[mid] <= arr[mid+1]的情况,不进行merge
	// 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
	if (arr[middle] > arr[middle + 1]) {
		__merge(arr, left, middle, right);
	}
	return;
}

// 对外开放的接口,调用内部函数
template<typename T>
void mergeSort(T arr[], int n) {
	__mergeSort(arr, 0, n-1);	
}

// 对外开放的接口2,调用内部函数
template<typename T>
void mergeSort2(T arr[], int n) {
	__mergeSort2(arr, 0, n-1);
}

int mergeSortTest() {
	int n = 50000;

	// 测试1 一般性测试
	cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
	int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);
	int* arr3 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Insertion Sort", insertionSort3, arr1, n);
	SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
	SortTestHelper::testSort("Merge Sort 2", mergeSort2, arr3, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;

	cout << endl;


	// 测试2 测试近乎有序的数组
	int swapTimes = 10;
	cout << "Test for Random Nearly Ordered Array, size = " << n << ", swap time = " << swapTimes << endl;
	arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	arr3 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Insertion Sort", insertionSort3, arr1, n);
	SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
	SortTestHelper::testSort("Merge Sort 2", mergeSort2, arr3, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;

	return 0;
}