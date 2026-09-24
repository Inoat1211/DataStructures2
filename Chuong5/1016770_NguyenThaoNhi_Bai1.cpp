#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;
class GraphMatrix {
private:
    int V;
    vector<vector<int>> matrix;

public:
    GraphMatrix(int V) {
        this->V = V;
        matrix = vector<vector<int>>(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v) {
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    long long traverseAll() {
        long long result = 0;

        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (matrix[u][v] != 0) {
                    result++;
                }
            }
        }

        return result;
    }
};

class GraphList {
private:
    int V;
    vector<vector<int>> adjList;

public:
    GraphList(int V) {
        this->V = V;
        adjList = vector<vector<int>>(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    long long traverseAll() {
        long long result = 0;

        for (int u = 0; u < V; u++) {
            for (int v : adjList[u]) {
                result++;
            }
        }

        return result;
    }

    int totalElements() {
        int total = 0;

        for (int u = 0; u < V; u++) {
            total += adjList[u].size();
        }

        return total;
    }
};


int main() {
 mt19937 rng(42);
 vector<int> sizes = {1000, 5000, 10000};
 for (int V : sizes) {
 int E = V * 5;
 vector<pair<int,int>> edges(E);
 uniform_int_distribution<int> dist(0, V - 1);
 for (auto& e : edges) e = {dist(rng), dist(rng)};
 // TODO: xay dung matrix (vector<vector<int>> kich thuoc VxV) tu edges
 // TODO: xay dung adjList (vector<vector<int>> kich thuoc V) tu edges
    GraphMatrix matrix(V);
    GraphList adjList(V);

    for (auto& e : edges) {
        matrix.addEdge(e.first, e.second);
        adjList.addEdge(e.first, e.second);
    }
 // TODO: tinh bo nho ly thuyet cua ca 2 cau truc (theo cong thuc de bai)
    long long matrixMemory = 1LL * V * V * sizeof(int);
    int totalElements = adjList.totalElements();
    long long listMemory = 1LL * totalElements * sizeof(int);

 // TODO: do thoi gian duyet toan bo canh ke cua tat ca dinh - ca 2 cau truc
 // LUU Y: dung "volatile" hoac cong don ket qua tranh trinh dich
 // toi uu hoa loai bo vong lap (xem lai Bai thuc hanh Chuong 2, Bai 5)
    auto startMatrix = high_resolution_clock::now();
    long long matrixResult = matrix.traverseAll();
    auto endMatrix = high_resolution_clock::now();
    double matrixTime =
        duration<double, milli>(endMatrix - startMatrix).count();
// Do thoi gian duyet danh sach ke
    auto startList = high_resolution_clock::now();
    long long listResult = adjList.traverseAll();
    auto endList = high_resolution_clock::now();
    double listTime =
        duration<double, milli>(endList - startList).count();
 // TODO: in ket qua: V, E, bo_nho_matrix, bo_nho_list, tg_matrix, tg_list
        cout << "V = " << V << endl;
        cout << "E = " << E << endl;

        cout << "Bo nho ma tran: "
             << matrixMemory / (1024.0 * 1024.0)
             << " MB" << endl;

        cout << "Bo nho danh sach: "
             << listMemory / (1024.0 * 1024.0)
             << " MB" << endl;

        cout << "Thoi gian duyet ma tran: "
             << matrixTime
             << " ms" << endl;

        cout << "Thoi gian duyet danh sach: "
             << listTime
             << " ms" << endl;
 }
 return 0;
}