#include <iostream>
#include <climits>
using namespace std;

struct TreeNode {
 int data;
 TreeNode* left;
 TreeNode* right;
 TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool isValidBSTHelper(TreeNode* node, long long minVal, long long maxVal) {
 // TODO: dieu kien dung: node == nullptr -> tra ve true
     if (node == nullptr)
        return true;
 // TODO: neu node->data <= minVal hoac node->data >= maxVal -> tra ve false
     if (node->data <= minVal || node->data >= maxVal)
        return false;
 // TODO: goi de quy cho ca 2 nhanh, thu hep dan khoang [minVal, maxVal]
     bool leftValid = isValidBSTHelper(
        node->left,
        minVal,
        node->data
    );

    bool rightValid = isValidBSTHelper(
        node->right,
        node->data,
        maxVal
    );

    return leftValid && rightValid;
}

bool isValidBST(TreeNode* root) {
 return isValidBSTHelper(root, LLONG_MIN, LLONG_MAX);
}
int main() {
 // TODO: xay dung cay hop le (vi du Bai 1), kiem tra isValidBST() == true
    TreeNode* root1 = new TreeNode(50);
    root1->left = new TreeNode(30);
    root1->right = new TreeNode(70);
    root1->left->left = new TreeNode(20);
    root1->left->right = new TreeNode(40);
    root1->right->right = new TreeNode(80);
    root1->left->left->left = new TreeNode(10);
    cout << "Cay 1: ";

    if (isValidBST(root1))
        cout << "La BST" << endl;
    else
        cout << "Khong phai BST" << endl;
 // TODO: xay dung cay KHONG hop le (hinh tren), kiem tra isValidBST() == false
    TreeNode* root2 = new TreeNode(10);
    root2->left = new TreeNode(5);
    root2->right = new TreeNode(15);
    root2->right->left = new TreeNode(6);   
    root2->right->right = new TreeNode(20);
    cout << "Cay 2: ";
    if (isValidBST(root2))
        cout << "La BST" << endl;
    else
        cout << "Khong phai BST" << endl;

 return 0;
}
