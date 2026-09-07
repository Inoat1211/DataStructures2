#include <algorithm>
#include <iostream>
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
