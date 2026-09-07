#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>
#include <random>
using namespace std;
using namespace chrono;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode* insert(TreeNode* root, int key) {
    if (root == nullptr) {
        return new TreeNode(key);
    }
    if (key < root->data) {
        root->left = insert(root->left, key);
    }
    else if (key > root->data) {
        root->right = insert(root->right, key);
    }
    return root;
}

int height(TreeNode* root) {
    if (root == nullptr) {
        return -1;
    }
    return 1 + max(height(root->left), height(root->right));
}

TreeNode* search(TreeNode* root, int key) {
    if (root == nullptr || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

struct AVLNode {
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int val)
        : data(val), height(0), left(nullptr), right(nullptr) {}
};

int getHeight(AVLNode* node) {
    if (node == nullptr) return -1;
    return node->height;
}

void updateHeight(AVLNode* node) {
    if (node != nullptr) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}

int getBalanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

bool isValidAVLHelper(AVLNode* node, long long minVal, long long maxVal, bool& balanced) {
    if (node == nullptr) return true;
    if (node->data <= minVal || node->data >= maxVal) return false;
    
    int bfVal = getBalanceFactor(node);
    if (bfVal < -1 || bfVal > 1) balanced = false;
    
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
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* insertAVL(AVLNode* node, int key) {
    if (node == nullptr) return new AVLNode(key);
    
    if (key < node->data) {
        node->left = insertAVL(node->left, key);
    }
    else if (key > node->data) {
        node->right = insertAVL(node->right, key);
    }
    else {
        return node;
    }

    updateHeight(node);
    int bf = getBalanceFactor(node);

    if (bf > 1 && key < node->left->data) return rotateRight(node);
    if (bf < -1 && key > node->right->data) return rotateLeft(node);
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

AVLNode* searchAVL(AVLNode* root, int key) {
    if (root == nullptr || root->data == key) return root;
    if (key < root->data) return searchAVL(root->left, key);
    return searchAVL(root->right, key);
}

int main() {
    cout << "n,Cau truc,Chieu cao,Thoi gian chen (ms),Thoi gian tim 1000 lan (ms)" << endl;

    int sizes[] = {1000, 5000, 10000, 20000};
    srand(42); 

    for (int n : sizes) {
        int searchKeys[1000];
        for (int i = 0; i < 1000; i++) {
            searchKeys[i] = (rand() % n) + 1; 
        }

        TreeNode* bstRoot = nullptr;

        auto startBST = high_resolution_clock::now();
        for (int i = 1; i <= n; i++) {
            bstRoot = insert(bstRoot, i);
        }
        auto endBST = high_resolution_clock::now();
        double insertTimeBST = duration<double, milli>(endBST - startBST).count();

        int heightBST = height(bstRoot);

        int foundCountBST = 0; 
        auto startSearchBST = high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            if (search(bstRoot, searchKeys[i]) != nullptr) {
                foundCountBST++;
            }
        }
        auto endSearchBST = high_resolution_clock::now();
        double searchTimeBST = duration<double, milli>(endSearchBST - startSearchBST).count();

    
        AVLNode* avlRoot = nullptr;

        auto startAVL = high_resolution_clock::now();
        for (int i = 1; i <= n; i++) {
            avlRoot = insertAVL(avlRoot, i);
        }
        auto endAVL = high_resolution_clock::now();
        double insertTimeAVL = duration<double, milli>(endAVL - startAVL).count();

        if (!isValidAVL(avlRoot)) {
            cout << "LOI AVL khi chen xong n = " << n << endl;
            return 1;
        }

        int heightAVL = getHeight(avlRoot);

        int foundCountAVL = 0;
        auto startSearchAVL = high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            if (searchAVL(avlRoot, searchKeys[i]) != nullptr) {
                foundCountAVL++;
            }
        }
        auto endSearchAVL = high_resolution_clock::now();
        double searchTimeAVL = duration<double, milli>(endSearchAVL - startSearchAVL).count();

        cout << n << ",BST thuong," << heightBST << "," << insertTimeBST << "," << searchTimeBST << endl;
        cout << n << ",AVL," << heightAVL << "," << insertTimeAVL << "," << searchTimeAVL << endl;

        if (foundCountBST != 1000 || foundCountAVL != 1000) {
            cout << "Canh bao: Khong tim thay du 1000 phan tu!" << endl;
        }
    }

    return 0;
}