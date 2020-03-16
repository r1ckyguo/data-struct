#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template<typename Graph, typename Weight>
class ReadGraph {
public:
	ReadGraph(Graph& graph, const string& filename) {
		ifstream file(filename);		// ���ļ�
		string line;
		int V, E;

		assert(file.is_open());		// ȷ���ļ��Ѿ���
		assert(getline(file, line));	// ���ļ��л�ȡһ��
		stringstream ss(line);	// �ַ�������һ��

		ss >> V >> E;	// ��ȡ�ļ��Ľڵ�ͱ�
		assert(V == graph.V());		// ȷ���ڵ���ͬ
		
		for (int i = 0; i < E; i++) {
			assert(getline(file, line));
			stringstream ss(line);
			int a, b;
			Weight w;
			ss >> a >> b >> w;
			assert(a >= 0 && a < V);
			assert(b >= 0 && b < V);
			graph.addEdge(a, b, w);
		}
	}
};