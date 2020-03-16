#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

// д��1
template<typename T>
void insertionSort1(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		// Ѱ��Ԫ��arr[i]���ʵĲ���λ��
		// jΪ��ǰλ�ã���ǰ���ҽ��в���
		for (int j = i; j > 0; j--) {
			if (arr[j] < arr[j - 1]) {
				swap(arr[j], arr[j - 1]);
			}
			else {
				break;	//��ǰj�Ѿ����ú�λ���ˣ������˳���ǰѭ��
			}
		}
	}
	return;
}

// д��2
template<typename T>
void insertionSort2(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
			swap(arr[j], arr[j - 1]);
		}
	}
	return;
}

// �Ż���
template<typename T>
void insertionSort3(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		T e = arr[i];
		int j;
		for (j = i; j > 0 && e < arr[j - 1]; j--) {
			arr[j] = arr[j - 1];		// ��ǰһ���ƶ�����һ������
		}
		arr[j] = e; // ��ʱj����e��Ҫ����ĵط�
	}
	return;
}

// ���ڹ鲢�����Ż��Ĳ�������
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
	// 1.�ԱȲ����ѡ������
	SortTestHelper::testSort("Insertion Sort", insertionSort1, arr1, n);
	SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);
	
	delete[] arr1;
	delete[] arr2;

	cout << "Test for Nearly Ordered Array, size = " << n << ", random range [0, " << n << "]" << endl;
	arr1 = SortTestHelper::generateNearlyOrderedArray(n, 10);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	// 2.�ԱȲ����ѡ������,�ڽ�����������
	SortTestHelper::testSort("Insertion Sort", insertionSort2, arr1, n);
	SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);

	delete[] arr1;
	delete[] arr2;
	cout << endl;

	cout << "Test for Nearly Same Array, size = " << n << ", random range [0, " << n << "]" << endl;
	arr1 = SortTestHelper::generateRandomArray(n, 0, 10);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	// 3.�ԱȲ����ѡ������,���н϶���ͬԪ�ص������
	SortTestHelper::testSort("Insertion Sort", insertionSort2, arr1, n);
	SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);

	delete[] arr1;
	delete[] arr2;
	cout << endl;

	cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
	arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	// 4. �ԱȲ���Ͳ����Ż�������   
	SortTestHelper::testSort("Insertion Sort", insertionSort2, arr1, n);
	SortTestHelper::testSort("Insertion Sort advance", insertionSort3, arr2, n);

	delete[] arr1;
	delete[] arr2;
	return 0;
}