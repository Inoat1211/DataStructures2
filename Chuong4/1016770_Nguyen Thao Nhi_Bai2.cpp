#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;
class HashMapChaining {
private:
 vector<list<pair<int,string>>> table;
 int capacity;
 int hashFunc(int key) const { return ((key % capacity) + capacity) % capacity; }
public:
 HashMapChaining(int cap = 11) : capacity(cap) { table.resize(capacity); }
 void insert(int key, const string& value) {
 // TODO: tham khao lai Vi du 4.2 trong bai giang
 int index = hashFunc(key);
for (auto& item : table[index]) {
        if (item.first == key) {
            item.second = value;
            return;
            }
        }
    table[index].push_back({key, value});
 }
 bool search(int key, string& outValue) const {
 // TODO
 int index = hashFunc(key);
 for (const auto& item : table[index]) {
        if (item.first == key) {
            outValue = item.second;
            return true;
        }
    }
    return false;
 }
 bool remove(int key) {
 // TODO
 int index = hashFunc(key);
for (auto it = table[index].begin(); it != table[index].end(); ++it) {
    if (it->first == key) {
            table[index].erase(it);
            return true;
        }
    }
        return false;
 }
};

class HashMapOpenAddressing {
private:
 struct Slot {
 int key; string value;
 bool occupied = false, deleted = false;
 };
 vector<Slot> table;
 int capacity, count = 0;
 int hashFunc(int key) const { return ((key % capacity) + capacity) % capacity; }
public:
 HashMapOpenAddressing(int cap = 11) : capacity(cap) { table.resize(capacity); }
 bool insert(int key, const string& value) {
 // TODO: tham khao lai Vi du 4.3, chu y dieu kien dung vong lap do
 int start = hashFunc(key);
 for (int i = 0; i < capacity; i++) {
        int index = (start + i) % capacity;
        if (table[index].occupied) {
            if (table[index].key == key) {
                table[index].value = value;
                    return true;
            }
        }
        else {
            table[index].key = key;
            table[index].value = value;
            table[index].occupied = true;
            table[index].deleted = false;
            count++;
            return true;
            }
        }

        return false;
 }
 bool search(int key, string& outValue) const {
 // TODO
 int start = hashFunc(key);
  for (int i = 0; i < capacity; i++) {
        int index = (start + i) % capacity;
        if (!table[index].occupied && !table[index].deleted) {
            return false;
        }
        if (table[index].occupied && table[index].key == key) {
            outValue = table[index].value;
            return true;
        }
        }
        return false;
 }
 bool remove(int key) {
 // TODO: CHI danh dau deleted = true, KHONG dat occupied lai ve false
 int start = hashFunc(key);
 for (int i = 0; i < capacity; i++) {
    int index = (start + i) % capacity;
    if (!table[index].occupied && !table[index].deleted) {
        return false;
    }
    if (table[index].occupied && table[index].key == key) {
        table[index].deleted = true;
        count--;
        return true;
        }
    }

    return false;
 }
};
int main() {
 // Ca kiem thu bat buoc: chon capacity nho de chac chan xay ra va cham
  cout << "PHAN A SEPARATE CHAINING" << endl;
  HashMapChaining hm1(5);
    hm1.insert(1, "A");
    hm1.insert(6, "B");     
    hm1.insert(11, "C");     
    string val;
    if (hm1.search(6, val)) {
        cout << "Tim thay 6: " << val << endl;
    }
    else {
        cout << "Khong tim thay 6" << endl;
    }
    hm1.insert(6, "B_updated");
    if (hm1.search(6, val)) {
        cout << "Sau khi cap nhat 6: " << val << endl;
    }
    if (hm1.remove(6)) {
        cout << "Xoa 6 thanh cong" << endl;
    }
    else {
        cout << "Khong tim thay 6 de xoa" << endl;
    }
    if (hm1.search(6, val)) {
        cout << "Tim thay 6: " << val << endl;
    }
    else {
        cout << "Khong tim thay 6 sau khi xoa" << endl;
    }
cout << endl;
cout << "PHAN B OPEN ADDRESSING" << endl;
 HashMapOpenAddressing hm2(5);
 hm2.insert(0, "A"); // hash(0) = 0
 hm2.insert(5, "B"); // hash(5) = 0 -> va cham, do sang slot 1
 hm2.insert(10, "C"); // hash(10) = 0 -> va cham, do sang slot 2
 hm2.remove(5); // xoa khoa GIUA chuoi do (slot 1)
 string val2;
 bool found = hm2.search(10, val2); // khoa 10 van con, PHAI tim thay
 cout << (found ? "Tim thay 10 - CORRECT" : "KHONG tim thay 10 - LOI!") << endl;
 return 0;
}
