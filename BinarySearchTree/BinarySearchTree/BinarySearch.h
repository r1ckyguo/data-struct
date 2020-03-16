#pragma once
#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

// 二分查找法,在有序数组arr中,查找target
// 如果找到target,返回相应的索引index
// 如果没有找到target,返回-1
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
			// 目标在左边
			r = mid - 1;
		}
		else {
			// 目标在右边
			l = mid + 1;
		}
		//cout << "l:" << l << " mid:" << mid << " r:" << r << endl;
	}
	return -1;	// 没有找到
}

// 递归方法写二分查找法
template <typename T>
int __search(T arr[], int l, int r, T target) {
	if (r > l) {
		return -1;	// 这时找不到
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