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

 void siftUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            int temp = heap[i];
            heap[i] = heap[parent(i)];
            heap[parent(i)] = temp;
            i = parent(i);
        }
    }

 void siftDown(int i) {
        int n = heap.size();
        int maxIndex = i;
        int l = left(i);
        int r = right(i);

        if (l < n && heap[l] > heap[maxIndex]) {
            maxIndex = l;
        }
        if (r < n && heap[r] > heap[maxIndex]) {
            maxIndex = r;
        }

        if (i != maxIndex) {
            int temp = heap[i];
            heap[i] = heap[maxIndex];
            heap[maxIndex] = temp;
            
            siftDown(maxIndex);
        }
    }   

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
 void insert(int value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }
 int extractMax() {
        if (heap.empty()) {
            cout << "Loi: Heap rong!" << endl;
            return -1; 
        }
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            siftDown(0);
        }
        return maxVal;
}

    void buildHeap(vector<int> arr) {
        heap = arr;
        int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            siftDown(i);
        }
    }

    bool isEmpty() {
        return heap.empty();
    }
};
int main() {
 MaxHeap h; 
 vector<int> arr = {45, 12, 78, 34, 89, 23, 67, 90, 11, 56, 3, 99, 41, 7, 88};
 h.buildHeap(arr);
cout << "Kiem tra isValidHeap() sau khi build: " << (h.isValidHeap() ? "Hop le (True)" : "Sai (False)") << endl;
cout << "Ket qua extractMax() lien tuc:" << endl;
    while (!h.isEmpty()) {
        cout << h.extractMax() << " ";
    }
    cout << endl;
 return 0;
}