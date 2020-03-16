#pragma once
#include<iostream>
#include<algorithm>
#include<ctime>
#include "SortTestHelper.h"
using namespace std;

template<typename T>
int __partition(T arr[], int left, int right) {
	// �Ż�:�����һ��Ԫ�����ڱ����н���
	swap(arr[left], arr[(rand() % (right - left + 1) + left)]);
	// �ϲ����̣�С��v�ķ���ߣ�����v�ķ��ұ�
	T v = arr[left];
	int j = left;		// jά��С��v��������[left, j]����С��v�ģ�[j+1, right]�Ǵ���v��
	for (int i = left + 1; i <= right; i++) {
		if (arr[i] < v) {
			++j;
			swap(arr[j], arr[i]);
		}
	}
	// ���ڱ�λ�������һ��С��v�Ľ��н���
	swap(arr[j], arr[left]);
	// ��ʱj��λ�þ���v�����С��v���ұߴ���v
	return j;
}


template<typename T>
void __quickSort(T arr[], int left, int right) {
	// ��ʱ�����˳�
	if (left >= right) {
		return;
	}
	// �Ż�������Ҫ����һ����Χʱ��ʹ�ò�������
	if (right - left <= 15) {
		insertionSort4(arr, left, right);
		return;
	}
	// p��λ���ǵ�ǰ�Ѿ��ָ�õ�Ԫ�أ�С��p����ߣ�����p���ұ�
	int p = __partition(arr, left, right);
	__quickSort(arr, left, p - 1);		// ��С��p����ߵ�Ԫ��
	__quickSort(arr, p + 1, right);		// �Ŵ���p���ұߵ�Ԫ��
	return;
}

template<typename T>
void quickSort(T arr[], int n) {
	srand(time(NULL));
	__quickSort(arr, 0, n - 1);
	return;
}

// =v��Ԫ�ط�ɢ�����ߡ���һ��=vԪ��ֻ��һ�ߣ��᲻ƽ�⵼��Ч�ʵ͡�
template<typename T>
int __partition2(T arr[], int left, int right) {
	swap(arr[left], arr[rand() % (right - left + 1) + left]);
	T v = arr[left];

	// �Ż���arr[l+1...i) <= v; arr(j...r] >= v. =v��Ԫ�ؿ��Է������ߣ� ����ͬԪ�ض�ʱЧ�ʻ��һ��
	int i = left + 1, j = right;
	while (true) {
		// i���ҶԱ�����
		while (i <= right && arr[i] < v) {
			i++;
		}
		// j����Ա�����
		while (j >= left + 1 && arr[j] > v) {
			j--;
		}
		// ��ʱ�Ѿ��ĺã������˳�
		if (i > j) {
			break;
		}
		// ��ʱi��j�����ֱ���Ŵ���v��С��v��Ԫ�ء�������Ҫ����һ��
		swap(arr[i], arr[j]);
		i++;
		j--;
	}
	swap(arr[left], arr[j]);
	return j;
}

template<typename T>
void __quickSort2(T arr[], int left, int right) {
	// ��ʱ�����˳�
	if (left >= right) {
		return;
	}
	// �Ż�������Ҫ����һ����Χʱ��ʹ�ò�������
	if (right - left <= 15) {
		insertionSort4(arr, left, right);
		return;
	}
	// p��λ���ǵ�ǰ�Ѿ��ָ�õ�Ԫ�أ�С��p����ߣ�����p���ұ�
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
	// lt����ά��С��v�ģ�ge����ά������v�ģ�i����ά������v������
	int lt = left;			// arr[l+1...lt] < v
	int gt = right + 1;		// arr[gt...r] > v
	int i = left + 1;		 // arr[lt+1...i) == v
	while (i < gt) {	// i���ң�gt���󣬵�����ʱ�ͽ���
		if (arr[i] < v) {
			swap(arr[i], arr[lt + 1]);		// ����v��i�����׸�Ԫ�أ�lt+1����arr[i]����
			++lt;
			++i;	// ��ʱi��Ҫ������
		}
		else if (arr[i] > v) {
			swap(arr[i], arr[gt - 1]);		// gt���׸�����Ԫ����arr[i]����
			gt--;		// ��ʱi����Ҫ�����ƣ���Ϊ�������arr[i]��û�бȽϹ�
		}
		else {	// arr[i] = v
			++i;
		}
	}
	swap(arr[lt], arr[left]);			// ���С��v��������һ��Ԫ�أ�lt�����ڱ�Ԫ�ؽ��н��������������
	// �ݹ��������[left, lt-1]���ұ�[gt, right]���������м�����
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

	// ����1 һ���Բ���
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


	// ����2 ���Խ������������
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


	// ����3 ���Դ��ڰ���������ͬԪ�ص�����
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