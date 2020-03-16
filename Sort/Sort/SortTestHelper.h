#pragma once
#include <iostream>
#include <ctime>
#include <cassert>
#include <string>

using namespace std;

namespace SortTestHelper {
	// 生成有n个元素的随机数组,每个元素的随机范围为[rangeL, rangeR]
	int* generateRandomArray(int n, int rangeL, int rangeR) {
		assert(rangeL <= rangeR);	//确保L小于R

		int* arr = new int[n];
		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		}
		return arr;
	}

	// 生成有n个元素的近有序数组,元素的范围为[0, n),swaptime为交换程度，越大则越无序
	int* generateNearlyOrderedArray(int n, int swapTimes) {
		int* arr = new int[n];

		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			arr[i] = i;
		}
		for (int j = 0; j < swapTimes; j++) {
			int posx = rand() % n;
			int posy = rand() % n;
			swap(arr[posx], arr[posy]);
		}
		return arr;
	}

	// 复制相同的数组
	int* copyIntArray(int arr[], int n) {
		int* newarr = new int[n];
		copy(arr, arr + n, newarr);
		return newarr;
	}

	// 打印n个元素的数组
	template<typename T>
	void printArray(T arr[], int n) {
		for (int i = 0; i < n; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
		return;
	}

	// 检查是否排序完成
	template<typename T>
	bool isSorted(T arr, int n) {
		for (int i = 0; i < n-1; i++) {
			if (arr[i] > arr[i + 1]) {
				return false;
			}
		}
		return true;
	}

	// 计算算法使用时间
	template<typename T>
	void testSort(const string& sortName, void (*sort)(T[], int), T arr[], int n) {
		clock_t startTime, endTime;
		startTime = clock();
		sort(arr, n);
		endTime = clock();

		assert(isSorted(arr, n));
		double duration = ((double)(endTime - startTime)) / CLK_TCK;
		cout << sortName << ": " << duration << " s" << endl;

		return;
	}

};