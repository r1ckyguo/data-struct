#pragma once
#include <iostream>
using namespace std;

// ��arr[l...mid]��arr[mid+1...r]�����ֽ��й鲢
template<typename T>
void __merge(T arr[], int left, int middle, int right) {
	int n = right - left + 1;
	T* aux = new T[n];	// ��������
	for (int i = left; i <= right; i++) {
		// ���������鸽��ֵ
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
// �ݹ�ʹ�ù鲢����,��arr[l...r]�ķ�Χ��������
template<typename T>
void __mergeSort(T arr[], int left, int right) {
	if (left >= right) {
		return;
	}
	int middle = (left + right) / 2;
	__mergeSort(arr, left, middle);
	__mergeSort(arr, middle + 1, right);
	__merge(arr, left, middle, right);		// ���кϲ���Ҳ�����������
	//SortTestHelper::printArray(arr, 10);
	return;
}

// �Ż���鲢����
template<typename T>
void __mergeSort2(T arr[], int left, int right) {
	if (right - left <= 15) {
		// �Ż�1
		insertionSort4(arr, left, right);			// ���ڹ鲢����Ĳ�������
		return;
	}
	int middle = (left + right) / 2;
	__mergeSort2(arr, left, middle);
	__mergeSort2(arr, middle + 1, right);
	// �Ż�2
	// ����arr[mid] <= arr[mid+1]�����,������merge
	// ���ڽ������������ǳ���Ч,���Ƕ���һ�����,��һ����������ʧ
	if (arr[middle] > arr[middle + 1]) {
		__merge(arr, left, middle, right);
	}
	return;
}

// ���⿪�ŵĽӿ�,�����ڲ�����
template<typename T>
void mergeSort(T arr[], int n) {
	__mergeSort(arr, 0, n-1);	
}

// ���⿪�ŵĽӿ�2,�����ڲ�����
template<typename T>
void mergeSort2(T arr[], int n) {
	__mergeSort2(arr, 0, n-1);
}

int mergeSortTest() {
	int n = 50000;

	// ����1 һ���Բ���
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


	// ����2 ���Խ������������
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