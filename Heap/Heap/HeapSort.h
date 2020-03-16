#pragma once
#include <iostream>
#include "Heap.h"

template<typename T>
void heapSort1(T arr[], int n) {
	MaxHeap<T> maxheap = MaxHeap<T>(n);
	for (int i = 0; i < n; i++) {
		maxheap.insert(arr[i]);		// 把所有数据插入到堆中
	}
	for (int i = n - 1; i >= 0; i--) {
		arr[i] = maxheap.extractMax();	// 每次都取最大的数据，从后往前放，也就是从小排到大
	}
	return;
}

template<typename T>
void heapSort2(T arr[], int n) {
	// 另一种堆排序
	MaxHeap<T> maxheap = MaxHeap<T>(arr, n);		// 使用另一种初始化方法
	for (int i = n - 1; i >= 0; i--) {
		arr[i] = maxheap.extractMax();
	}
}

template<typename T>
void __shiftDown(T arr[], int n, int k) {
	// n为数组长度，k为父节点，从k往下shiftdown
	while (2 * k + 1 < n) {
		// 2 * k + 1是k的左孩子,如果有左孩子的话
		int j = 2 * k + 1;
		if (j + 1 < n && arr[j] < arr[j + 1]) {
			// j+1是右孩子，如果有右孩子，且右孩子大于左孩子，那么j指向右孩子
			++j;
		}
		if (arr[k] >= arr[j]) break;
		swap(arr[k], arr[j]);
		k = j;
	}
	return;
}

template<typename T>
void heapSort3(T arr[], int n) {
	// 原地堆排序
	// Heapify
	for (int i = (n - 1) / 2; i >= 0; i--) {
		// 这时索引是从0开始的数组，所以要>=0
		// (n-1)/2是最后一个父节点，往前shiftdown
		__shiftDown(arr, n, i);
	}
	// 开始排序
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);	// 把最大的往后交换，然后在shiftdown
		__shiftDown(arr, i, 0);		// 参与shiftdown的有i个元素，对第0个往下shiftdown
	}
	return;
}

template<typename T>
void __shiftDown2(T arr[], int n, int k) {

	T e = arr[k];
	while (2 * k + 1 < n) {
		int j = 2 * k + 1;
		if (j + 1 < n && arr[j + 1] > arr[j])
			j += 1;

		if (e >= arr[j]) break;


		arr[k] = arr[j];
		k = j;
	}

	arr[k] = e;
}

template<typename T>
void heapSort4(T arr[], int n) {

	for (int i = (n - 1) / 2; i >= 0; i--)
		__shiftDown2(arr, n, i);

	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		__shiftDown2(arr, i, 0);
	}
}