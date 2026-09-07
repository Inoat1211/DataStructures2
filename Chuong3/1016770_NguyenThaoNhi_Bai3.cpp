#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct AVLNode {
 int data;
 int height;
 AVLNode* left;
 AVLNode* right;
 AVLNode(int val) : data(val), height(0), left(nullptr), right(nullptr) {}
};
int getHeight(AVLNode* node) {
 // TODO: sinh vien cai dat
 if (node == nullptr) {
        return -1;
    }
    return node->height;
}
void updateHeight(AVLNode* node) {
 // TODO: sinh vien cai dat
 if (node != nullptr) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}
int getBalanceFactor(AVLNode* node) {
 // TODO: sinh vien cai dat
 if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}
// Kiem tra dong thoi: (a) la BST hop le, (b) can bang tai moi nut
bool isValidAVLHelper(AVLNode* node, long long minVal, long long maxVal,
 bool& balanced) {
 if (node == nullptr) return true;
 if (node->data <= minVal || node->data >= maxVal) return false;
 int bfVal = getBalanceFactor(node);
 if (bfVal < -1 || bfVal > 1) balanced = false; // vi pham dieu kien can bang
 bool leftOk = isValidAVLHelper(node->left, minVal, node->data, balanced);
 bool rightOk = isValidAVLHelper(node->right, node->data, maxVal, balanced);
 return leftOk && rightOk;
}
bool isValidAVL(AVLNode* root) {
 bool balanced = true;
 bool isBST = isValidAVLHelper(root, LLONG_MIN, LLONG_MAX, balanced);
 return isBST && balanced;
}

AVLNode* rotateRight(AVLNode* y) {
 // TODO: tham khao lai Vi du 3.3 trong bai giang, chu y thu tu updateHeight
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}
AVLNode* rotateLeft(AVLNode* x) {
 // TODO: tham khao lai Vi du 3.3 trong bai giang
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* insertAVL(AVLNode* node, int key) {
 // Buoc 1: chen nhu BST thong thuong
 if (node == nullptr) return new AVLNode(key);
 if (key < node->data)
 node->left = insertAVL(node->left, key);
 else if (key > node->data)
 node->right = insertAVL(node->right, key);
 else
 return node;
 // Buoc 2: cap nhat chieu cao
 updateHeight(node);
 // Buoc 3: TODO - tinh balance factor va xu ly 4 truong hop LL/RR/LR/RL
 int bf = getBalanceFactor(node);
 if (bf > 1 && key < node->left->data)
        return rotateRight(node);
if (bf < -1 && key > node->right->data)
        return rotateLeft(node);
if (bf > 1 && key > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
}
if (bf < -1 && key < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
 return node;
}
int main() {
 // Kiem thu lan luot 4 bo du lieu trong bang - moi bo dung 1 cay AVL rieng
 cout << "--- LL ---" << endl;
 AVLNode* rootLL = nullptr;
 int keysLL[] = {30, 20, 10};
 for (int k : keysLL) {
 rootLL = insertAVL(rootLL, k);
 // TODO: in ket qua isValidAVL(root), va in root->data de kiem tra
 if (!isValidAVL(rootLL)) cout << "Loi AVL khi chen " << k << endl;
        cout << "Chen " << k << " -> Goc: " << rootLL->data << endl;
    }
 // gia tri gan voi ky vong trong bang (vd: sau khi chen het, root la 20)
 cout << "Goc cuoi = " << rootLL->data << " (Ky vong: 20)\n\n";

 cout << "--- RR ---" << endl;
    AVLNode* rootRR = nullptr;
    int keysRR[] = {10, 20, 30};
    for (int k : keysRR) {
        rootRR = insertAVL(rootRR, k);
        if (!isValidAVL(rootRR)) cout << "Loi AVL khi chen " << k << endl;
        cout << "Chen " << k << " -> Goc: " << rootRR->data << endl;
    }
    cout << "Goc cuoi = " << rootRR->data << " (Ky vong: 20)\n\n";

cout << "--- LR ---" << endl;
    AVLNode* rootLR = nullptr;
    int keysLR[] = {30, 10, 20};
    for (int k : keysLR) {
        rootLR = insertAVL(rootLR, k);
        if (!isValidAVL(rootLR)) cout << "Loi AVL khi chen " << k << endl;
        cout << "Chen " << k << " -> Goc: " << rootLR->data << endl;
    }
    cout << "Goc cuoi = " << rootLR->data << " (Ky vong: 20)\n\n";

cout << "--- RL ---" << endl;
    AVLNode* rootRL = nullptr;
    int keysRL[] = {10, 30, 20};
    for (int k : keysRL) {
        rootRL = insertAVL(rootRL, k);
        if (!isValidAVL(rootRL)) cout << "Loi AVL khi chen " << k << endl;
        cout << "Chen " << k << " -> Goc: " << rootRL->data << endl;
    }
    cout << "Goc cuoi = " << rootRL->data << " (Ky vong: 20)\n";
 
 return 0;
}
