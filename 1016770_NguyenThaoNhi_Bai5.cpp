#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
using namespace std::chrono;
// ... struct TreeNode, insert(), height(), search() nhu cac bai truoc ...
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int key) {
    if (root == nullptr)
        return new TreeNode(key);

    if (key < root->data) {
        root->left = insert(root->left, key);
    }
    else if (key > root->data) {
        root->right = insert(root->right, key);
    }
    return root;
}

TreeNode* search(TreeNode* root, int key) {
    if (root == nullptr)
        return nullptr;
    if (root->data == key)
        return root;
    if (key < root->data)
       return search(root->left, key);
       
    return search(root->right, key);
}

int height(TreeNode* root) {
    if (root == nullptr)
        return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (leftHeight > rightHeight)
        return 1 + leftHeight;
    else
        return 1 + rightHeight;
}


int main() {
 mt19937 rng(42); // seed co dinh de ket qua co the lap lai duoc
 vector<int> sizes = {1000, 5000, 10000, 20000};
 cout << "n,loai_du_lieu,chieu_cao,thoi_gian_chen_ms,thoi_gian_tim_ms\n";
 for (int n : sizes) {
 // Kich ban (a): chen ngau nhien
 vector<int> keys(n);
 for (int i = 0; i < n; i++) keys[i] = i;
 shuffle(keys.begin(), keys.end(), rng);
 TreeNode* root = nullptr;
 auto t1 = high_resolution_clock::now();
 for (int k : keys) root = insert(root, k);
 auto t2 = high_resolution_clock::now();
 // TODO: tinh thoi gian chen = duration<double, milli>(t2-t1).count()
        double insertTime =
        duration<double, milli>(t2 - t1).count();
 // TODO: tinh chieu cao bang height(root)
         int treeHeight = height(root);
 // QUAN TRONG: dung "volatile" hoac cong don ket qua de tranh
         volatile int foundCount = 0;
 // trinh bien dich toi uu hoa (loai bo) vong lap tim kiem ben duoi
 auto t3 = high_resolution_clock::now();
 for (int i = 0; i < 1000; i++)
 if (search(root, keys[i % n]) != nullptr)
    foundCount++;
 auto t4 = high_resolution_clock::now();
 // TODO: tinh thoi gian tim kiem = duration<double, milli>(t4-t3).count()
         double searchTime =
            duration<double, milli>(t4 - t3).count();
 // TODO: in ket qua theo dinh dang yeu cau
         cout << n << ",Ngau nhien,"
             << treeHeight << ","
             << insertTime << ","
             << searchTime << endl;
 // Kich ban (b): chen theo thu tu da sap xep - sinh vien tu hoan thien
 // tuong tu nhu tren, nhung voi keys[i] = i theo thu tu tang dan
         root = nullptr;
        for (int i = 0; i < n; i++)
            keys[i] = i;

        auto t5 = high_resolution_clock::now();

        for (int k : keys)
            root = insert(root, k);
        auto t6 = high_resolution_clock::now();
        double insertTimeSorted =
            duration<double, milli>(t6 - t5).count();
        int treeHeightSorted = height(root);
        volatile int foundCountSorted = 0;
        auto t7 = high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            if (search(root, keys[i % n]) != nullptr)
                foundCountSorted++;
        }
        auto t8 = high_resolution_clock::now();
        double searchTimeSorted =
            duration<double, milli>(t8 - t7).count();

        cout << n << ",Da sap xep,"
             << treeHeightSorted << ","
             << insertTimeSorted << ","
             << searchTimeSorted << endl;
    
 }
 return 0;
}