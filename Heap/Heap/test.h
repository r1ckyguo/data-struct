#pragma once
#include<iostream>
#include<ctime>
#include "Heap.h"
#include "HeapSort.h"
#include "SortTestHelper.h"
#include "MergeSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "IndexMaxHeap.h"

using namespace std;

void test1() {
    // ��ӡ�Ѵ�С
    MaxHeap<int> maxheap = MaxHeap<int>(100);
    cout << maxheap.size() << endl;

    return;
}

void test2() {
    // ����50�����ݵ���
    MaxHeap<int> maxheap = MaxHeap<int>(100);
    srand(time(NULL));
    for (int i = 0; i < 50; i++) {
        maxheap.insert(rand() % 100);
    }
    // ��ӡ���ѵĽṹ
    maxheap.testPrint();
    return;
}

void test3() {
    // ����ȡ���ѵ����ֵ
    MaxHeap<int> maxheap = MaxHeap<int>(100);
    srand(time(NULL));
    for (int i = 0; i < 50; i++) {
        maxheap.insert(rand() % 100);
    }
    maxheap.testPrint();
    // �Ѷѵ����ֵȡ����
    while (!maxheap.isEmpty()) {
        cout << maxheap.extractMax() << " ";
    }
    cout << endl;
}

void test4() {
    // ���Զ�����
    int n = 1000000;

    // ����1 һ���Բ���
    cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
    int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);
    int* arr3 = SortTestHelper::copyIntArray(arr1, n);
    int* arr4 = SortTestHelper::copyIntArray(arr1, n);
    int* arr5 = SortTestHelper::copyIntArray(arr1, n);
    int* arr6 = SortTestHelper::copyIntArray(arr1, n);
    int* arr7 = SortTestHelper::copyIntArray(arr1, n);


    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Way, arr3, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);
    SortTestHelper::testSort("Heap Sort 3", heapSort3, arr6, n);
    SortTestHelper::testSort("Heap Sort 4", heapSort4, arr7, n);


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;


    cout << endl;


    // ����2 ���Խ������������
    int swapTimes = 100;
    cout << "Test for Random Nearly Ordered Array, size = " << n << ", swap time = " << swapTimes << endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);
    arr5 = SortTestHelper::copyIntArray(arr1, n);
    arr6 = SortTestHelper::copyIntArray(arr1, n);
    arr7 = SortTestHelper::copyIntArray(arr1, n);


    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Way, arr3, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);
    SortTestHelper::testSort("Heap Sort 3", heapSort3, arr6, n);
    SortTestHelper::testSort("Heap Sort 4", heapSort4, arr7, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    cout << endl;


    // ����3 ���Դ��ڰ���������ͬԪ�ص�����
    cout << "Test for Random Array, size = " << n << ", random range [0,10]" << endl;
    arr1 = SortTestHelper::generateRandomArray(n, 0, 10);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);
    arr5 = SortTestHelper::copyIntArray(arr1, n);
    arr6 = SortTestHelper::copyIntArray(arr1, n);
    arr7 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Way, arr3, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);
    SortTestHelper::testSort("Heap Sort 3", heapSort3, arr6, n);
    SortTestHelper::testSort("Heap Sort 4", heapSort4, arr7, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    return;
}

void test5() {
    // ����indexheapʹ��
    IndexMaxHeap<int> indexheap = IndexMaxHeap<int>(100);
    for (int i = 0; i < 3; i++) {
        indexheap.insert(i, rand() % 10);
    }
    indexheap.testPrint();
    indexheap.insert(1, 99);
    cout << endl;
    indexheap.testPrint();
    while (!indexheap.isEmpty()) {
            cout << indexheap.extractMax() << endl;
            indexheap.testPrint();
        }
    //int a;
    //while (!indexheap.isEmpty()) {
    //    a = indexheap.extractMax();
    //    cout << a << endl;
    //    indexheap.testPrint();
    //}
}
void test6() {
    int n = 100;
    // indexmaxheap�Ķ�����
    int* arr = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        arr[i] = rand() % n;
    SortTestHelper::printArray(arr, n);
    SortTestHelper::testSort("Heap Sort Using Index-Max-Heap", heapSortUsingIndexMaxHeap, arr, n);
    SortTestHelper::printArray(arr, n);
    delete[] arr;

}