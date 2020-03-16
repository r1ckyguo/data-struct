#pragma once
#include <iostream>
#include <cassert>
#include <ctime>
#include <vector>
#include "BinarySearch.h"
#include "BST.h"
#include "FileOps.h"
#include "SequenceST.h"
using namespace std;

// 测试两种二分查找法
int test1() {
    int n = 1000000;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = i;

    // 测试非递归二分查找法
    clock_t startTime = clock();
    for (int i = 0; i < 2 * n; i++) {
        int v = binarySearch(a, n, i);
        if (i < n)
            assert(v == i);
        else
            assert(v == -1);
    }
    clock_t endTime = clock();
    cout << "Binary Search (Without Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

    // 测试递归的二分查找法
    startTime = clock();
    for (int i = 0; i < 2 * n; i++) {
        int v = binarySearch2(a, n, i);
        if (i < n)
            assert(v == i);
        else
            assert(v == -1);
    }
    endTime = clock();
    cout << "Binary Search (Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;


    //delete[] a;

    return 0;
}

// 测试二分查找树查找txt的文字词频
int test2() {
    string filename = "bible.txt";
    vector<string> words;
    if (FileOps::readFile(filename, words)) {
        cout << "There are totally " << words.size() << " words in " << filename << endl;

        cout << endl;

        // test BST
        time_t startTime = clock();
        BST<string, int> bst = BST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            // 统计bible里面的词数
            int* res = bst.search(*iter);
            if (res == NULL) {
                bst.insert(*iter, 1);   // 如果BST没有记录这个词的话则记录
            }
            else {
                (*res)++;               // 如果有记录这个词，这个词频++
            }
        }

        cout << "'god' : " << *bst.search("god") << endl;   // 查找词频
        time_t endTime = clock();
        cout << "BST, time: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        cout << endl;

        // test 顺序查找sst
        startTime = clock();
        SequenceST<string, int> sst = SequenceST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            // 统计bible里面的词数
            int* res = sst.search(*iter);
            if (res == NULL) {
                sst.insert(*iter, 1);   // 如果BST没有记录这个词的话则记录
            }
            else {
                (*res)++;               // 如果有记录这个词，这个词频++
            }
        }
        cout << "'god' : " << *sst.search("god") << endl;   // 查找词频

        endTime = clock();
        cout << "SST, time: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        cout << endl;
    }
}

// 测试遍历
int test3() {
    srand(time(NULL));
    BST<int, int> bst = BST<int, int>();
    int n = 10;
    for (int i = 0; i < n; ++i) {
        int key = rand() % n;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        cout << key << " ";
        bst.insert(key, value);
    }
    cout << endl;
    // test size
    cout << "size:" << bst.size() << endl << endl;
    // test preOder
    cout << "preOrder:" << endl;
    bst.preOrder();
    cout << endl << endl;
    // test inOder
    cout << "inOrder:" << endl;
    bst.inOrder();
    cout << endl << endl;
    // test postOder
    cout << "postOrder:" << endl;
    bst.postOrder();
    cout << endl << endl;
    // test levelOrder
    cout << "levelOrder:" << endl;
    bst.levelOrder();
    cout << endl << endl;
    return 0;
}

// 测试移除最大最小值
int test4() {
    srand(time(NULL));
    BST<int, int> bst = BST<int, int>();

    int n = 10;
    for (int i = 0; i < n; i++) {
        int key = rand() % n;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        //cout<<key<<" ";
        bst.insert(key, value);
    }

    // test removeMin
    while( !bst.isEmpty() ){
        cout<<"min: "<<bst.minimum()<<endl;
        bst.removeMin();
        cout<<"After removeMin, size = "<<bst.size()<<endl;
    }

    // test removeMax
    //while (!bst.isEmpty()) {
    //    cout << "max: " << bst.maxmum() << endl;
    //    bst.removeMax();
    //    cout << "After removeMax, size = " << bst.size() << endl;
    //}

    return 0;
}

// 测试移除某一值
int test5() {

    srand(time(NULL));
    BST<int, int> bst = BST<int, int>();

    int n = 10;
    for (int i = 0; i < n; i++) {
        int key = rand() % n;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        //cout<<key<<" ";
        bst.insert(key, value);
    }

    // test remove
    // remove elements in random order
    int* order = new int[n];
    for (int i = 0; i < n; i++)
        order[i] = i;
    shuffle(order, n);
    for (int i = 0; i < n; ++i) {
        if (bst.contain(order[i])) {
            bst.remove(order[i]);
            cout << "After remove " << order[i] << " size = " << bst.size() << endl;
        }
    }
    return 0;
}

// 测试二叉搜索树的弊端
int test6() {
    string filename = "communist.txt";
    vector<string> words;
    if (FileOps::readFile(filename, words)) {

        cout << "There are totally " << words.size() << " words in " << filename << endl;

        cout << endl;


        // test BST
        time_t startTime = clock();
        BST<string, int>* bst = new BST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int* res = (*bst).search(*iter);
            if (res == NULL)
                (*bst).insert(*iter, 1);
            else
                (*res)++;
        }

        cout << "'unite' : " << *(*bst).search("unite") << endl;
        time_t endTime = clock();
        cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

        cout << endl;

        delete bst;


        // test SST
        startTime = clock();
        SequenceST<string, int>* sst = new SequenceST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int* res = (*sst).search(*iter);
            if (res == NULL)
                (*sst).insert(*iter, 1);
            else
                (*res)++;
        }

        cout << "'unite' : " << *(*sst).search("unite") << endl;

        endTime = clock();
        cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

        cout << endl;

        delete sst;


        // test BST2
        startTime = clock();
        BST<string, int>* bst2 = new BST<string, int>();

        sort(words.begin(), words.end());

        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int* res = (*bst2).search(*iter);
            if (res == NULL)
                (*bst2).insert(*iter, 1);
            else
                (*res)++;
        }

        cout << "'unite' : " << *(*bst2).search("unite") << endl;
        endTime = clock();
        cout << "BST2 , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

        cout << endl;

        delete bst2;

    }

    return 0;
}