#pragma once
#include <iostream>
#include "Heap.h"

template<typename T>
void heapSort1(T arr[], int n) {
	MaxHeap<T> maxheap = MaxHeap<T>(n);
	for (int i = 0; i < n; i++) {
		maxheap.insert(arr[i]);		// ���������ݲ��뵽����
	}
	for (int i = n - 1; i >= 0; i--) {
		arr[i] = maxheap.extractMax();	// ÿ�ζ�ȡ�������ݣ��Ӻ���ǰ�ţ�Ҳ���Ǵ�С�ŵ���
	}
	return;
}

template<typename T>
void heapSort2(T arr[], int n) {
	// ��һ�ֶ�����
	MaxHeap<T> maxheap = MaxHeap<T>(arr, n);		// ʹ����һ�ֳ�ʼ������
	for (int i = n - 1; i >= 0; i--) {
		arr[i] = maxheap.extractMax();
	}
}

template<typename T>
void __shiftDown(T arr[], int n, int k) {
	// nΪ���鳤�ȣ�kΪ���ڵ㣬��k����shiftdown
	while (2 * k + 1 < n) {
		// 2 * k + 1��k������,��������ӵĻ�
		int j = 2 * k + 1;
		if (j + 1 < n && arr[j] < arr[j + 1]) {
			// j+1���Һ��ӣ�������Һ��ӣ����Һ��Ӵ������ӣ���ôjָ���Һ���
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
	// ԭ�ض�����
	// Heapify
	for (int i = (n - 1) / 2; i >= 0; i--) {
		// ��ʱ�����Ǵ�0��ʼ�����飬����Ҫ>=0
		// (n-1)/2�����һ�����ڵ㣬��ǰshiftdown
		__shiftDown(arr, n, i);
	}
	// ��ʼ����
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);	// ���������󽻻���Ȼ����shiftdown
		__shiftDown(arr, i, 0);		// ����shiftdown����i��Ԫ�أ��Ե�0������shiftdown
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