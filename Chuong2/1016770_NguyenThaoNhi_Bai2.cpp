#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
 int data;
 TreeNode* left;
 TreeNode* right;
 TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
void preorderHelper(TreeNode* root, vector<int>& result) {
 // TODO: Nut - Trai - Phai
 if (root == nullptr)
        return;
    result.push_back(root->data);
    preorderHelper(root->left, result);
    preorderHelper(root->right, result);
}
vector<int> preorder(TreeNode* root) {
    vector<int> result;
    preorderHelper(root, result);
    return result;
}


// TODO: cai dat tuong tu cho inorder() va postorder()
void inorderHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr)
        return;
    inorderHelper(root->left, result);
    result.push_back(root->data);
    inorderHelper(root->right, result);
}

vector<int> inorder(TreeNode* root) {
    vector<int> result;
    inorderHelper(root, result);
    return result;
}

void postorderHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr)
        return;
    postorderHelper(root->left, result);
    postorderHelper(root->right, result);
    result.push_back(root->data);
}

vector<int> postorder(TreeNode* root) {
    vector<int> result;
    postorderHelper(root, result);
    return result;
}

vector<int> levelOrder(TreeNode* root) {
 vector<int> result;
 if (root == nullptr) return result;
 queue<TreeNode*> q;
 q.push(root);
 // TODO: dung vong lap while + queue de duyet theo tung muc
 
 while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        result.push_back(current->data);

        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }

 return result;
}

vector<int> inorderIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> s;
    TreeNode* current = root;
    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        result.push_back(current->data);
        current = current->right;
    }
    return result;
}


void printVector(const vector<int>& v) {
 for (int x : v) cout << x << " ";
 cout << endl;
}

int main() {
 // TODO: xay dung lai cay nhu Bai 1
 
TreeNode* root = new TreeNode(50);
root->left = new TreeNode(30);
root->right = new TreeNode(70);
root->left->left = new TreeNode(20);
root->left->right = new TreeNode(40);
root->right->right = new TreeNode(80);
root->left->left->left = new TreeNode(10);
    
cout << "Preorder:    "; printVector(preorder(root));
cout << "Inorder:     "; printVector(inorder(root));
cout << "Postorder:   "; printVector(postorder(root));
cout << "Level-order: "; printVector(levelOrder(root));
 
    vector<int> inIterative = inorderIterative(root);
    cout << "Inorder khong de quy: ";
    printVector(inIterative);
 return 0;
}
