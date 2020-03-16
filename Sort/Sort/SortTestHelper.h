#pragma once
#include <iostream>
#include <ctime>
#include <cassert>
#include <string>

using namespace std;

namespace SortTestHelper {
	// ������n��Ԫ�ص��������,ÿ��Ԫ�ص������ΧΪ[rangeL, rangeR]
	int* generateRandomArray(int n, int rangeL, int rangeR) {
		assert(rangeL <= rangeR);	//ȷ��LС��R

		int* arr = new int[n];
		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		}
		return arr;
	}

	// ������n��Ԫ�صĽ���������,Ԫ�صķ�ΧΪ[0, n),swaptimeΪ�����̶ȣ�Խ����Խ����
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

	// ������ͬ������
	int* copyIntArray(int arr[], int n) {
		int* newarr = new int[n];
		copy(arr, arr + n, newarr);
		return newarr;
	}

	// ��ӡn��Ԫ�ص�����
	template<typename T>
	void printArray(T arr[], int n) {
		for (int i = 0; i < n; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
		return;
	}

	// ����Ƿ��������
	template<typename T>
	bool isSorted(T arr, int n) {
		for (int i = 0; i < n-1; i++) {
			if (arr[i] > arr[i + 1]) {
				return false;
			}
		}
		return true;
	}

	// �����㷨ʹ��ʱ��
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