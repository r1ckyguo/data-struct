#pragma once
#include <iostream>
#include <ctime>
#include "UnionFind1.h"
#include "UnionFind2.h"
#include "UnionFind3.h"
#include "UnionFind4.h"
#include "UnionFind5.h"
using namespace std;

void testUF() {
	int n = 100000;
	srand(time(NULL));
	UF1::UnionFind uf1 = UF1::UnionFind(n);

	time_t startTime = clock();
	for (int i = 0; i < n; ++i) {
		int a = rand() % n;
		int b = rand() % n;
		uf1.unionElement(a, b);
	}
	for (int i = 0; i < n; ++i) {
		int a = rand() % n;
		int b = rand() % n;
		uf1.isConnected(a, b);
	}
	time_t endTime = clock();
	cout << "UF1£ºid Union," << 2 * n << "ops," << double(endTime - startTime) / CLOCKS_PER_SEC << "s." << endl;
	
	srand(time(NULL));
	UF2::UnionFind uf2 = UF2::UnionFind(n);

	startTime = clock();

	for (int i = 0; i < n; i++) {
		int a = rand() % n;
		int b = rand() % n;
		uf2.unionElement(a, b);
	}
	for (int i = 0; i < n; i++) {
		int a = rand() % n;
		int b = rand() % n;
		uf2.isConnected(a, b);
	}
	endTime = clock();

	cout << "UF2:parent union, " << 2 * n << " ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	srand(time(NULL));
	UF3::UnionFind uf3 = UF3::UnionFind(n);

	startTime = clock();

	for (int i = 0; i < n; i++) {
		int a = rand() % n;
		int b = rand() % n;
		uf3.unionElement(a, b);
	}
	for (int i = 0; i < n; i++) {
		int a = rand() % n;
		int b = rand() % n;
		uf3.isConnected(a, b);
	}
	endTime = clock();

	cout << "UF3:parent union-size advance, " << 2 * n << " ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	srand(time(NULL));
	UF4::UnionFind uf4 = UF4::UnionFind(n);

	startTime = clock();

	for (int i = 0; i < n; i++) {
		int a = rand() % n;
		int b = rand() % n;
		uf4.unionElement(a, b);
	}
	for (int i = 0; i < n; i++) {
		int a = rand() % n;
		int b = rand() % n;
		uf4.isConnected(a, b);
	}
	endTime = clock();

	cout << "UF4:parent union-rank advance, " << 2 * n << " ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	srand(time(NULL));
	UF5::UnionFind uf5 = UF5::UnionFind(n);

	startTime = clock();

	for (int i = 0; i < n; i++) {
		int a = rand() % n;
		int b = rand() % n;
		uf5.unionElement(a, b);
	}
	for (int i = 0; i < n; i++) {
		int a = rand() % n;
		int b = rand() % n;
		uf5.isConnected(a, b);
	}
	endTime = clock();

	cout << "UF5:parent union-rank advance and path compression, " << 2 * n << " ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
}