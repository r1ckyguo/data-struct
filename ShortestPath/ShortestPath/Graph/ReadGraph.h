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
		ifstream file(filename);		// 打开文件
		string line;
		int V, E;

		assert(file.is_open());		// 确保文件已经打开
		assert(getline(file, line));	// 从文件中获取一行
		stringstream ss(line);	// 字符流，读一行

		ss >> V >> E;	// 获取文件的节点和边
		assert(V == graph.V());		// 确保节点相同
		
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