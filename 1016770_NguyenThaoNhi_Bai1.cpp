#include <iostream>
using namespace std;
struct TreeNode {
 int data;
 TreeNode* left;
 TreeNode* right;
 TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
int countNodes(TreeNode* root) {
 // TODO: sinh vien cai dat
 if(root == nullptr) 
    return 0;
 return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(TreeNode* root) {
 // TODO: sinh vien cai dat
 if(root == nullptr) 
    return 0;
 if(root->left == nullptr&& root->right == nullptr)
    return 1;
 return countLeaves(root->left)+countLeaves(root->right);
}

int height(TreeNode* root) {
 // TODO: sinh vien cai dat
 if(root == nullptr) 
    return -1;
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
    return 1 + leftHeight;
    else return 1 + rightHeight;
}

int depth(TreeNode* root, int target){
    if(root == nullptr) 
        return -1;
    if(root->data==target)
        return 0;
      if (target < root->data) {
        int d = depth(root->left, target);
        if (d == -1)
            return -1;
        return d + 1;
    }
    else {
        int d = depth(root->right, target);
        if (d == -1)
            return -1;
        return d + 1;
    }
}

int maxValue(TreeNode* root){
    if(root == nullptr)
        return -1;
    while(root->right!=nullptr)
        root=root->right;
    return root->data;
}

int minValue(TreeNode* root){
    if(root == nullptr)
        return -1;
    while(root->left!=nullptr)
        root=root->left;
    return root->data;
}

int main() {
 // Xay dung cay thu cong nhu hinh ve trong de bai
 TreeNode* root = new TreeNode(50);
 root->left = new TreeNode(30);
 root->right = new TreeNode(70);
 root->left->left = new TreeNode(20);
 root->left->right = new TreeNode(40);
 root->right->right = new TreeNode(80);
 root->left->left->left = new TreeNode(10);

 // TODO: sinh vien tiep tuc xay dung day du cay theo hinh ve
 cout << "Tong so nut: " << countNodes(root) << endl;
 cout << "So nut la: " << countLeaves(root) << endl;
 cout << "Chieu cao: " << height(root) << endl;

 // TODO: goi va in ket qua cho depth(), maxValue(), minValue()
  cout << "Do sau cua nut 40: " << depth(root, 40) << endl;
 cout << "Gia tri lon nhat: " << maxValue(root) << endl;
 cout << "Gia tri nho nhat: " << minValue(root) << endl;
 return 0;
}