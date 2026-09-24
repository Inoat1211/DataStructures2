#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

vector<int> bfsShortestPath(vector<vector<int>>& adjList, int source, int n, vector<int>& parent) {
    vector<int> dist(n, INT_MAX);
    parent.assign(n, -1);
    queue<int> q;

    dist[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adjList[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    return dist;
}

vector<int> reconstructPath(vector<int>& parent, int target) {
    vector<int> path;

    int cur = target;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n = 10; 
    vector<vector<int>> adjList(n);
    auto addFriend = [&](int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    };

    addFriend(0, 1);
    addFriend(0, 2);
    addFriend(1, 3);
    addFriend(2, 3);
    addFriend(3, 4);
    addFriend(4, 5);
    addFriend(5, 6);
    addFriend(6, 7);
    addFriend(7, 8);
    addFriend(8, 9);
    addFriend(2, 5);
    addFriend(4, 9);

    int u, v;
    cout << "Nhap 2 nguoi can tim duong quen biet (0-9): ";
    cin >> u >> v;
    vector<int> parent;
    vector<int> dist = bfsShortestPath(adjList, u, n, parent);
    if (dist[v] == INT_MAX) {
        cout << "Khong co duong quen biet!" << endl;
    } else {
        cout << "So buoc quen biet ngan nhat: " << dist[v] << endl;
        vector<int> path = reconstructPath(parent, v);
        cout << "Duong di: ";
        for (int p : path) cout << p << " ";
        cout << endl;
    }
    return 0;
}