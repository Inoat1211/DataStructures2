#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool dfsCheckCycle(int u, vector<vector<int>>& adjList, vector<int>& color) {
    color[u] = 1;
    for (int v : adjList[u]) {
        if (color[v] == 1) {
            return true;
        }
        if (color[v] == 0 && dfsCheckCycle(v, adjList, color)) {
            return true;
        }
    }
    color[u] = 2; 
    return false;
}

bool hasCycle(vector<vector<int>>& adjList, int n) {
    vector<int> color(n, 0);
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (dfsCheckCycle(i, adjList, color)) return true;
        }
    }
    return false;
}

void dfsTopo(int u, vector<vector<int>>& adjList, vector<bool>& visited, vector<int>& result) {
    visited[u] = true;
    for (int v : adjList[u]) {
        if (!visited[v]) {
            dfsTopo(v, adjList, visited, result);
        }
    }
    result.push_back(u);
}

vector<int> topologicalSort(vector<vector<int>>& adjList, int n) {
    vector<bool> visited(n, false);
    vector<int> result;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsTopo(i, adjList, visited, result);
        }
    }
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    int numCourses = 8;
    vector<vector<int>> adjList(numCourses);

    adjList[0].push_back(1); 
    adjList[2].push_back(1); 
    adjList[0].push_back(4);
    adjList[1].push_back(3); 
    adjList[1].push_back(5); 
    adjList[4].push_back(5); 
    adjList[4].push_back(6); 
    adjList[3].push_back(7); 
    adjList[5].push_back(7); 
    adjList[6].push_back(7);

    if (hasCycle(adjList, numCourses)) {
        cout << "LOI: chuong trinh dao tao co vong lap tien quyet!" << endl;
        return 1;
    }
    vector<int> order = topologicalSort(adjList, numCourses);
    cout << "Thu tu hoc hop le: ";
    for (int course : order) cout << course << " ";
    cout << endl;
    return 0;
}