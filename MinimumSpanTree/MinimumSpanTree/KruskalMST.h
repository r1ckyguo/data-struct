#pragma once
#include <iostream>
#include <vector>
#include "Edge.h"
#include "Heap/MinHeap.h"
#include "UnionFind/UnionFind.h"

using namespace std;


template <typename Graph, typename Weight>
class KruskalMST {
private:
    vector<Edge<Weight>> mst;
    Weight mstWeight;

public:
    KruskalMST(Graph& graph) {
        MinHeap<Edge<Weight>> heap(graph.E());
        for (int i = 0; i < graph.V(); ++i) {
            typename Graph::adjIterator adj(graph, i);
            for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()) {
                // 避免无向图插入两次同一条边
                if (e->v() < e->w()) {
                    heap.insert(*e);
                }
            }
        }

        UF::UnionFind uf = UF::UnionFind(graph.V());
        while (!heap.isEmpty() && mst.size() < graph.V() - 1) {
            Edge<Weight> e = heap.extractMin();
            if (uf.isConnected(e.v(), e.w())) {
                continue;
            }
            mst.push_back(e);
            uf.unionElement(e.v(), e.w());
        }
        mstWeight = mst[0].wt();
        for (int i = 1; i < mst.size(); i++)
            mstWeight += mst[i].wt();
    }
    ~KruskalMST() {

    }
    vector<Edge<Weight>> mstEdges() {
        return mst;
    };

    Weight result() {
        return mstWeight;
    };
};