#include <iostream>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;
// ... struct TreeNode, insert(), height() tai su dung tu Chuong 2 ...
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int key) {
    if (root == nullptr)
        return new TreeNode(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);

    return root;
}

int height(TreeNode* root) {
    if (root == nullptr)
        return -1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}


int main() {
 int sizes[] = {1000, 5000, 10000, 20000};
 cout << "n,chieu_cao_thuc_te,log2(n),n-1,thoi_gian_chen_ms" << endl;

 for (int n : sizes) {
    int keys[20000];
    for(int i=0;i<n;i++) 
    keys[i]=i;

 TreeNode* root = nullptr;
 auto start = high_resolution_clock::now();
 for (int i = 0; i < n; i++)
 root = insert(root, i); // chen theo thu tu da sap xep
 auto end = high_resolution_clock::now();
 // TODO: tinh thoi gian chen bang duration<double, milli>
double insertTime= duration<double, milli>(end - start).count();
 
// TODO: goi height(root) de lay chieu cao thuc te
int treeHeight=height(root);
 // TODO: in ra n, chieu cao thuc te, chieu cao ly thuyet log2(n), thoi gian
 double chieuCaoLyThuyet= log2(n);

 cout << n << "," << treeHeight << "," << chieuCaoLyThuyet << "," << (n - 1) << "," << insertTime << endl;
 }
 return 0;
}