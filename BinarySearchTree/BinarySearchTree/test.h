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

// �������ֶ��ֲ��ҷ�
int test1() {
    int n = 1000000;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = i;

    // ���Էǵݹ���ֲ��ҷ�
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

    // ���Եݹ�Ķ��ֲ��ҷ�
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

// ���Զ��ֲ���������txt�����ִ�Ƶ
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
            // ͳ��bible����Ĵ���
            int* res = bst.search(*iter);
            if (res == NULL) {
                bst.insert(*iter, 1);   // ���BSTû�м�¼����ʵĻ����¼
            }
            else {
                (*res)++;               // ����м�¼����ʣ������Ƶ++
            }
        }

        cout << "'god' : " << *bst.search("god") << endl;   // ���Ҵ�Ƶ
        time_t endTime = clock();
        cout << "BST, time: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        cout << endl;

        // test ˳�����sst
        startTime = clock();
        SequenceST<string, int> sst = SequenceST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            // ͳ��bible����Ĵ���
            int* res = sst.search(*iter);
            if (res == NULL) {
                sst.insert(*iter, 1);   // ���BSTû�м�¼����ʵĻ����¼
            }
            else {
                (*res)++;               // ����м�¼����ʣ������Ƶ++
            }
        }
        cout << "'god' : " << *sst.search("god") << endl;   // ���Ҵ�Ƶ

        endTime = clock();
        cout << "SST, time: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        cout << endl;
    }
}

// ���Ա���
int test3() {
    srand(time(NULL));
    BST<int, int> bst = BST<int, int>();
    int n = 10;
    for (int i = 0; i < n; ++i) {
        int key = rand() % n;
        // Ϊ�˺������Է���,����valueֵȡ��keyֵһ��
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

// �����Ƴ������Сֵ
int test4() {
    srand(time(NULL));
    BST<int, int> bst = BST<int, int>();

    int n = 10;
    for (int i = 0; i < n; i++) {
        int key = rand() % n;
        // Ϊ�˺������Է���,����valueֵȡ��keyֵһ��
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

// �����Ƴ�ĳһֵ
int test5() {

    srand(time(NULL));
    BST<int, int> bst = BST<int, int>();

    int n = 10;
    for (int i = 0; i < n; i++) {
        int key = rand() % n;
        // Ϊ�˺������Է���,����valueֵȡ��keyֵһ��
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

// ���Զ����������ı׶�
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