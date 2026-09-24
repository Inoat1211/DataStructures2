#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge { int u, v, weight; };

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n) { for (int i = 0; i < n; i++) parent[i] = i; }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return false; 
        parent[rx] = ry;
        return true;
    }
};

int kruskalMST(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    DSU dsu(n);
    int totalWeight = 0;
    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            totalWeight += e.weight;
        }
    }
    return totalWeight;
}

int primMST(vector<vector<pair<int,int>>>& adjList, int n) {
    vector<bool> inMST(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    int totalWeight = 0;
    pq.push({0, 0}); 

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (inMST[u]) continue; 

        inMST[u] = true;
        totalWeight += w;

        for (auto& [v, weight] : adjList[u]) {
            if (!inMST[v]) {
                pq.push({weight, v});
            }
        }
    }
    return totalWeight;
}

int main() {
    int n = 6;
    vector<Edge> edgeList = {
        {0,1,4}, {0,2,3}, {1,2,1}, {1,3,2}, {2,3,4},
        {3,4,2}, {4,5,6}, {2,4,5}, {3,5,7}
    };
    vector<vector<pair<int,int>>> adjList(n);
    for (auto& e : edgeList) {
        adjList[e.u].push_back({e.v, e.weight});
        adjList[e.v].push_back({e.u, e.weight});
    }
    cout << "Tong trong so MST (Kruskal): " << kruskalMST(edgeList, n) << endl;
    cout << "Tong trong so MST (Prim): " << primMST(adjList, n) << endl;
    return 0;
}