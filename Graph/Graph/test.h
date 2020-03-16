#pragma once
#include<iostream>
#include<ctime>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"
#include "Components.h"
#include "Path.h"
#include "ShortestPath.h"

using namespace std;

int test1() {
	// 遍历图
	int N = 20;
	int M = 100;
	srand(time(NULL));
	cout << "Sparse graph:" << endl;
	// sparse graph
	SparseGraph g1(N, false);
	for (int i = 0; i < M; i++) {
		int a = rand() % N;
		int b = rand() % N;
		g1.addEdge(a, b);
	}

	// O(E)遍历
	for (int v = 0; v < N; v++) {
		cout << v << ":";
		SparseGraph::adjIterator adj(g1, v);
		for (int w = adj.begin(); !adj.end(); w = adj.next()) {
			cout << w << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Dense graph:" << endl;
	// dense graph
	DenseGraph g2(N, false);
	for (int i = 0; i < M; i++) {
		int a = rand() % N;
		int b = rand() % N;
		g2.addEdge(a, b);
	}

	// O(V^2)
	for (int v = 0; v < N; v++) {
		cout << v << ":";
		DenseGraph::adjIterator adj(g2, v);
		for (int w = adj.begin(); !adj.end(); w = adj.next()) {
			cout << w << " ";
		}
		cout << endl;
	}
	return 0;
}

int test2() {
	// 测试读取txt中的图结构
	string filename = "testG2.txt";
	cout << "Sparse graph:" << endl;
	SparseGraph g1(7, false);
	ReadGraph<SparseGraph> readGraph1(g1, filename);
	g1.show();

	cout << endl << "Dense graph:" << endl;
	DenseGraph g2(7, false);
	ReadGraph<DenseGraph> readGraph2(g2, filename);
	g2.show();

	return 0;
}

int test3() {
	// TestG1.txt
	cout << endl << "Sparse graph:" << endl;
	string filename1 = "testG1.txt";
	SparseGraph g1 = SparseGraph(13, false);
	ReadGraph<SparseGraph> readGraph1(g1, filename1);
	Component<SparseGraph> com1(g1);
	cout << "TestG1.txt, Component Count:" << com1.count() << endl;

	cout << endl << "Dense graph:" << endl;
	string filename2 = "testG2.txt";
	DenseGraph g2 = DenseGraph(7, false);
	ReadGraph<DenseGraph> readGraph2(g2, filename2);
	Component<DenseGraph> com2(g2);
	cout << "TestG2.txt, Component Count:" << com2.count() << endl;

	return 0;
}

int test4() {
	// 测试寻路
	string filename = "testG2.txt";
	SparseGraph g = SparseGraph(7, false);
	ReadGraph<SparseGraph> readGraph(g, filename);
	g.show();
	cout << endl;

	Path<SparseGraph> path(g, 0);
	cout << "DFS:";
	path.showPath(6);
	return 0;
}

int test5() {
	string filename = "testG2.txt";
	SparseGraph g = SparseGraph(7, false);
	ReadGraph<SparseGraph> readGraph(g, filename);
	g.show();
	cout << endl;

	Path<SparseGraph> dfs(g, 0);
	cout << "DFS : ";
	dfs.showPath(6);

	ShortestPath<SparseGraph> bfs(g, 0);
	cout << "BFS : ";
	bfs.showPath(6);

	return 0;
}