#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

class HashMapAutoResize {
private:
 vector<list<pair<int,string>>> table;
 int capacity;
 int count = 0;
 int rehashCount = 0;
 const double LOAD_FACTOR_THRESHOLD = 0.75;
 int hashFunc(int key, int cap) const { return ((key % cap) + cap) % cap; }
 void rehash() {
 // TODO: tao bang moi capacity gap doi, bam lai toan bo phan tu cu
 int oldCapacity = capacity;
    vector<list<pair<int, string>>> oldTable = table;
    capacity *= 2;
    table.clear();
    table.resize(capacity);
    for (const auto& bucket : oldTable) {
        for (const auto& item : bucket) {
            int index = hashFunc(item.first, capacity);
            table[index].push_back(item);
        }
    }
 // TODO: tang rehashCount len 1, in ra thong bao capacity cu -> moi
    rehashCount++;
    cout << "Rehash: " << oldCapacity << " -> " << capacity << endl;
 }
public:
 HashMapAutoResize(int cap = 8) : capacity(cap) { table.resize(capacity); }
 void insert(int key, const string& value) {
 // TODO: kiem tra load factor TRUOC khi chen, goi rehash() neu can
 // TODO: chen nhu binh thuong (tham khao Bai 2)
 if (double(count + 1) / capacity > LOAD_FACTOR_THRESHOLD) {
            rehash();
    }
    int index = hashFunc(key, capacity);
    for (auto& item : table[index]) {
        if (item.first == key) {
            item.second = value;
            return;
        }
    }
    table[index].push_back({key, value});
    count++;
 }
 double currentLoadFactor() const { return double(count) / capacity; }
 int getRehashCount() const { return rehashCount; }
};
int main() {
 HashMapAutoResize hm(8);
 for (int i = 1; i <= 1000; i++)
 hm.insert(i, "value_" + to_string(i));
 cout << "Tong so lan rehash: " << hm.getRehashCount() << endl;
 cout << "Load factor cuoi cung: " << hm.currentLoadFactor() << endl;
 return 0;
}
