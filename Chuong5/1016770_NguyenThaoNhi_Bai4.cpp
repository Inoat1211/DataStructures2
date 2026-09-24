#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<int> dijkstra(vector<vector<pair<int,int>>>& adjList, int source, int n) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue; 

        for (auto& [v, w] : adjList[u]) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    vector<vector<pair<int,int>>> adjList(5);
    auto addEdge = [&](int u, int v, int w) {
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    };
    addEdge(0, 1, 5); addEdge(1, 3, 5); 
    addEdge(0, 2, 1); addEdge(2, 4, 1); addEdge(4, 3, 1); 

    int n = 5;
    vector<int> bfsSteps(n, -1);
    vector<bool> visited(n, false);
    queue<int> q;
    visited[0] = true;
    bfsSteps[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& [v, w] : adjList[u]) {
            if (!visited[v]) {
                visited[v] = true;
                bfsSteps[v] = bfsSteps[u] + 1; 
                q.push(v);
            }
        }
    }
    vector<int> dist = dijkstra(adjList, 0, n);

    cout << "So buoc (BFS, bo qua trong so) tu A den D: " << bfsSteps[3] << endl;
    cout << "Tong trong so ngan nhat (Dijkstra) tu A den D: " << dist[3] << endl;

    if (bfsSteps[3] < dist[3]) {
        cout << "Nhan xet: BFS chon duong A-B-D (2 canh) vi it canh hon,"
             << " nhung tong trong so lai lon hon (10 > 3)." << endl;
        cout << "=> BFS KHONG tim duoc duong di re nhat tren do thi co trong so khac nhau." << endl;
    }

    return 0;
}