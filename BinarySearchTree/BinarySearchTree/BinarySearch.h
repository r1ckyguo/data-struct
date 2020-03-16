#pragma once
#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

// ���ֲ��ҷ�,����������arr��,����target
// ����ҵ�target,������Ӧ������index
// ���û���ҵ�target,����-1
template <typename T>
int binarySearch(T arr[], int n, T target) {
	int l = 0, r = n - 1;
	int mid;
	while (l <= r) {
		//mid = (l + r) / 2;
		// ???
		mid = l + (r - l) / 2;
		if (arr[mid] == target) {
			return mid;
		}
		if (arr[mid] > target) {
			// Ŀ�������
			r = mid - 1;
		}
		else {
			// Ŀ�����ұ�
			l = mid + 1;
		}
		//cout << "l:" << l << " mid:" << mid << " r:" << r << endl;
	}
	return -1;	// û���ҵ�
}

// �ݹ鷽��д���ֲ��ҷ�
template <typename T>
int __search(T arr[], int l, int r, T target) {
	if (r > l) {
		return -1;	// ��ʱ�Ҳ���
	}
	int mid = (l + r) / 2;
	if (arr[mid] == target) {
		return mid;
	}
	if (arr[mid] > target) {
		return __search(arr, l, mid - 1, target);
	}
	if (arr[mid] < target) {
		return __search(arr, mid + 1, r, target);
	}
}

template <typename T>
int binarySearch2(T arr[], int n, T target) {
	return __search(arr, 0, n-1, target);
}