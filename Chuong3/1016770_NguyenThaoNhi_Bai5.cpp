#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class MaxHeap {
private:
 vector<int> heap;
 int parent(int i) { return (i - 1) / 2; }
 int left(int i) { return 2 * i + 1; }
 int right(int i) { return 2 * i + 2; }
public:
 void setData(vector<int> arr) { heap = arr; } // gan truc tiep, khong qua
 // ham insert
 bool isValidHeap() {
 // TODO: for i tu 1 den heap.size()-1
 for (int i = 1; i < heap.size(); i++) {
 // neu heap[parent(i)] < heap[i] -> tra ve false
 if (heap[parent(i)] < heap[i]) {
                return false;
            }
        }
 // TODO: het vong lap khong vi pham -> tra ve true
 return true;
 }
 void printAsTree() {
 int n = heap.size();
 int levelStart = 0, levelSize = 1;
 while (levelStart < n) {
 // TODO: in cac phan tu tu chi so levelStart den het muc hien tai
 for (int i = levelStart; i < n && i < levelStart + levelSize; i++) {
                cout << heap[i] << " ";
            }
    cout << endl;
 // TODO: cap nhat levelStart += levelSize; levelSize *= 2;
    levelStart += levelSize;
    levelSize *= 2;
 }
 }
};
int main() {
 MaxHeap h1; h1.setData({90, 70, 80, 20, 60, 50, 30});
 cout << "Mang A hop le? " << (h1.isValidHeap() ? "Co" : "Khong") << endl;
 MaxHeap h2; h2.setData({90, 70, 80, 85, 60, 50, 30});
 cout << "Mang B hop le? " << (h2.isValidHeap() ? "Co" : "Khong") << endl;
 return 0;
}
